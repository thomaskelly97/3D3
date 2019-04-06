#include <stdio.h>
#include <string.h>
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
#include <string>
#include <array>


  #include<unordered_map>
  #include<iostream> 
  #include<fstream>
  using namespace std;
	int port[7];
	int costs[7][7];
	int via[15][15];	
	/* Vertex names */
    char ch[7]={'A','B','C','D','E','F','G'};
 
void getinitialcosts(){
	char name_of_routers[7]={'A','B','C','D','E','F','G'};
	//int costs[7][7];
	//int port[7];
	bool got_port[7];
	for(int k=0;k<7;k++){
		got_port[k]=false;
		}
	for(int k=0;k<7;k++){
		for(int l=0;l<7;l++){
			costs[k][l]=-1;
		}
	}
	string line;
	ifstream sample("sample.txt");
	int x,y,z,cost,flag=1,i=0,j=0;
	string x_string="",y_string="",z_string="",cost_string="";
	while(getline(sample,line)){
	flag=1;
	i=0;j=0;x_string="";y_string="";z_string="",cost_string="";
	char* a = (char*)line.c_str();
		while(flag<5){
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
						}
					if(j==3){
						flag++;
						if(!got_port[y]){
						port[y]=stoi(z_string);
						got_port[y]=true;
						}
					}
			}
			
			if(a[i]<0){
				flag++;
				cost=stoi(cost_string);
				}
	
			switch(flag)
			{	
				case 1: x_string+=a[i++];break; 
				case 2: y_string+=a[i++];break;
				case 3: z_string+=a[i++];break;
				case 4: cost_string+=a[i++];break;

			} 
				
				
		}
				costs[x][y]=cost;

}	
	for(int k=0;k<7;k++){
		for(int l=0;l<7;l++){
			cout<<"cost for link from "<<name_of_routers[k]<<" to "<<name_of_routers[l]<<": "<<costs[k][l]<<" \n";
		}
		cout<< " port for "<<name_of_routers[k]<<" is: "<<port[k]<<" \n";
	}

	

}


string pathgen(char src,char dest){

	

	string path = "";
	int curr=src;
	int prev;
	while(curr!=dest){
		curr=via[curr][dest];
		if(prev==curr)
			curr=dest;
		path+=ch[curr];
		path+="\t";                       //each node separated by \t
		prev=curr;
		}
	path+="\r\n";					//ending path with \r\n
	return path;

}


int main(int argc, char **argv)
{
	string sourcefordvr="sample.txt"; //file with costs and stuff
	char source_char='A',destination_char='F';  // source & destination goes here
	int source = (int)(source_char-'A'), destination = (int)(destination_char-'A');
    int graph[15][15];
    int i,j,k,t;
    int numNodes=7;
 
   /* cout<<"\n Enter Number of Nodes:";
    cin>>numNodes;
 */
    /* Initialize graph*/
    for (i=0;i<numNodes;i++)
    {
        for(j=0;j<numNodes;j++)
        {
            graph[i][j]=-1;
        }
    }
 
    
    /* Get input */
/*    for (i=0;i<numNodes;i++)
    {
        for(j=0;j<numNodes;j++)
        {
            if(i==j)
            {
                graph[i][j]=0;
            }
            if(graph[i][j]==-1)
            {
                cout<<"\n Enter Distance between "<<ch[i]<<" - "<<ch[j]<<" : ";
                cin>>t;
                graph[i][j]=graph[j][i]=t;
            }
        }
    }
 */



    /* Initializing via */
    
    for (i=0;i<numNodes;i++)
    {
        for(j=0;j<numNodes;j++)
        {
            via[i][j]=-1;
        }
    }


	getinitialcosts();
	
	/*for(int k=0;k<7;k++){
		for(int l=0;l<7;l++){
			cout<<"cost for link from "<<ch[k]<<" to "<<ch[l]<<": "<<costs[k][l]<<" \n";
		}
		cout<< " port for "<<ch[k]<<" is: "<<port[k]<<" \n";
	}*/	


	for(int counter=0;counter<numNodes;counter++){									//can do something about the size..
		for(int count=0;count<numNodes;count++){
			graph[counter][count]=costs[counter][count];
		}	
	}


 
    cout<<"\n After Initialization";
    /* Display table initialization */
    for (i=0;i<numNodes;i++)
    {
        cout<<"\n"<<ch[i]<<" Table";
        cout<<"\nNode\tDist\tVia";
        for(j=0;j<numNodes;j++)
        {
            cout<<"\n"<<ch[j]<<"\t"<<graph[i][j]<<"\t"<<via[i][j];
        }
    }
 
    //sharing table
    int sh[15][15][15];
    for(i=0;i<numNodes;i++)
    {
        for(j=0;j<numNodes;j++)
        {
            for (k=0;k<numNodes;k++)
            {
                /* Check if edge is present or not*/
                if((graph[i][j]>-1)&&(graph[j][k]>-1))
                {
                    sh[i][j][k]=graph[j][k]+graph[i][j];
                }
                else
                {
                    sh[i][j][k]=-1;
                }
            }
        }
    }
   
    /* Updating */
    int final[15][15];
    for(i=0;i<numNodes;i++)
    {
        for(j=0;j<numNodes;j++)
        {
            /* Copy initial value from input graph*/
            final[i][j]=graph[i][j];
            via[i][j]=i;
             
            /*Update them*/
            /* Check condition a - b - c */
            for(k=0;k<numNodes;k++)
            {
                 
                if((final[i][j]>sh[i][k][j]) || (final[i][j] == -1))
                {
                    if(sh[i][k][j]>-1)
                    {
                        final[i][j]=sh[i][k][j];
                        via[i][j]=k;
                    }
                }
            }

 
            if(final[i][j]==-1)
            {
                for(k=0;k<numNodes;k++)
                {
 
                    if((final[i][k]!=-1)&&(final[k][j]!=-1))
                    {
                        if((final[i][j]==-1) || ((final[i][j]!=-1) &&(final[i][j]>final[i][k]+final[k][j]))) 
                        {
                            if(final[i][k]+final[k][j]>-1)
                            {
                                final[i][j]=final[i][k]+final[k][j];
                                via[i][j]=k;
                            }
                        }
                    }
                     
                }
            }
        }
    }
 
    cout<<"\n After Update :";
    /* Display table Updation */
    for (i=0;i<numNodes;i++)
    {
        cout<<"\n"<<ch[i]<<" Table";
        cout<<"\nNode\tDist\tVia";
        for(j=0;j<numNodes;j++)
        {
            cout<<"\n"<<ch[j]<<"\t"<<final[i][j]<<"\t";
            if(i==via[i][j])
                cout<<"-";
            else
                cout<<ch[via[i][j]];
        }
    }
 


	
	//creating message here


	string path = pathgen(source,destination);	
	string line_traffic;
	cout<<"\nroute: "<<path;
	cout<<"source to destination cost:";
	cout<<final[source][destination];
	cout<<"\n";
		
	ifstream inputfile ("traffic.txt");
	if (inputfile.is_open())
	{
	
	ofstream myfile("message.txt");
	if (myfile.is_open())
	  {
	    myfile << path;
	while ( getline (inputfile,line_traffic) )
	{
	myfile << line_traffic;
	myfile<<"\n";
	}
	cout<<"message to be sent written in message.txt\n";
	inputfile.close();
	myfile.close();
	}
	
  	else cout << "Unable to open message.txt";
	
	}
	
  	else cout << "Unable to open traffic.txt";
	
	//cin.ignore();
    return 0; 
}
 
