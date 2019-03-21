#ifndef httpRequest_H
#define httpRequest_H

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

class httpRequest
{
    string method;  
    string host; 
    string httpVer; 
    string uri; 
    vector<string> headers; 
    string parsedHead; 
    string fullRequest; 
    
    void initialise(std::string method, std::string host, std::string uri);
    string parser();

public: 
    httpRequest(); //default constructor 
    void setMethod(string method);
    void addHeader(string header);
    void setHost(string host);
    void setUri(string uri);
    void setVer(string version);
    void createRequest();
    int getLength();
    std::string getHost();
    std::string convert(); 
};

#endif
