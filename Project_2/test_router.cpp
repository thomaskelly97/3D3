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
    //Test router. Set up as type server 
    //ideally all routers will be setup by an init_router file, and each router sets its own parameters in the my-router.cpp.
    router r2; 
    r2.initialise('B', 10000, 0);
    r2.Rrecv();

    return 0; 
}