#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <string> 
#include <iostream>
#include <sstream> 
#include <errno.h> 
#include <unistd.h> 
#include "router.h"
using namespace std; 

router::router(){ //default constructor 
    this->name = ' '; 
    this->port = 10000; 
    this->behaviour = 0; 
}

void router::initialise(char n, int p, int b){ // initialises address settings 
    this->name = n;
    this->port = p;
    this->behaviour = b; 

    memset(&servAddr, 0, sizeof(servAddr));
    memset(&cliAddr, 0, sizeof(cliAddr));

    this->servAddr.sin_family = AF_INET;
    this->servAddr.sin_port = htons(this->port);     
    this->servAddr.sin_addr.s_addr = INADDR_ANY;

    this->len = sizeof(this->cliAddr); 
    this->sockc = socket(AF_INET, SOCK_DGRAM, 0);
    this->socks = socket(AF_INET, SOCK_DGRAM, 0);

    cout << "\n\nInitialised router. Port:" << this->port << endl << "Name: " << n <<
    " - behaving as a " << b << " - (0 denotes server behaviour, 1 for client)\n"; //debug info 
}

//SETTERS 
void router::setName(char n){
    this->name = n; 
}

void router::setPort(int p){
    this->port = p; 
}
void router::setB(int b){
    this->behaviour = b; 
}

//GETTERS 
char router::getN(){
    return this->name; 
}

int router::getP(){
    return this->port; 
}
int router::getB(){
    return this->behaviour; 
}

void router::Rsend(char msg[100]){    
    //CLIENT SEND 
    cout << "SEND AND RECEIVE RESPONSE (client behaviour)\n";
    char recvmsg[100]; //receive buffer 
    int s,r; 
    
    s = sendto( (this->sockc), msg, 100, MSG_CONFIRM, ( struct sockaddr *)(this->pSer), (this->len));
    if(s == -1){
        perror("send error");
    }
    cout << "Message sent -[ " << msg << " ]-" << endl; 

        //CLIENT RECEIVE 
    r = recvfrom((this->sockc), (char *)recvmsg, 100, MSG_WAITALL, ( struct sockaddr *)(this->pCli), this->plen);
    if(r == -1){
        perror("recv error");
    }
    cout << "Receiving Response: " << recvmsg << endl; 
}

void router::Rrecv(){
    char recvmsg[100]; 
    char sendmsg[100] = "this is the server response";
    int r,s; 
    if(bind(this->socks, (const struct sockaddr *)(this->pSer), sizeof(this->servAddr)) <0){
        perror("bind error"); 
    }
    cout << "RECEIVE AND RESPOND (server behaviour)\n";

    //SERVER RECEIVE 
    r = recvfrom(this->socks, (char *)recvmsg, 100, MSG_WAITALL, 
                     (struct sockaddr *)(this->pCli), this->plen);
    if(r == -1){
        perror("recv error");
    }
    cout << "Receiving Msg -[ " << recvmsg << " ]- ...sending response -[ "<<sendmsg<< " ]-" << endl; 
         

    //SERVER SEND RESPONSE 
    s = sendto(this->socks, sendmsg, 100, 0, (const struct sockaddr *)(this->pCli), this->len);
    if(s == -1){
        perror("send error");
    }
}