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
  cout << "Thomas Kelly - 16323455\n---SERVER---\n";
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
  //Tell user basic info     
  cout << "Host name -> "<< hostName <<" | Port -> " << port << " | File Directory -> "<< file_dir << endl << endl;

  //Address/port configuration 
  const char *portCon = port.c_str(); 
  int sockfd,sock02; 
  int b; 

  int getaddrinfo(const char *node, const char *service, 
  const struct addrinfo *hints, 
  struct addrinfo **res); 
   
  int status;
  struct addrinfo hints;
  struct addrinfo *servinfo;  // will point to the results

  memset(&hints, 0, sizeof hints); // empty the struct 
  hints.ai_family = AF_INET;     //set ipv4 
  hints.ai_socktype = SOCK_STREAM; //tcp
  hints.ai_flags = AI_PASSIVE;     // auto set IP 
    //Get address for specific port 
    cout << "> Acquiring address info...";
    if ((status = getaddrinfo(NULL, portCon, &hints, &servinfo)) != 0) {
      fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(status));
      exit(1);
    }
    //Create socket 
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
    sleep(1);//wait to allow bind. Thinking this might help solve the bind error...
    //Listen for incoming connect
    int lis; 
    cout<<"listening...\n";
    lis = listen(sockfd, 10);
    if(lis == -1){
      cout << "listen error\n";
      exit(1);
    }

    
    //create a fork to handle multiple concurrent clients 
    fork();

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
  
  bool isEnd = false; //intialise loop(connection) to stay open 
  char buf[60] = {0};
  
  stringstream ss; 
  
  while(!isEnd){ //keep looping until ALL clients terminate their connection 
    BR_flag = 0; 
    memset(buf, '\0', sizeof(buf));
    cout << "> Receiving request:\n";
    //cout << "Server about to receive request.\n";
    if(recv(sock02, buf, 60, 0) == -1){
      perror("recv");
      return 5; 
    }
    //cout << "Server just received request\n";

    ss << buf << endl; 
    cout << buf << endl; //printing request 

    //Need to parse the request. Get method, URL, Version,  IP
    parseRequest(buf);
    //now store array has the file location we want 
    cout << "> Request parsed, searching for file:"<< store << endl;

    //Now we need to search for the file 
    string res_msg;
    res_msg = searchFile(store,sock02); //search for the specified file, returning the corresponding response message 
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
      cout << "Terminating connnection\n"; //if the client wants to, terminate their connection 
      isEnd = true;
    }
     //reset buffers 
     memset(buffer,'\0',sizeof(buffer));
     memset(store, '\0', sizeof(store));
  }
    
  cout << "EXIT\n";
  return 0;
}

void parseRequest(char parseBuffer[60]){ //splits the request and stores the file name in 'store' 
    char sample;
    int flag=0; 
    //cout << "Entered parseRequest.\n";
     //max size = 30 
    int count =0; 
    for(int i=0; i < 60; i++){
      sample = parseBuffer[i]; //take in a character from buf 
      
      
      if(flag == 1){
        if(sample == ' '){
          flag = 0; 
        } 
        else {
          store[count] = sample; 
          
          count++; 
        }
      
      }
      //since we know we only need GET, ignore the first three chars
      if(sample == '/' && parseBuffer[i-1] == ' '){ //if we encounter empty space 
        //now we know the next thing will be the directory 
        flag = 1; 
      }
      if(parseBuffer[i] == 'H' && parseBuffer[i+1] == 'T' && parseBuffer[i+2] == 'T' && parseBuffer[i+3] == 'P'){
          //cout << parseBuffer[i] << parseBuffer[i+1] << parseBuffer[i+2] << parseBuffer[i+3] << parseBuffer[i+4] << endl;  
          if(parseBuffer[i+7] == '1'){ //then we have requested http 1.1 
            BR_flag = 1; 
          }
      }
    }
}

string searchFile(char fileName[], int sock){ //opens the required file based on the request and then set a corresponding response code 
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
  } 
  //call sendFile function 
  sendFile(f,sock);
  //we now have the response code and corresponding file. 
  return respCode;
}


void sendFile (FILE *file,int sock){
  int i =0;
  while(!feof(file)){
    buffer[i] = fgetc(file); 
    i++; 
  }
  //Now buffer has the file.
 
  int s = send(sock, buffer, 500, 0);
  if(s == -1){
    perror("send");
  }
    
}

