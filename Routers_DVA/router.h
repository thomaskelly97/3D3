#ifndef router_H
#define router_H

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
#include <fstream>
#define size 7
using namespace std; 



class router
{
    char name; //set in main of my-router
    int port;  //set in initialize()
    int neighbours[size];   // set in setparserstuff()
    int costToNeighbour[size];  // set in setparserstuff()                     //change this name to costTo()
    int destVia[size];  // set in setparserstuff()
    int portForNeighbour[size];  // set in setparserstuff()
    int socks,sockc; //socket for server & client side of router 
    struct sockaddr_in servAddr, cliAddr; 
    const struct sockaddr_in * pSer = &servAddr;
    const struct sockaddr_in * pCli = &cliAddr;  
    socklen_t len; 
    socklen_t * plen = &len; 
    int iterations_without_update;
    string filename;
    ofstream outputfile;
public: 
    router(); //default constructor 
    int msgflag;     // 0 for dvs 1 for normal message and 2 for update dvs
    bool updating; //reciving for updates
    bool isupdated;  //if table got updated
    bool dvsendready; //dv is send ready

    int dvrecved[20];

    void initialise(char n, int p, int srcNum);
    //SETTERS 
    void setName(char n);
    void setPort(int p);
    void setNeighbours(int source, int n[]);
    void setAddress(int srcNum);
    void setPSER(const struct sockaddr_in addr);
    void setparserstuff(int neighbours[size],int neighbour_ports[size],int link_cost[size]);   //set neighbours,CTN,DV,PFN etc.
    //GETTERS 
    char getN(); 
    int getP(); 
    int getANeighbour(int index);
    
    //METHODS 
    void Rsend(char msg[100]);
    void Rrecv(int pNum, char src); 
    void dvsend();
    void dvrecv(int pNum,char src);
    void updatetables();
    void writeToFile();
};

#endif