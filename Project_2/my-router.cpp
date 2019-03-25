#include <stdio.h>
#include <string.h>
#include <stdlib.h> 
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
    char recvmsg[100];
    char sendmsg[100] = "Server Response";  
    int r, s,behav;
    struct sockaddr_in servAddr, cliAddr; 
    socklen_t len = sizeof(cliAddr); 
#include <conio.h>, SOCK_DGRAM, 0);
#include <conio.h>T, SOCK_DGRAM, 0);
#include <conio.h>
    //FOR NOW, BEHAV INDICATES HOW THE ROUTER SHOULD BEHAVE
    //Enter 0 in the command line for 'server', enter 1 for a 'client'
    behav = atoi(argv[1]); //get arguement 

   // portNum = atoi(portNum); //convert to integer 
    memset(&servAddr, 0, sizeof(servAddr));
    memset(&cliAddr, 0, sizeof(cliAddr));

    servAddr.sin_family = AF_INET;
    servAddr.sin_port = htons(portNum);     // short, network byte order
    servAddr.sin_addr.s_addr = INADDR_ANY;

    if(behav == 0){   //behav = 1 -> server 
        if(bind(sock, (const struct sockaddr *)&servAddr, sizeof(servAddr)) <0){
            perror("bind error");
            return 1; 
        }
        cout << "RECEIVE AND RESPOND\n";

        //SERVER RECEIVE 
        r = recvfrom(sock, (char *)recvmsg, 100, MSG_WAITALL, 
                    (struct sockaddr *) &cliAddr, &len);
        if(r == -1){
            perror("recv error");
        }
        cout << "Incoming Msg:" << recvmsg << endl; 
         

        //SERVER SEND RESPONSE 
        s = sendto(sock, sendmsg, 100, 0, (struct sockaddr *) &cliAddr, len);
        if(s == -1){
            perror("send error");
        }

    } else {
        //behave as a client 
        cout << "Send a message? (y)\n";
        cin >> sendmsg;
         

        //CLIENT SEND 
        s = sendto(sockc, sendmsg, 100, MSG_CONFIRM, (const struct sockaddr *) &servAddr, len);
        if(s == -1){
            perror("send error");
        }
        cout << "Message sent\n"; 

        //CLIENT RECEIVE 
        r = recvfrom(sockc, (char *)recvmsg, 100, MSG_WAITALL, (struct sockaddr *) &cliAddr, &len);
        if(r == -1){
            perror("recv error");
        }
        cout << "Response received: " << recvmsg << endl; 
    
    }
       

    close(sock);
}