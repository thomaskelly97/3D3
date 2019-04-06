#ifndef NetworkGraph_H
#define NetworkGraph_H
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <string> 
#include <iostream>
#include <errno.h> 
#include <unistd.h> 
#include <vector> 
#include "router.h"
#include <fstream> 


#define MAXROUTERS 20

using namespace std; 

class NetworkGraph
{

    private:
    const char* inputfilename;   
    char Routers[MAXROUTERS];
    
    public: 
    NetworkGraph();
    
    //Functions
    void CreateNetworkGraph();
    bool RouterExists(char RName);
    void AddRouter(char RName, char DName, int Port, int cost);
    // void SendTraffic();
    
};

#endif
