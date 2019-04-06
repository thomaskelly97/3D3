#ifndef Msg_H
#define Msg_H

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
#include "router.h"
#define size 7
using namespace std; 

class Msg
{
    string srcName;
    string destName;
    int destPort; 
    string data; 

    public: 
    Msg(); 

    //SETTERS 
    void setDP(int DP);
    void setDN(string DN);
    void setSN(string SN);
    void setDATA(string d);
     
    //GETTERS 
    int getDP();
    string getDN();
    string getSN();


    //METHODS 
    void createMsg();
};

#endif