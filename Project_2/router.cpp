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
#include <chrono> 
#include <ctime> 
#include "router.h"
#include "Msg.h"
using namespace std; 

//int nTable[size][size] = {0,1,0,0,1,0, 1,0,1,0,1,1, 0,1,0,1,0,1, 0,0,1,0,0,1,  1,1,0,0,0,1, 0,1,1,1,1,0};  //this will have to be updated upon network initialisation 
//Group6; Thomas Kelly, Prabhjot Singh, Naoise Myler



router::router(){ //default constructor 
    this->name = ' '; 
    this->port = 10000; 
    for(int i =0; i< size; i++){
        this->neighbours[i] = 0; 
    } 
    
}

void router::initialise(char n, int p, int srcNum){ // initialises address settings 
    this->name = n;
    this->port = p;
    int oo=1;
    for(int i =0; i< size; i++){
        this->neighbours[i] = 0; 
    }
    this->isupdated=false;
    iterations_without_update=0;
    this->updating=true;
    memset(&servAddr, 0, sizeof(servAddr));
    memset(&cliAddr, 0, sizeof(cliAddr));

    this->servAddr.sin_family = AF_INET;
    this->servAddr.sin_port = htons(p);     
    this->servAddr.sin_addr.s_addr = INADDR_ANY;
    //addresses[srcNum] = this->servAddr; 
    this->len = sizeof(this->cliAddr); 
    this->sockc = socket(AF_INET, SOCK_DGRAM, 0);
    this->socks = socket(AF_INET, SOCK_DGRAM, 0);
    if (setsockopt(sockc, SOL_SOCKET, SO_REUSEADDR, &oo, sizeof(int)) < 0){
        perror("setsockopt(SO_REUSEADDR) failed");
    } 
    if (setsockopt(socks, SOL_SOCKET, SO_REUSEADDR, &oo, sizeof(int)) < 0){
        perror("setsockopt(SO_REUSEADDR) failed");
    }

    filename="";
    filename+="router";
    filename+=this->name;  
    filename+="OutputStream.txt";
    this->outputfile.open(filename);
    
    this->outputfile<<"**this file is updated when router table for "<<this->name<<" is changed**\n";

    this->outputfile.close();
    this->msgflag=-1;

   // cout << "\n\nRouter Name: "<< this->name << "\nPort: " << this->port << endl; 
    if(bind(this->socks, (const struct sockaddr *)(this->pSer), sizeof(this->servAddr)) <0){
        perror("bind error"); 
    }


}

//SETTERS 
void router::setName(char n){
    this->name = n; 
}

void router::setPort(int p){
    this->port = p; 
}

void router::setNeighbours(int source, int n[]){
    //char abc[4] = {'A','B','C','D'};
    for(int i = 0; i<size; i++){
        if(n[i] == 1){
            this->neighbours[i] = 1; //set as a neighbour 
        }
    }
}

//GETTERS 
char router::getN(){
    return this->name; 
}

int router::getP(){
    return this->port; 
}

int router::getANeighbour(int index){
    return this->neighbours[index]; 
}


void router::Rsend(){    
    //CLIENT SEND 
    char msg[100];                     
   // bool update = true; 
    char answ; 

    struct sockaddr_in addr; 
    socklen_t len = sizeof(addr); 

    
    addr.sin_family = AF_INET;  
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    memset(addr.sin_zero, '\0', sizeof(addr.sin_zero));

    //cout << "Client thread running - Any key to proceed\n";
    
    char recvmsg[100] = {0}; //receive buffer 
    int s;
    //,r; 
    //const struct sockaddr_in * temp;
    


   int via = destVia[(int)(recvmsg[0]-'A')];    //recvmsg[0] is destination , recvmsg[1] is source...

	//cout<<"IN FUNCTION RSEND\n";
        cin >> answ; 
      //  for(int i = 0; i<size; i++){
            
            if(this->neighbours[via] == 1 ){//if something is a neighbour, send to it
                //we can now use the i
                addr.sin_port = htons(portForNeighbour[via]);
               // cout << "CLIENT-Found neighbour " << via << " on port " << portForNeighbour[via] << "..attempting send"<< endl;  

            //  this->setPSER(addresses[i]);
                s = sendto( (this->socks), msg, 100, MSG_CONFIRM, ( struct sockaddr *)&addr, len);
                //cout << "CLIENT-Message sent, awaiting response."<< endl << endl; 
 	       }
        //}
        
        if(s == -1){
            perror("send error");

        }
	      // cout << "CLIENT- receiving response: " << recvmsg << endl; 
 
}
void router::dvsend(){    
    //CLIENT SEND 
    //char ch[size]={'A','B','C','D','E','F','G'};
    bool update = true; 
    //char answ; 

    struct sockaddr_in addr; 
    socklen_t len = sizeof(addr); 
    int s; 
    int msg[100];
	msg[0]=(int)(name-'A');
    string msgDest; 
    string actualMsg; 
    string msgSrc;
    string srcMsgN = "" + this->name; 
    //int msgDI; 
	Msg *m = new Msg();
    for(int forcounter=1;forcounter<size+1;forcounter++)
	{	
		msg[forcounter]=portForNeighbour[forcounter-1];
		msg[forcounter+size]=costToNeighbour[forcounter-1];
	//	cout<<(forcounter-1)<<" ,port: "<<portForNeighbour[forcounter-1]<<" ,cost: "<<costToNeighbour[forcounter-1]<<"\n";
	//	cout<<(forcounter)<<",msg: "<<msg[forcounter]<<",msg+size: "<<msg[forcounter+size]<<"\n";	
	}
    
	//cout<<"**about to send**"<<msg<<"\n";

    addr.sin_family = AF_INET;  
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    memset(addr.sin_zero, '\0', sizeof(addr.sin_zero));
    
    if(this->name == 'G'){ //if this is node G, user has specified for message injection to occur 
        int ports[size] = {10000,10001,10002,10003,10004, 10005};
        const char *inject_msg;
        string inj_msg; 
        cout << "\nMESSAGE INJECTOR RUNNING\n"; //message will be hardcoded to be sent to A 
        cout << "Where do you want to send from?\n"<<endl;
        cin >> msgSrc; 
        cout << "Where do you want to send to?\n"<<endl;
        cin >> msgDest; 
        cout << "Enter message to send:\n"<<endl;
        cin >> actualMsg; 
        
            
        m->setSN(msgSrc);
        m->setDN(msgDest);
        m->setDATA(actualMsg);
        m->createMsg();
        inj_msg = m->getDATA();
        inject_msg = inj_msg.c_str(); 
 
        //cout<<(int)(msgDest.c_str()[0]-'A');
        //cout<<"\n";
        cout<<inject_msg<<"\n";
        addr.sin_port = htons(ports[(int)(msgSrc.c_str()[0]-'A')]); 
        s = sendto( (this->socks), inject_msg, 100, MSG_CONFIRM, ( struct sockaddr *)&addr, len); //send message to A
        //cout<<"sent a message to "<<msgSrc<<"through port: "<<ports[(int)(msgSrc.c_str()[0]-'A')];                                                            


    } else {
        //else run the client thread normally 
        //cout << "Client thread running - Any key to proceed\n";
    

    //int recvmsg[100]; //receive buffer
    //const struct sockaddr_in * temp;
    
        //cin >> answ;
        //cout<<"Source port: "<<port<<"sending dvs to neighbours...\n"; 
        for(int i = 0; i<size; i++){
            
            if(this->neighbours[i] == 1 && update == true && portForNeighbour[i]!=-1){//if something is a neighbour, send to it
                //we can now use the i
                addr.sin_port = htons(portForNeighbour[i]);
               // cout << "CLIENT-Found neighbour " << i << " on port " << portForNeighbour[i] << "..attempting send"<< endl;  

            //  this->setPSER(addresses[i]);
                s = sendto( (this->socks), msg, 100, MSG_CONFIRM, ( struct sockaddr *)&addr, len);
                //cout << "CLIENT-Message sent."<< endl << endl; 
            }
        }
        
        if(s == -1){
            perror("send error");
        }
        sleep(rand()%3);


/*
            //CLIENT RECEIVE 
    //this->servAddr.sin_port = htons(pNum);     
    //this->servAddr.sin_addr.s_addr = INADDR_ANY;  
            r = recvfrom(this->socks, (int *)recvmsg, 100, MSG_WAITALL, 
                (struct sockaddr *)&addr, &len);    
        if(r == -1){
            perror("recv error");
        }
  */
    }
    
	return;      
}


void router::Rrecv(int pNum, char src){
    char recvmsg[100]; 
    char sendmsg[100];
    char abc[size] = {'A','B','C','D', 'E','F'};
    sprintf(sendmsg, "Hello from %c" , src);
    int r;
    //char answ;
    //s; 
    //cout << "Server thread running\n";
    memset(&servAddr, 0, sizeof(servAddr));
    memset(&cliAddr, 0, sizeof(cliAddr));

    this->servAddr.sin_family = AF_INET;
    this->servAddr.sin_port = htons(pNum);     
    this->servAddr.sin_addr.s_addr = INADDR_ANY;  
 
    //cout<<"IN FUNCTION RRECV\n";
      
    while(1){
    //SERVER RECEIVE 
    //cout << "SERVER-Waiting to receive...\n";
        r = recvfrom(this->socks, (char *)recvmsg, 100, MSG_WAITALL, 
                        (struct sockaddr *)(this->pCli), this->plen);

	//if(recvmsg[0]==(int)(name-'A'))
        if(r == -1){
            perror("recv error");
        }
        if(recvmsg[0]=='i'){   
            if(recvmsg[2]==name){
                cout<<"Sending message to: "<<recvmsg[4]<<"\n";
                //recvmsg[5]=name;
            }
            if(recvmsg[4]==name){
                cout<<">>Message Received from: "<<recvmsg[2]<<"\n";
                auto time0 = std::chrono::system_clock::now();
                std::time_t time_now0 = std::chrono::system_clock::to_time_t(time0);

                cout << ">>Received on " << std::ctime(&time_now0);  
                cout<<">>Message path through network:\n";
                
                int whilecount=5;
                while(whilecount<12&&recvmsg[whilecount]!='0'){
                    cout<<"\t"<<recvmsg[whilecount++]<<"\t-->";
                }
                    cout<<"\t"<<name<<"\n>>Received Message:\n";
                whilecount=12;
                while(recvmsg[whilecount])
                    cout<<recvmsg[whilecount++];
                }
                
            else{
                int lastnode,wscount;
                wscount=5;
                lastnode=wscount;
                while(recvmsg[wscount]!='0')
                {
                    lastnode=wscount;
                    wscount++;
                }
                
                recvmsg[wscount]=name;

                int nextnode=destVia[(int)(recvmsg[4]-'A')];

                memset(&servAddr, 0, sizeof(servAddr));
                memset(&cliAddr, 0, sizeof(cliAddr));

                this->servAddr.sin_family = AF_INET;
                this->servAddr.sin_port = htons(portForNeighbour[nextnode]);     
                this->servAddr.sin_addr.s_addr = INADDR_ANY;
                
                if(recvmsg[2]!=name)
                cout<<">>Receiving packet from: "<<recvmsg[lastnode]<<"\n";
                //TIME STAMP STUFF 
                auto time = std::chrono::system_clock::now();
                std::time_t time_now = std::chrono::system_clock::to_time_t(time);

                cout << ">>Received on " << std::ctime(&time_now);  
                cout<<">>Final Destination: "<<recvmsg[4]<<"\n";
                cout<<">>Forwarding packet to: "<<abc[nextnode]<<"\n";

                r = sendto( (this->socks), (char *)recvmsg, 100, MSG_CONFIRM, ( struct sockaddr *)&servAddr, len); //send message to A
       
            }
            cout << "----------------------------------------------------------------------";
            cout<< endl; 
        }

    
        
    }
    
}



void router::dvrecv(int pNum, char src){
    //char abc[size] = {'A','B','C','D', 'E','F'};
    //sprintf(sendmsg, "Hello from %c" , src);;
    int r=0;
    r++; 
    //s; 
    //cout << "Server thread running\n";
    memset(&servAddr, 0, sizeof(servAddr));
    memset(&cliAddr, 0, sizeof(cliAddr));

    this->servAddr.sin_family = AF_INET;
    this->servAddr.sin_port = htons(pNum);     
    this->servAddr.sin_addr.s_addr = INADDR_ANY;  
    
    while(1){
    //SERVER RECEIVE 
    //cout << "SERVER-Waiting to receive...\n";
        r = recvfrom(this->socks, (int *)dvrecved, 100, MSG_WAITALL, 
                        (struct sockaddr *)(this->pCli), this->plen);
        if(r == -1){
            perror("recv error");
        }
        //cout << "Server receives {";
	//cout<<"in function dvrecv\n";
	//for(int a=0;a<(2*size)+1;a++)
	//	cout<<dvrecved[a]<<" "; 

    //Thinking here we need a function to write to file. 
   // writeToFile();
	updatetables();

    return;
    }
}


void router::updatetables(){
	char ch[size]={'A','B','C','D','E','F'};
	updating=false; //counting if update doesn't occur

	for(int forcounter=1;forcounter<size+1;forcounter++){
		if(dvrecved[forcounter+size]!=-1){
			//cout<<"in here for: "<<(forcounter-1)<<"\n";
			//cout<<dvrecved[forcounter+size]<<" "<<costToNeighbour[dvrecved[0]]<<"     "<<costToNeighbour[forcounter-1]<<" "<<neighbours[forcounter-1]<<" ";
			//cout<<(bool)(dvrecved[forcounter+size]+costToNeighbour[dvrecved[0]]<costToNeighbour[forcounter-1])<<" ";
			if((((dvrecved[forcounter+size]+costToNeighbour[dvrecved[0]]<costToNeighbour[forcounter-1])&&costToNeighbour[forcounter-1]!=1)||costToNeighbour[forcounter-1]==-1)&&(dvrecved[forcounter+size]!=-2))
				{
				//cout<<" changed\n";
				iterations_without_update=0;
				updating=true; 			//means update occurred
				costToNeighbour[forcounter-1]=dvrecved[forcounter+size]+costToNeighbour[dvrecved[0]];
				if(destVia[dvrecved[0]]==dvrecved[0])
					destVia[forcounter-1]=dvrecved[0];
				else
					destVia[forcounter-1]=destVia[dvrecved[0]];
				//if(neighbours[forcounter-1]==0)
				//	neighbours[forcounter-1]=1;
				}
			//else if((neighbours[forcounter-1]==-1)&&(forcounter-1)==(int)(name-'A')){
			//	costToNeighbour[dvrecved[0]]=dvrecved[forcounter-1];
			//	via[]
			//}
		}
		
		
	}
		if(!updating)
			iterations_without_update++;


	if(updating){
		

		cout<<"tables updated after recieving distance vectors from"<<(ch[dvrecved[0]])<<", new tables: \n"<<"Router\t"<<"Updated Cost\tVia\n";
		outputfile<<"tables updated after recieving distance vectors from"<<(ch[dvrecved[0]])<<", new tables: \n"<<"router\t"<<"min cost\tVia\n";		
		for(int forcounter=0;forcounter<size-1;forcounter++)
			{
			cout<<ch[forcounter]<<"\t"<<costToNeighbour[forcounter]<<"\t\t"<<ch[destVia[forcounter]]<<"\n";
			outputfile<<ch[forcounter]<<"\t"<<costToNeighbour[forcounter]<<"\t\t"<<ch[destVia[forcounter]]<<"\n";
			//cout<<"written to output stream\n";

			}
            cout << "----------------------------------------------------------------------\n";
		}

	//else{
        //cout<<"no updates this time\n";
       // cout << ""; 
   // }
		

	
	return;
}


void router::setPSER(const struct sockaddr_in addr){
    this->pSer = &addr; 
}

void router::setparserstuff(int neighbours[size],int neighbour_ports[size],int link_cost[size]){

	//char ch[size]={'A','B','C','D','E','F','G'};
	for(int forcounter=0;forcounter<size;forcounter++){
	
		this->neighbours[forcounter]=neighbours[forcounter];
		this->costToNeighbour[forcounter]=link_cost[forcounter];
		this->portForNeighbour[forcounter]=neighbour_ports[forcounter];		

		if(neighbours[forcounter]==1)
			this->destVia[forcounter]=forcounter;   // if neighbour, destination is neighbour itself
		else
			this->destVia[forcounter]=-1;
	}

	costToNeighbour[(int)(name-'A')]=-2;
	destVia[(int)(name-'A')]=-2;

	// to verify....
	//cout<<"***************************in setparserstuff *************\nneighbours:\n";
	//for(int forcounter=0;forcounter<size;forcounter++){
		//cout<<"\n"<<ch[forcounter]<<": "<<neighbours[forcounter];
		//if(neighbours[forcounter]==1)
		//cout<<"\nname: "<<ch[forcounter]<<",port: "<<portForNeighbour[forcounter]<<",cost: "<<costToNeighbour[forcounter]<<",via: "<<destVia[forcounter]<<endl;
	//}
	return;
}

/*string sortFileName(string fn){
    fn = "routing-output" + this->name + ".txt"; 
    cout << fn; 
    return fn; 
}
void router::writeToFile(){
    ofstream file; 
    string file_name; //needs to insert the appropriate NAME in the output.txt  
    file_name = sortFileName(file_name);
    file.open(file_name);
}*/