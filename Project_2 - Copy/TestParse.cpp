#include <iostream>
#include <string>
#include <fstream>
#include "router.h"
using namespace std;

#define MAXROUTERS  20

bool RouterExists(char RName);
void AddRouter(char RName, char DName, int Port, int cost);
void PrintRouters();
void RemoveRouter(char RName);


int main()
{
    string inputfilename = "Graph_Inputs.txt";
    fstream inputfile;
    inputfile.open(inputfilename, ios::in);

    //Create
    char buf;
    char RName, DName;
    int Port, cost;
    char PortC[10];
    int i;
    
    if (!inputfile) {
        cout << "Unable to open input file";
    }

    //Else parse whole file
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

            Port = stoi(PortC);

            //Parse Cost
            inputfile.get(buf);
            cost = stoi(&buf);
            inputfile.get(buf);

            //If router doesn't exist, make Router
            if(!RouterExists(RName)){
                cout << "\nWill Add Router " << RName << endl;
                AddRouter(RName, DName, Port, cost);
            }
            else if(!RouterExists(DName)){
                cout << "\nWill Add Router " << RName << endl;
                AddRouter(DName, RName, Port, cost);
            }
        }
    }
    i = 0;

    cout <<endl;
    PrintRouters();
    RemoveRouter('E');
    PrintRouters();

    return 0;
}

//Needs to be changed to be able to check the Router.getN()
bool RouterExists(char RName){
    bool exists = false;
    int i = 0;

    while(routers[i]){
    if(RName == routers[i]){
        exists = true; break;
    }
    else 
        i++;
    }
    return exists;
}

//Needs to be changed to add Router objects to a string
void AddRouter(char RName, char DName, int Port, int cost){
    
    int i = 0;

    while(routers[i]){//Go to last router
        i++;
    }
    if(i > MAXROUTERS){
        cout << "\nMAX routers reached !";
    }
    else{
        //Create router & add it to the list
        routers[i] = RName; 
        cout << "Added router " << routers[i] <<endl;
    }
}

void RemoveRouter(char RName){
    int i = 0;
    cout << "\nRemoving router " << RName << "\n";
    
    while(routers[i] != RName){
        i++;
    }
    
    while(routers[i+1]){
        routers[i] = routers[i+1];
        i++;
    }
    routers[i] = ' ';
}

void PrintRouters(){
    int i = 0;
    while(routers[i]){
        cout << " " << routers[i];
        i++;
    }
}