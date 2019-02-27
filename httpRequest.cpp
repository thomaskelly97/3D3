#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <iostream>
#include <sstream> 
#include <errno.h> 
#include <unistd.h> 
using namespace std; 

httpRequest::httpRequest(){ //default constructor 
    this->initialise("GET", "127.0.0.1", "/");
}

void httpRequest::initialise(string method, string host, string uri){
    this->method = method;
    this->host = host;
    this->uri = " " + uri + " ";
}

 

void httpRequest::setMethod(string method){
    this->method = method; 
}
void httpRequest::addHeader(string header){
    this->headers.push_back(header + "\r\n");
}
void httpRequest::setHost(string host){
    this->host = host; 
}
void httpRequest::setUri(string uri){
    this->uri = " " + uri + " "; 
}
void httpRequest::createRequest(){
    //this->fullRequest = this->method + this->uri + this->httpVer + "\r\n";
    this->fullRequest = this->fullRequest + this->host + "\r\n"; 
    //this->fullRequest = this->fullRequest + this->parsedHead() + "\r\n";
    this->fullRequest = this->fullRequest + "\r\n";
}
int httpRequest::getLength(){
    return this->fullRequest.length(); 
}
string httpRequest::getHost(){
    return this->host; 
}
string httpRequest::convert(){
    return this->fullRequest; 
}

