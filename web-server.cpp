#include <stdio.h>
#include <string.h>
#include <sys/types.h>

#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <iostream>
#include <sstream> 
#include <errno.h> 
#include <unistd.h> 
#include <sstream> 
#include "httpRequest.h"


using namespace std; 

void parseRequest(char parseBuffer[40]);
string searchFile(char fileName[], int sock);
void sendFile (FILE *file, int sock); 
void send400(); 
char buffer[500]; //will store contents of the html file 
char store[30] = {0};
int BR_flag = 0; 

int main(int argc, char *argv[])
{
  //DEFAULT SETTINGS 
  cout << "\n---SERVER---\n";
  string hostName, port, file_dir; 
  hostName = "localhost";
  port = "4000"; 
  file_dir = "."; 
  if(argc > 1){
      cout << ">> Custom settings\n";
      hostName = argv[1];
      port = argv[2]; 
      file_dir = argv[3];     
  } else {
      cout << ">> Default settings\n";
  }
        
  cout << "Host name -> "<< hostName <<" | Port -> " << port << " | File Directory -> "<< file_dir << endl << endl;
  const char *portCon = port.c_str(); 
  int sockfd,sock02; 
  int b; 

  int getaddrinfo(const char *node, const char *service, 
  const struct addrinfo *hints, 
  struct addrinfo **res); 
   
  int status;
  struct addrinfo hints;
  struct addrinfo *servinfo;  // will point to the results

  memset(&hints, 0, sizeof hints); // make sure the struct is empty
  hints.ai_family = AF_INET;     //set ipv4 
  hints.ai_socktype = SOCK_STREAM; //tcp
  hints.ai_flags = AI_PASSIVE;     // fill in my IP for me
    //Get address for specific port 
    cout << "> Acquiring address info...";
    if ((status = getaddrinfo(NULL, portCon, &hints, &servinfo)) != 0) {
      fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(status));
      exit(1);
    }
    //Get socket 
    cout << "creating socket...";
    sockfd = socket(servinfo->ai_family, servinfo->ai_socktype, servinfo->ai_protocol);
    if(sockfd == -1){
      cout << "socket error\n"; 
      exit(1);
    }

    //Bind socket to address
    cout << "binding...";
    b = bind(sockfd, servinfo->ai_addr, servinfo->ai_addrlen);
    if(b == -1){
      cout << "bind error\n"; 
      exit(1);
    }
  sleep(1);
    //Listen for incoming connect
    int lis; 
    cout<<"listening...\n";
    lis = listen(sockfd, 10);
    if(lis == -1){
      cout << "listen error\n";
      exit(1);
    }

    //accept incoming connection 
    struct sockaddr_storage incom_addr; 
    socklen_t addr_size; 
    addr_size = sizeof incom_addr; 
    sock02 = accept(sockfd, servinfo->ai_addr, &addr_size);
    if(sock02 == -1){
      cout << "accept error\n";
      exit(1);
    }
    cout << "> Successfully connected to client\n";

  //Now we'd want to 'wait' for requests from the client! 
  
  bool isEnd = false; 
  char buf[60] = {0};
  
  stringstream ss; 
  cout << "> Receiving request:\n";
  while(!isEnd){
    memset(buf, '\0', sizeof(buf));
    cout << "Server about to receive request.\n";

    if(recv(sock02, buf, 60, 0) == -1){
      perror("recv");
      return 5; 
    }
    cout << "Server just received request\n";
    ss << buf << endl; 
    cout << buf << endl; 
    //Need to parse the request. Get method, URL, Version,  IP
    
    parseRequest(buf);
    //now store array has the file location we want 
    //ss << store << endl; 
    cout << "> Request parsed, searching for file:"<< store << endl;

    //Now we need to search for the file 
    string res_msg;
    res_msg = searchFile(store,sock02);
     if (send(sock02, res_msg.c_str(), 20, 0) == -1) {
      perror("send");
      return 6;
    }
    
    
    if (ss.str() == "close\n")
      break;

    char rmsg[6] = {0}; 
    int rrr = recv(sock02, rmsg, 1, 0);
    //cout << "Receiving " << rmsg << " from client...\n";
    if(rrr == -1){
      perror("recv");
    }
    if(rmsg[0] == 'n'){
      cout << "Terminating connnection\n";
      isEnd = true;
    }
     //set loop to finish 
     memset(buffer,'\0',sizeof(buffer));
  }
    
  cout << "EXIT\n";
  return 0;
}

void parseRequest(char parseBuffer[60]){
    char sample;
    int flag=0; 
    //cout << "Entered parseRequest.\n";
     //max size = 30 
    int count =0; 
    for(int i=0; i < 60; i++){
      sample = parseBuffer[i]; //take in a character from buf 
      
      //cout  << "|" << sample; 
      if(flag == 1){
        if(sample == ' '){
          flag = 0; 
        } 
        else {
          store[count] = sample; 
          //cout << "-" << store[count]; 
          count++; 
        }
      if(parseBuffer[0] != 'G' || parseBuffer[1] != 'E' || parseBuffer[2] != 'T' || parseBuffer[3] != ' '){
          //Since we only need to do GET, make sure this is what is said
          BR_flag = 1; 
        }
      }
      //since we know we only need GET, ignore the first three chars
      if(sample == '/' && parseBuffer[i-1] == ' '){ //if we encounter empty space 
        //now we know the next thing will be the directory 
        flag = 1; 
      }
    }
}

string searchFile(char fileName[], int sock){
  FILE *f;
  string respCode; 
  //cout << "\"" << fileName << "\"" << endl;  
  f = fopen(fileName, "r"); //try to open file 
 
  if(!f){
    cout << "> Sending 404 Not Found\n";
    respCode = "404 Not Found\n";
    f = fopen("404.html", "r"); //open the 'not found' file if you we get that error 
  } else if (BR_flag == 1){
    cout << "> Sending 400 Bad Request\n";
    respCode = "400 Bad Request\n";
    f = fopen("400.html", "r");
  } else {
    cout << "> File found. Sending 200 OK\n"; 
    respCode = "200 OK\n";
    //call sendFile function 
    
  }
  //RESET BUFFER 
  
  sendFile(f,sock);
  return respCode;
}


void sendFile (FILE *file,int sock){
  int i =0;
  while(!feof(file)){
    buffer[i] = fgetc(file); 
    i++; 
  }
  //Now buffer has the file.
  //cout << "> Sending file\n";
  int s = send(sock, buffer, 500, 0);
  if(s == -1){
    perror("send");
  }
    
}

