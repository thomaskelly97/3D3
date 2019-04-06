
// #include <stdio.h>
// #include <string.h>
#include <stdlib.h>
// #include <sys/types.h>
// #include <sys/socket.h>
// #include <netdb.h>
// #include <arpa/inet.h>
// #include <netinet/in.h>
#include <string> 
#include <iostream>
// #include <errno.h> 
// #include <unistd.h> 
// #include <vector> 
// #include "router.h"
#include <fstream> 
#include <stdio.h>

// #include "NetworkGraph.h"
// #include "NetworkGraph.cpp"

using namespace std; 

void AddRouter(char RName, char DName, int Port, int cost);
bool RouterExists(char RName);

#define MAXROUTERS 10

char Routers[MAXROUTERS];

int main(){

    ifstream inputfile;
    inputfile.open("Graph_Inputs.txt");//Doesn't like this

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
            // //Parse Source Name
            // inputfile.get(buf);            
            // RName = buf;
            // inputfile.get(buf);            

            // //Parse Dest Name
            // inputfile.get(buf);
            // DName = buf;
            // i = 0;
            // inputfile.get(buf);
            // inputfile.get(buf);
            i = 0;
            // //Parse Port no
            // while(buf != ','){
            //     PortC[i] = buf;
            //     i++;                
            //     inputfile.get(buf);
            // }            

            // Port = atoi(PortC);

            // //Parse Cost
            // inputfile.get(buf);
            // cost = buf- '0';
            // inputfile.get(buf);

            // //If router doesn't exist, make Router
            // if(!RouterExists(RName)){
            //     cout << "\nWill Add Router " << RName << endl;
            //     AddRouter(RName, DName, Port, cost);
            // }
            
            // if(!RouterExists(DName)){
            //     cout << "\nWill Add Router " << DName << endl;
            //     AddRouter(DName, RName, Port, cost);
            // }
            inputfile.get(buf);
            RName = buf;
            inputfile.get(buf);
            inputfile.get(buf);

            DName = buf;
            inputfile.get(buf);
            inputfile.get(buf);

            //Parse Port no
            while(buf != ','){
                PortC[i] = buf;
                i++;                
                inputfile.get(buf);
            } 
            
            Port = atoi(PortC);
            inputfile.get(buf);
            cost = buf;
            cout << "\n" << RName << DName << Port << cost;
            inputfile.get(buf);
            
        }
    }
    i = 0;

    // cout << endl;
    // while(Routers[i]){
    //     //EDIT 
    //     cout << Routers[i] << " ";
    //     i++;
    // }
    return 0;
}


bool RouterExists(char RName){
    bool exists = false;
    int i = 0;

    while(Routers[i]){
        if(RName == Routers[i]){
            exists = true; break;
        }
        else 
            i++;
    }
    return exists;
}

//Needs to be changed to add Router objects to a string
void AddRouter(char RName, char DName, int Port, char cost){
    
    int i = 0;

    while(Routers[i]){//Go to last router
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
        Routers[i] = RName;
        cout << "\nAdded " << Routers[i];

    }
}