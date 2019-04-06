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

using namespace std; 

class Msg
{
    char msg[100];
     
    
public: 
    Msg();
    void initialise(char Source, char Dest);
    
    //GETTERS 
    char* getMsg(); 
};

#endif