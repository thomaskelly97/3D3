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
#include <pthread.h>  
#include "router.h"

#define size 3 
using namespace std; 
int threadCount =0; 
router *r = new router(); //instantiate a router 
void * threadInit(void * x);

int charToInt(char c); 

int main(int argc, char *argv[])
{    
    //we should instantiate ALL routers as 'servers' (0)
    //if a router decides it wants to SEND data, simply change its type to a client
    //using setB(1) which will set its behaviour to client. This allows it to send data
    char src,dest; 
    int port,x=0,srcNum,dstNum; 
    x++; 
    pthread_t serverT, clientT; 

    dest = *argv[1];
    src = *argv[2];
    port = atoi(argv[3]);
    srcNum = charToInt(src);
    dstNum = charToInt(dest);

    cout << "Router: " << src << "(" << srcNum << ")"<< "\nNeighbour: " << dest << "(" << dstNum << ")\n"; 

    r->initialise(src,port); // initialise router 'A' on port 10000 as a client type(1)
    pthread_create(&serverT, NULL, threadInit, &x);
    pthread_create(&clientT, NULL, threadInit, &x);

     
    pthread_join(serverT, NULL);
    pthread_join(clientT, NULL);
    return 0; 
}

void clientInit(){
    char msg[100] = "hello";
    r->Rsend(msg);
}


void serverInit(){
    r->Rrecv();
}

void * threadInit(void *x){
    int * xI = (int *) x;
    xI++;  
    threadCount++; 
    if(threadCount == 1){
        //cout << "Server thread\n";
        serverInit(); 
    } else if(threadCount == 2){
        //cout << "Client thread\n"; 
        clientInit();
    }
     

    return NULL; 
}

int charToInt(char c){
    char abc[size] = {'A','B','C'};
    for (int i =0; i< size; i++){
        if(abc[i] == c){
            return i; 
        }
    }
    return -1; 
}