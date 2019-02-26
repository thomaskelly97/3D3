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


using namespace std; 

int main(int argc, char *argv[])
{
   cout << "> Initialise server...\n";
  //struct sockaddr_in my_addr; 
 //int bind(int sockfd, struct sockaddr *my_addr, int addrlen);
  //int socket (int domain, int type, int protocol);
  
  int sockfd,sock02; 
  int b; 

  int getaddrinfo(const char *node, const char *service, 
  const struct addrinfo *hints, 
  struct addrinfo **res); 
   
  int status;
  struct addrinfo hints;
  struct addrinfo *servinfo;  // will point to the results

  memset(&hints, 0, sizeof hints); // make sure the struct is empty
  hints.ai_family = AF_INET;     // don't care IPv4 or IPv6
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags = AI_PASSIVE;     // fill in my IP for me
    //Get address for specific port 
    cout << "> Acquire address info...\n";
    if ((status = getaddrinfo(NULL, "3490", &hints, &servinfo)) != 0) {
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

    //Listen for incoming connect
    int lis; 
    cout<<"> Listening...";
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

    //Send Sample 
    int len,bytes_sent; 
    char* msg = "Hello world\n";
    len = strlen(msg);
    bytes_sent = send(sock02,msg,len,0);

    
    //Connect! 
   /* int con; 
    con = connect(sockfd, servinfo->ai_addr, servinfo->ai_addrlen);
    if(con == -1){
      cout << "connection error\n";
      exit(1);
    }*/ 
  return 0;
}