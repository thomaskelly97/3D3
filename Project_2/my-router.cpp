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
#include <fstream> 

using namespace std; 


int main(int argc, char *argv[])
{    
    int portNum = 4000; 
    char recvmsg[100] = "init"; 
    char sendmsg[100]; 
    int r=0,s=0;
    struct sockaddr_in servAddr, cliAddr;
    socklen_t len = sizeof(servAddr); 

   // portNum = atoi(portNum); //convert to integer 
    int sock = socket(AF_INET, SOCK_DGRAM, 0);
    if(sock < 0){
        perror("socket error");
    }
    
    memset(&servAddr, 0, sizeof(servAddr));

    servAddr.sin_family = AF_INET;
    servAddr.sin_port = htons(portNum);     // short, network byte order
    servAddr.sin_addr.s_addr = inet_addr("127.0.0.1"); 

    cout << "Enter message to send.\n";
    cin >> sendmsg; 

    //CLIENT SEND 
    s = sendto(sock, sendmsg, 100, MSG_CONFIRM, (const struct sockaddr *) &servAddr, len);
    if(s == -1){
        perror("send error");
    }
    cout << "Message sent\n"; 

    //CLIENT RECEIVE 
    r = recvfrom(sock, (char *)recvmsg, 100, MSG_WAITALL, (struct sockaddr *) &cliAddr, &len);
    if(r == -1){
        perror("recv error");
    }
    cout << "Response received: " << recvmsg << endl; 
    
   
    
    close(sock);
}
