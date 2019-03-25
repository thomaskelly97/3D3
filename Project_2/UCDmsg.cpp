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
#include "UDPmsg.h"
using namespace std; 

UDPmsg::UDPmsg(){ //default constructor 
    this->initialise("10000", "10000", "10");
}

void UDPmsg::initialise(int sourceP, int destP, int cost){
    this->sourceP = sourceP;
    this->destP = destP;
    this->cost = cost;
}


void UDPmsg::setSource(int SP){
    this->sourceP = SP; 
}
void UDPmsg::setDest(int DP){
    this->destP = DP; 
}
void UDPmsg::setPort(int p){
    this->port = p; 
}
void UDPmsg::setLength(int c){
    this->cost = c; 
}

int UDPmsg::getS(){
    return this->sourceP; 
}
int UDPmsg::getD(){
    return this->destP; 
}
int UDPmsg::getPort(){
    return this->port; 
}
int UDPmsg::getC(){
    return this->cost; 
}
        
void UDPmsg::createMsg(){
    this->msg = this->sourceP + "," + this->destP + "," + this->port, + "," + this->cost + "\n";   
}



void UDPmsg::setMethod(string method){
    this->method = method; 
}
void UDPmsg::addHeader(string header){
    this->headers.push_back(header + "\r\n");
}
void UDPmsg::setHost(string host){
    this->host = host; 
}
void UDPmsg::setUri(string uri){
    this->uri = " " + uri + " "; 
}
void UDPmsg::setVer(string version){
    this->httpVer = version; 
}

void UDPmsg::createRequest(){
    this->fullRequest = this->method + this->uri + this->httpVer + "\r\n";
    this->fullRequest = this->fullRequest + this->host + "\r\n"; 
    this->fullRequest = this->fullRequest + this->parser() + "\r\n";
    this->fullRequest = this->fullRequest + "\r\n";
    cout << "Making the following request:\n====================\n" << this->fullRequest << "\n";
}

