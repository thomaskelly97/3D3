#include "Msg.h"
#include "router.h"

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
#define size 7

    Msg::Msg(){
        this->data = " ";
        this->srcName = "A"; 
        this->destName = "B"; 
        this->destPort = 10000;  
         
    }


    void Msg::createMsg(){
        //MESSAGE FORMAT: [SRC,DEST,PORT,DATA]
        //                [1  , 1   , 5   , 100]
        string portAsStr = to_string(this->destPort);
        this->data = this->srcName + "," + this->destName + "," + portAsStr + "," + this->data + "\n";
        cout << "PACKET: " << this->data; 
    }



    //SETTERS 
    void Msg::setDP(int DP){
        this->destPort = DP; 
    }
    void Msg::setDN(string DN){
        this->destName = DN; 
    }
    void Msg::setSN(string SN){
        this->srcName = SN; 
    }
    void Msg::setDATA(string d){
        this->data = d; 
    }
     
    //GETTERS 
    int Msg::getDP(){
        return this->destPort;
    }
    string Msg::getDN(){
        return this->destName; 
    }
    string Msg::getSN(){
        return this->srcName; 
    }

