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
    router r1; 
    char trymsg[100] = "hello from r1";

  
    
    r1.initialise('A', 10000, 1);
   // r2.initialise('B', 10000, 0);
    r1.Rsend(trymsg);
    //r2.Rrecv();
    return 0; 
}