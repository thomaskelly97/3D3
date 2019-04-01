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
#define size 4 
using namespace std; 

class router
{
    char name; 
    int port;  
    int neighbours[size]; 

    int socks,sockc; //socket for server & client side of router 
    struct sockaddr_in servAddr, cliAddr; 
    const struct sockaddr_in * pSer = &servAddr;
    const struct sockaddr_in * pCli = &cliAddr;  
    socklen_t len; 
    socklen_t * plen = &len; 
     
    
public: 
    router(); //default constructor 
    void initialise(char n, int p, int srcNum);
    //SETTERS 
    void setName(char n);
    void setPort(int p);
    void setNeighbours(int source);
    void setAddress(int srcNum);
    void setPSER(const struct sockaddr_in addr);

    //GETTERS 
    char getN(); 
    int getP(); 
    int getANeighbour(int index);

    
    //METHODS 
    void Rsend(char msg[100]);
    void Rrecv(int pNum); 
};

#endif