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

int main(int argc, char *argv[])
{
  cout << "> Initialise server...\n";
  string hostName, port, file_dir; 
  hostName = "localhost";
  port = "4000"; 
  file_dir = "."; 

  if(argc > 1){
      hostName = argv[1];
      port = argv[2]; 
      file_dir = argv[3];     
  } else {
      cout << ">> Default settings\n";
  }
        
  cout << "Host name -> "<< hostName <<" | Port -> " << port << " | File Directory -> "<< file_dir << endl << endl;
   
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
    cout << "> Acquire address info...\n";
    if ((status = getaddrinfo(NULL, "4000", &hints, &servinfo)) != 0) {
      fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(status));
      exit(1);
    }
    //Get socket 
    cout << "> Creating socket...\n";
    sockfd = socket(servinfo->ai_family, servinfo->ai_socktype, servinfo->ai_protocol);
    if(sockfd == -1){
      cout << "socket error\n"; 
      exit(1);
    }

    //Bind socket to address
    cout << "> Binding...\n";
    b = bind(sockfd, servinfo->ai_addr, servinfo->ai_addrlen);
    if(b == -1){
      cout << "bind error\n"; 
      exit(1);
    }
  sleep(1);
    //Listen for incoming connect
    int lis; 
    cout<<"> Listening...\n";
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
    cout << ">> Successfully connected to client01\n";

  //Now we'd want to 'wait' for requests from the client! 
  
  bool isEnd = false; 
  char buf[40] = {0};
  stringstream ss; 
  cout << "> Receiving request:\n";
  while(!isEnd){
    memset(buf, '\0', sizeof(buf));
    
    if(recv(sock02, buf, 40, 0) == -1){
      perror("recv");
      return 5; 
    }
    ss << buf << endl; 
    cout << buf << endl << "> Successfully received, sending response\n"; 
    //Need to parse the request. Get method, URL, Version,  IP
    sleep(2);

    //ECHO BACK >> 
    string res_msg; 
    //default response 
    res_msg = "200 OK\n";
     if (send(sock02, res_msg.c_str(), 20, 0) == -1) {
      perror("send");
      return 6;
    }

    if (ss.str() == "close\n")
      break;
    
    ss.str("");
  }


    
    //Connect! 
   /* int con; 
    con = connect(sockfd, servinfo->ai_addr, servinfo->ai_addrlen);
    if(con == -1){
      cout << "connection error\n";
      exit(1);
    }*/ 
  return 0;
}