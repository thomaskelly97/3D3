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
using namespace std; 
 
int main(int argc, char **argv)
{
    int graph[15][15];
    int i,j,k,t;
    int numNodes;
 
    cout<<"\n Enter Number of Nodes:";
    cin>>numNodes;
 
    /* Initialize graph*/
    for (i=0;i<numNodes;i++)
    {
        for(j=0;j<numNodes;j++)
        {
            graph[i][j]=-1;
        }
    }
 
    /* Vertex names */
    char ch[7]={'A','B','C','D','E','F','G'};
 
    /* Get input */
    for (i=0;i<numNodes;i++)
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
 
    /* Initializing via */
    int via[15][15];
    for (i=0;i<numNodes;i++)
    {
        for(j=0;j<numNodes;j++)
        {
            via[i][j]=-1;
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
 
    cin.ignore();
    return 0; 
}
 