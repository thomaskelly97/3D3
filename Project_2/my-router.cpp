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
#include "router.h"

#define size 3 //amount of nodes 

int routerNum;

using namespace std; 

int abcf(char c); 
int main(int argc, char *argv[])
{    
    //we should instantiate ALL routers as 'servers' (0)
    //if a router decides it wants to SEND data, simply change its type to a client
    //using setB(1) which will set its behaviour to client. This allows it to send data
  
   // const struct sockaddr_in addr[2][size]; //address array, stores addresses of all routers.
    char abc[3] = {'A', 'B', 'C'};  
    int ports[3] = {10000, 10001, 10002};
    
    char trymsg[100] = "hello from r1"; //use a sample message 
    char answ = 'n'; 

    char src;
    char dest;

    src = *argv[1]; 
   // int port;       //these parameters will be set by network class

    router *r = new router(); 

    r->initialise(src, 10000,0); // initialise router 'A' on port 10000 as a client type(1)
    cout << "This is router " << src << endl; 

    while(1){
        cout << "Do you want to send something?(y/n)\n"; 
        cin >> answ; 
        if(answ == 'y'){ //change to client 
            cout << "Where do you want to send it? (A, B ,C)";
            cin >> dest; 
            for(int i=0; i<size;i++){
                if(abc[i] == dest){
                    //set the 'server' address 
                    r->setPort(ports[i]);
                    r->Rsend(trymsg);
                }
            }
        } else { //stay as server 
            r->Rrecv(); 
        }
        r->setB(0); //turn it back into a server. 
    }

    return 0; 
}

int abcf(char c){
    char abc[3] = {'A', 'B', 'C'}; 
    for(int i=0; i<size; i++){
        if(abc[i] == c){
            return i; 
        }
    }
}