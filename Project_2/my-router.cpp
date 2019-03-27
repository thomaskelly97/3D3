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


using namespace std; 

int main(int argc, char *argv[])
{    
    //we should instantiate ALL routers as 'servers' (0)
    //if a router decides it wants to SEND data, simply change its type to a client
    //using setB(1) which will set its behaviour to client. This allows it to send data
   

    router r1; //instantiate a router 
    char trymsg[100] = "hello from r1"; //use a sample message 

    r1.initialise('A', 10000, 1); // initialise router 'A' on port 10000 as a client type(1)
    r1.Rsend(trymsg); //send message 
    
    return 0; 
}