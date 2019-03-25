#ifndef UDPmsg_H
#define UDPmsg_H

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

class UDPmsg
{
    char sourceP;  
    char destP; 
    int port; 
    int cost;  

    void initialise(std::char sourceP, std::char destP, int port, std::int cost);
public: 
    UDPmsg(); //default constructor 
    void setSource(char SP);
    void setDest(char DP);
    void setPort(char p);
    void setCost(char l);

    int getS();
    int getD();
    int getC();

    void createMsg();
};

#endif
