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

#include "httpRequest.h"
#include "httpRequest.cpp"
using namespace std; 


#define PORT "3490" // the port client will be connecting to 

#define MAXDATASIZE 100 // max number of bytes we can get at once 

int main(int argc, char *argv[])
{    
    string URL = "http://localhost:4000/index.html"; 
    if (argc > 1){
        URL = argv[1]; 
    }
    cout << "Search URL: " << URL << endl; 

    int sock02 = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in servAddr; 
    servAddr.sin_family = AF_INET;
    servAddr.sin_port = htons(4000);     // short, network byte order
    servAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    memset(servAddr.sin_zero, '\0', sizeof(servAddr.sin_zero));

    //Connect to server 
    if (connect(sock02, (struct sockaddr *)&servAddr, sizeof(servAddr))) {
        perror("connect");
        return 2;
    }
    cout << ">> Successfully connected to server\n";

    //Now we need to create the HTTP Request and send it to the server
    httpRequest req; 
    req.set 
    //set host, etc.  
    //call buildRequest to form the message into a string as show: 
    //"GET /beej/inet_ntoaman.html http/1.1\nHOST: retran.com\n\n"
    //send that to the server 
    //server returns code 
    //client processes code 
    //server sends file 
    


}