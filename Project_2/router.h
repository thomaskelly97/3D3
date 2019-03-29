#ifndef router_H
#define router_H

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
#include <vector> 

using namespace std; 

class router
{
    char name; 
    int port; 
    int behaviour; //0=server, 1=client 
    int socks,sockc; //socket for server & client side of router 
    int routerNum; 
    struct sockaddr_in servAddr, cliAddr; 
    const struct sockaddr_in * pSer = &servAddr;
    const struct sockaddr_in * pCli = &cliAddr;  
    socklen_t len; 
    socklen_t * plen = &len; 
     
    
public: 
    router(); //default constructor 
    void initialise(char n, int p, int b);
    //SETTERS 
    void setName(char n);
    void setPort(int p);
    void setB(int b);
    void setServ(struct sockaddr_in servA);
    void setCli(struct sockaddr_in cliA);
    
    //GETTERS 
    char getN(); 
    int getP(); 
    int getB();
    int getRN();  
    
    //METHODS 
    void Rsend(char msg[100]);
    void Rrecv(); 
};

#endif