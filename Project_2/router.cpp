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

int nTable[size][size] = {0,1,1,0, 1,0,0,1, 1,0,0,1, 0,1,1,0};  //this will have to be updated upon network initialisation 
int ports[size] = {10000,10001,10002,10003}; //in reality this will be read in and parsed from above layer. 

router::router(){ //default constructor 
    this->name = ' '; 
    this->port = 10000; 
    for(int i =0; i< size; i++){
        this->neighbours[i] = 0; 
    } 
}

void router::initialise(char n, int p, int srcNum){ // initialises address settings 
    this->name = n;
    this->port = p;
    int oo=1;
    for(int i =0; i< size; i++){
        this->neighbours[i] = 0; 
    }

    memset(&servAddr, 0, sizeof(servAddr));
    memset(&cliAddr, 0, sizeof(cliAddr));

    this->servAddr.sin_family = AF_INET;
    this->servAddr.sin_port = htons(p);     
    this->servAddr.sin_addr.s_addr = INADDR_ANY;
    //addresses[srcNum] = this->servAddr; 
    this->len = sizeof(this->cliAddr); 
    this->sockc = socket(AF_INET, SOCK_DGRAM, 0);
    this->socks = socket(AF_INET, SOCK_DGRAM, 0);
    if (setsockopt(sockc, SOL_SOCKET, SO_REUSEADDR, &oo, sizeof(int)) < 0){
        perror("setsockopt(SO_REUSEADDR) failed");
    } 
    if (setsockopt(socks, SOL_SOCKET, SO_REUSEADDR, &oo, sizeof(int)) < 0){
        perror("setsockopt(SO_REUSEADDR) failed");
    }
   // cout << "\n\nRouter Name: "<< this->name << "\nPort: " << this->port << endl; 
}

//SETTERS 
void router::setName(char n){
    this->name = n; 
}

void router::setPort(int p){
    this->port = p; 
}

void router::setNeighbours(int source){
    //char abc[4] = {'A','B','C','D'};
    for(int i = 0; i<size; i++){
        for(int j = 0; j< size ;j++){
            if(source == i && nTable[source][j] == 1){
                //found a neighbour 
                this->neighbours[j] = 1; 
                //cout << abc[j] << " is a neighbour.\n"; 
            }
        }
    }
}

//GETTERS 
char router::getN(){
    return this->name; 
}

int router::getP(){
    return this->port; 
}

int router::getANeighbour(int index){
    return this->neighbours[index]; 
}


void router::Rsend(char msg[100]){    
    //CLIENT SEND 
    bool update = true; 
    char answ; 
    cout << "Client thread running - Any key to proceed\n";
    cin>> answ; 
    char recvmsg[100]; //receive buffer 
    int s,r; 
    //const struct sockaddr_in * temp;
    while(1){
        cin >> answ; 
        for(int i = 0; i<size; i++){
            
            if(this->neighbours[i] == 1 && update == true){//if something is a neighbour, send to it
                //we can now use the i
                cout << "CLIENT-Found neighbour " << i << " on port " << ports[i] << "..attempting send"<< endl;  

            //  this->setPSER(addresses[i]);
                s = sendto( (this->socks), msg, 100, MSG_CONFIRM, ( struct sockaddr *)(this->pSer), (this->len));
                cout << "CLIENT-Message sent, awaiting response."<< endl << endl; 
        }
        }
        
        if(s == -1){
            perror("send error");
        }
        

            //CLIENT RECEIVE 
            r = recvfrom(this->sockc, (char *)recvmsg, 100, MSG_WAITALL, 
                (struct sockaddr *)(this->pSer), this->plen);    if(r == -1){
            perror("recv error");
        }
        cout << "Client receiving response: " << recvmsg << endl; 
        }
}

void router::Rrecv(int pNum, char src){
    char recvmsg[100]; 
    char sendmsg[100];
    char abc[size] = {'A','B','C','D'};
    sprintf(sendmsg, "Server Response from %c" , src);;
    int r,s; 
    cout << "Server thread running\n";
    memset(&servAddr, 0, sizeof(servAddr));
    memset(&cliAddr, 0, sizeof(cliAddr));

    this->servAddr.sin_family = AF_INET;
    this->servAddr.sin_port = htons(pNum);     
    this->servAddr.sin_addr.s_addr = INADDR_ANY;  
    if(bind(this->socks, (const struct sockaddr *)(this->pSer), sizeof(this->servAddr)) <0){
        perror("bind error"); 
    }
    
    while(1){
    //SERVER RECEIVE 
    cout << "SERVER-Waiting to receive...\n";
        r = recvfrom(this->socks, (char *)recvmsg, 100, MSG_WAITALL, 
                        (struct sockaddr *)(this->pCli), this->plen);
        if(r == -1){
            perror("recv error");
        }
        cout << "Server receives " << recvmsg << "...sending response "<<   endl; 
            

        //SERVER SEND RESPONSE 
        for(int i =0; i<size; i++){
            if(this->neighbours[i] == 1){
                cout << "I am " << src << " sending to " << abc[i] << endl;
                s = sendto(this->sockc, sendmsg, 100, 0, (const struct sockaddr *)(this->pCli), this->len);
                if(s == -1){
                    perror("send error");
                }
            }
        }
    }
}


void router::setPSER(const struct sockaddr_in addr){
    this->pSer = &addr; 
}