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
    int r;
    socklen_t *len; 
    struct sockaddr_in servAddr, cliAddr; 
    int sock = socket(AF_INET, SOCK_DGRAM, 0);

   // portNum = atoi(portNum); //convert to integer 
    memset(&servAddr, 0, sizeof(servAddr));
    memset(&cliAddr, 0, sizeof(cliAddr));

    servAddr.sin_family = AF_INET;
    servAddr.sin_port = htons(portNum);     // short, network byte order
    servAddr.sin_addr.s_addr = htonl(INADDR_ANY); 

    if(bind(sock, (const struct sockaddr *)&servAddr, sizeof(servAddr)) <0){
        perror("bind error");
        return 1; 
    }
    cout << "Server is ready to receive\n";

    
    r = recvfrom(sock, (char *)recvmsg, 100, MSG_WAITALL, 
                (struct sockaddr *) &cliAddr, len);
    recvmsg[r] = '\0'; 
    cout << "Receiving Message.. " << recvmsg << endl << "send response\n"; 
    sendto(sock, (char *)sendmsg, 100, MSG_CONFIRM, (sockaddr *)&cliAddr, sizeof(cliAddr));
    

    close(sock);
}

