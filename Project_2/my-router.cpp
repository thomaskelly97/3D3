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
#include <pthread.h>  
#include "router.h"
#include "msg.h"

#define size 7
using namespace std; 
int threadCount =0, PingthreadCount=0; 
int bothConverged =0; 
router *r = new router(); //instantiate a router 
void * threadInit(void * x);
void * pingInit(void * x);
//int nTable[size][size] = {0,1,1,0, 1,0,0,1, 1,0,0,1, 0,1,1,0}; 


pthread_t pingST, RrecvT; 

//PRABHJOT PARSER VARIABLES
 char ch[size]={'A','B','C','D','E','F','G'};												
  char name;
  int neighbour_ports[size];
  int port;                                      
  int neighbours[size];
  int link_cost[size];
  int sendcount;
////////////////////////////////////	
void parser();


int sockfd; 
int charToInt(char c); 
char src;

int main(int argc, char *argv[])
{    

    int x=0,srcNum;
    x++; 
    pthread_t serverT, clientT; 

    src = *argv[1];
    name = src; 
    
    srcNum = charToInt(src);
   // dstNum = charToInt(dest);

    parser();
    cout << "Router: " << src << "(" << srcNum <<")\n"; 

    r->initialise(src,port, srcNum); // initialise router 'A' on port 10000 as a client type(1)
    //r->setNeighbours(srcNum, neighbours); //I need to take the parsed data from this file and set it in the router.cpp file. 

    r->setparserstuff(neighbours,neighbour_ports,link_cost);
    
    cout << src << "'s neighbours: ";
    for(int ii = 0; ii<size; ii++){
        if(r->getANeighbour(ii) == 1){
            cout << ch[ii] << " "; 
        } 
    }
    
    cout << endl; 
    pthread_create(&serverT, NULL, threadInit, &x);
    pthread_create(&clientT, NULL, threadInit, &x);

    pthread_join(serverT, NULL);
    pthread_join(clientT, NULL);
    return 0; 
}

void clientInit(){
	sleep(8);
    while(!r->isupdatedsend){
    	r->dvsend();
	cout<<"out of dvsend() with sendcount= "<<sendcount<<"\n";
	if(!r->updating)
		sendcount++;
	else 
		sendcount=0;

	cout<<sendcount;
	if(sendcount>=6)
		r->isupdatedsend=true;
	}	
	r->isupdated=false;
	r->msgflag=1;
	
    cout<<"\nback in function clientInit()\n";
	r->Rsend();
}


void serverInit(){
     int count=0;    
	int x =0; 
	x++; 
	r->outputfile.open(r->filename);
    while(!r->isupdated){
    	r->dvrecv(port,src);
    

    if(!r->updating){
	count++;
	}
    else 
	count=0;

     if(count>=7){											
	r->isupdated=true;
	r->msgflag=1;
	}
	}
	
	r->outputfile.close();
  cout<<"\nback in function serverInit()\n  ";
  //in serverInit
  
 

	r->Rrecv(port,src);
}

void * threadInit(void *x){
    int * xI = (int *) x;
    xI++;  
    threadCount++; 
	
    if(threadCount == 1){
        //cout << "Server thread\n";
        serverInit(); 
    } else if(threadCount == 2){
        //cout << "Client thread\n"; 
        clientInit();
    }
    return NULL; 
}


void pingerInit(){
	//This sets up the pinger functionality 
	//We want to ping neighbours, then wait for a response. 
	int i; 
	cout << "PING THREAD\n"; 
	 

	cout << "Entering Ping Func.\n";
		
	r->ping(); 
	
}

void RrecvInit(){
	r->Rrecv(port,src); //runs the Rrecv function as normal... 
}


void * pingInit(void *x){
    int * xI = (int *) x;
    xI++;  
    PingthreadCount++; 
	
    if(PingthreadCount == 1){
        //cout << "Server thread\n";
		RrecvInit();
    } else if(PingthreadCount == 2){
        //cout << "Client thread\n"; 
        pingerInit(); 
    }
    return NULL; 
}

int charToInt(char c){
    for (int i =0; i< size; i++){
        if(ch[i] == c){
            return i; 
        }
    }
    return -1; 
}


//PARSES TOPOLOGY FILES 
//Each router stores its neighbour in the object->neighbours array 
//
void parser(){
//parses sample.txt to get myport port of neighbours and link cost for neighbours
	//will have to change the function signature when adding to router class .. either to void function_name()
	//or void function_name(char name) if u want to pass the name 	

	string name_string="";
	name_string+=name;
	string line;	
	//int get_port_from; //seems unused so I'm commenting it out.... 
	bool got_port=false;
	ifstream myfile("newsample.txt");										//file with initial info goes here
	int x=0,y,z=0,cost,flag=1,i=0,j=0;
	x++; x=0; z++; z=0; 
	string x_string="",y_string="",z_string="",cost_string="";


	for(int i=0;i<7;i++){
		link_cost[i]=-1;
		neighbours[i]=0;
		neighbour_ports[i]=-1;
	}



	while(getline(myfile,line)){
	flag=1;
	i=0;j=0;x_string="";y_string="";z_string="",cost_string="";
	char* a = (char*)line.c_str();
	char currchar=a[i];
		while(flag<5&&currchar==name){
			
			if(a[i]==','){
				i++;
				j++;
					if(j==1){
							flag++;
							x=(int)(x_string.c_str()[0] -'A');
						}
					if(j==2){
							flag++;
							y=(int)(y_string.c_str()[0]-'A');
							neighbours[y]=1;
						}

					if(j==3){
							flag++;
							if(!got_port){
							port = stoi(z_string);
							got_port=true;
						}
						}
				}
			
			if(a[i]<0){
				flag++;
				cost=stoi(cost_string);
				link_cost[y]=cost;
				}
	
			switch(flag)
			{	
				case 1: x_string+=a[i++];break;
				case 2: y_string+=a[i++];break;
				case 3: z_string+=a[i++];break;
				case 4: cost_string+=a[i++];break;

			} 
				
				
		}

		for(int forcounter=0;forcounter<7;forcounter++){
			char currneighbour;
			if(neighbours[forcounter]==1)
				currneighbour=forcounter;
			else currneighbour=-1;
		if((int)(currchar-'A')==currneighbour){
			while(j<3){
				
				if(a[i]==','){
					i++;				
					j++;
				}
				if(j==1){
					y_string+=a[i];
					}
					
				else if(j==2){
					z_string+=a[i];
					}
				i++;
				}
				
				if(j==3)
				neighbour_ports[forcounter]=stoi(z_string);
			

		}
	}

		if(a[2]==name&&!neighbours[(int)(currchar-'A')]){
			while(j<3){

				if(a[i]==','){
					i++;				
					j++;
				}
				if(j==0){
					y_string+=a[i];
					y=(int)(y_string.c_str()[0]-'A');
					i++;				
					}
				else if(j==1){
					i++;
					}	
				else if(j==2){
					z_string+=a[i];
					i++;					
					}
				
				
				}
				if(j==3)
				neighbour_ports[y]=stoi(z_string);
				cout<<"for "<<y<<": "<<neighbour_ports[y]<<"\n";
				while(!(a[i]<0)){
					cost_string+=a[i++];
					}
				//cost=stoi(cost_string);
				//link_cost[y]=cost;
				}

	}

	//neighbour_ports[(int)(name-'A')] = port;
	neighbours[(int)(name-'A')]=-1;
	cout<<"port(" << port<<"\n" ;//<< "): "<<port<<", neighbours of " << src << ": ";
//		for(i=0;i<7;i++){

//		if(neighbours[i]){
//			cout<<ch[i]<<",link cost: "<<link_cost[i]<<", port: "<<neighbour_ports[i]<<"\n";	
//		}

//		}
}
