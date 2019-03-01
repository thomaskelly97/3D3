#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <iostream>
#include <sstream> 
#include <errno.h> 
#include <unistd.h> 

#include "httpRequest.h"
#include "httpRequest.cpp"

using namespace std; 


#define PORT "3490" // the port client will be connecting to 

#define MAXDATASIZE 100 // max number of bytes we can get at once 

void parseURL(string url); 
char host[20];
char port[10];
char parsed_url[20];  

int main(int argc, char *argv[])
{    
    string URL = {"http://localhost:4000/index.html"}; //default 
    if (argc > 1){
        URL = argv[1]; 
    }
    cout << "\n---CLIENT---\nSearch URL: " << URL << endl; 
    parseURL(URL);
    int portNum;
    portNum = atoi(port); //convert to integer 
    int sock02 = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in servAddr; 
    servAddr.sin_family = AF_INET;
    servAddr.sin_port = htons(portNum);     // short, network byte order
    servAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    memset(servAddr.sin_zero, '\0', sizeof(servAddr.sin_zero));

    //Connect to server 
    if (connect(sock02, (struct sockaddr *)&servAddr, sizeof(servAddr))) {
        perror("connect");
        return 2;
    }
    cout << ">> Successfully connected to server\n";

    //Now we need to create the HTTP Request and send it to the server
    //set host, etc.  
    //call buildRequest to form the message into a string as show: 
    //"GET /beej/inet_ntoaman.html http/1.1\nHOST: retran.com\n\n"
    cout << "Creating HTTP Request...\n";
    httpRequest req; 
    req.setMethod("GET");
    req.setHost(host);
    req.setUri(parsed_url);
    req.setVer("HTTP/1.0");
    req.createRequest();
    cout << "==================\n";
    //send that to the server 
    int reqLen =0, res=0, sent=0;
    reqLen = req.getLength();
    char buffer[10054]; 
    do{
        res = send(sock02, req.convert().c_str(),(reqLen - sent),0);
        sent = sent + res; 
    } while (sent < reqLen);
     cout << "---FILE---\n";
    res = recv(sock02, buffer, 10054,0);
    if(res > 0){
        cout << buffer; 
    } else if(res == 0){
        cout << "Connection Closed\n";
    } else {
        cout << "recv failed\n";
    }
    //server returns code 
    //client processes code 
    //server sends file 
    


}


void parseURL(string url){
    //cout << "Entered parser.\n";
    char sample; 
    bool h= false, p=false,u=false; 
    int j=0,k=0,l=0; //counter

    for(std::string::size_type i =0; i<url.size();i++){
        //loop through string 
        sample = url[i]; 
       // cout << "-" << sample << endl;
        if(i > 6 && h == false){ //if we're over 7 and host not finished
            host[j] = sample;  
            //cout << "|" << host[j];
            j++;
            if(sample == ':'){
                h = true; //host is finished 
                j--;
                host[j] = 0;
                 //block out the ':' 
            }
        } 
        if(i > (6+j+1) && p == false){
            port[k] = sample; 
            //cout << "~" << port[k]; 
            k++; 
            if(sample == '/'){
                p=true;
                parsed_url[l] = sample; 
                l++; 
                k--;  
                port[k] = 0;
                
            }
        }
        if(i > (7+j+k+1) && u == false){
            parsed_url[l] = sample; 
            //cout << "+" << parsed_url[l]; 
            l++; 
            if(sample == ' '){
                u = true; 
                l--; 
                parsed_url[l] = 0;
                
                break; 
            }
        }
      

    }
    cout << "Parsed data: \nHost: " << host << "\nPort Number: " << port << "\nURL: "<< parsed_url << endl; 
}