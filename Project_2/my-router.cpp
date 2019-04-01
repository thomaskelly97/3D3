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

#define size 6
using namespace std; 
int threadCount =0; 
router *r = new router(); //instantiate a router 
void * threadInit(void * x);
//int nTable[size][size] = {0,1,1,0, 1,0,0,1, 1,0,0,1, 0,1,1,0}; 
char abc[size] = {'A','B','C','D','E','F'};

int sockfd; 
int charToInt(char c); 
int port; 
char src;

int main(int argc, char *argv[])
{    

    int x=0,srcNum;
    //dstNum; 
    x++; 
    pthread_t serverT, clientT; 
    /*
   // const struct sockaddr_in addr; 
    //int sockfd = socket(AF_INET, SOCK_DGRAM, 0);


    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &oo, sizeof(int)) < 0){
        perror("setsockopt(SO_REUSEADDR) failed");
    }

    memset(addr.sin_zero, '\0', sizeof(addr.sin_zero));

    this->servAddr.sin_family = AF_INET;
    this->servAddr.sin_port = htons(p);     
    this->servAddr.sin_addr.s_addr = inet_pton("127.0.0.1");;
   */
    src = *argv[1];
    port = atoi(argv[2]);
    srcNum = charToInt(src);
   // dstNum = charToInt(dest);

    cout << "Router: " << src << "(" << srcNum <<")\n"; 

    r->initialise(src,port, srcNum); // initialise router 'A' on port 10000 as a client type(1)
    r->setNeighbours(srcNum);
    //r->setAddress(srcNum);
    cout << src << "'s neighbours: ";
    for(int ii = 0; ii<size; ii++){
        if(r->getANeighbour(ii) == 1){
            cout << abc[ii] << " "; 
        } 
    }
    
    cout << endl; 
    pthread_create(&serverT, NULL, threadInit, &x);
    pthread_create(&clientT, NULL, threadInit, &x);

    pthread_join(serverT, NULL);
    pthread_join(clientT, NULL);
    return 0; 
}

void clientInit(){
    char msg[100];
    sprintf(msg, "hello from %c" , src);
    r->Rsend(msg);
}


void serverInit(){
    r->Rrecv(port,src);
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
    char abc[size] = {'A','B','C','D','E','F'};
    for (int i =0; i< size; i++){
        if(abc[i] == c){
            return i; 
        }
    }
    return -1; 
}