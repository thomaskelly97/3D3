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
        this->data = "";
        this->srcName = ""; 
        this->destName = ""; 
        this->destPort = -1;  
        this->msg= "";
    }


    void Msg::createMsg(){
        //MESSAGE FORMAT: [SRC,DEST,whiitespaces for route,DATA]
        //                [2  , 4   , 5-9   , 100]
        string portAsStr = to_string(this->destPort);
        this->data += "i";
	this->data += " " +this->srcName +" "+ this->destName+"000000" +" "+ this->msg + "\n";
        cout << "PACKET: " << this->data << endl; 
        cout<< "data.c_str()[2]: "<<data.c_str()[2];
        cout<< "\ndata.c_str()[4]: "<<data.c_str()[4];
        cout<< "\ndata.c_str()[5]: "<<data.c_str()[5];
        cout<< "\ndata.c_str()[9]: "<<data.c_str()[9]<<" ";
        cout<< "\nlength: "<<sizeof(this->msg)<<"\n";
        
    }



    //SETTERS 
    void Msg::setDN(string DN){
        this->destName = DN; 
        cout<<"set destName to "<<destName<<"\n";
    }
    void Msg::setSN(string SN){
        this->srcName = SN; 
        cout<<"set srcName to "<<srcName<<"\n";
    }
    void Msg::setDATA(string d){
        this->msg = d; 
        cout<<"set data to "<<data<<"\n";
    }
     
    //GETTERS 

    string Msg::getDN(){
        return this->destName; 
    }
    string Msg::getSN(){
        return this->srcName; 
    }
    string Msg::getDATA(){
        return (this->data); 
    }
