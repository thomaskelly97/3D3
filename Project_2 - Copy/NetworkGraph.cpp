
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
#include "router.cpp"
#include <fstream> 
#include "NetworkGraph.h"

using namespace std; 

NetworkGraph::NetworkGraph()
{
    this->inputfilename = "Graph_Inputs.txt";
}

void NetworkGraph::CreateNetworkGraph()
{
    ifstream inputfile;
    inputfile.open(this->inputfilename);//Doesn't like this

    //Create
    char buf;
    char RName, DName;
    int Port, cost;
    char PortC[10];
    int i;
    
    if (!inputfile) {
        cout << "Unable to open input file";
    }

    // Else parse whole file
    else{ 
        while(!inputfile.eof())
        {            
            //Parse Source Name
            inputfile.get(buf);            
            RName = buf;
            inputfile.get(buf);

            //Parse Dest Name
            inputfile.get(buf);
            DName = buf;
            i = 0;
            inputfile.get(buf);
            inputfile.get(buf);

            //Parse Port no
            while(buf != ','){
                PortC[i] = buf;
                i++;                
                inputfile.get(buf);
            }            

            Port = atoi(PortC);

            //Parse Cost
            inputfile.get(buf);
            cost = (int)buf;
            inputfile.get(buf);

            //If router doesn't exist, make Router
            if(!NetworkGraph::RouterExists(RName)){
                cout << "\nWill Add Router " << RName << endl;
                NetworkGraph::AddRouter(RName, DName, Port, cost);
            }
            
            if(!NetworkGraph::RouterExists(DName)){
                cout << "\nWill Add Router " << DName << endl;
                NetworkGraph::AddRouter(DName, RName, Port, cost);
            }
        }
    }
    i = 0;

    cout << endl;
    while(this->Routers){
        //EDIT 
        cout << this->Routers[i] << " ";
        i++;
    }
}

bool NetworkGraph::RouterExists(char RName){
    bool exists = false;
    int i = 0;

    while(this->Routers){
        if(RName == this->Routers[i]){
            exists = true; break;
        }
        else 
            i++;
    }
    return exists;
}


//Needs to be changed to add Router objects to a string
void NetworkGraph::AddRouter(char RName, char DName, int Port, int cost){
    
    int i = 0;

    while(this->Routers[i]){//Go to last router
        i++;
    }
    if(i > MAXROUTERS){
        cout << "\nMAX routers reached !";
    }
    else{
        //Create router & add it to the list        
        //Need to delete the behaviour after it's changed!!!
        // router newrouter;
        // newrouter.initialise(RName, Port, 0);
        this->Routers[i] = RName;
    }
}