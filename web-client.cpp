//Thomas Kelly 
//Student Number 16323455 
//This program was written largely through vagrant on windows, but also by using a linux machine at times

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
#include <fstream> 

#include "httpRequest.h"
#include "httpRequest.cpp"

using namespace std; 



void insertChar(char word[]);
void writeTo(char input[]);
void parseURL(string url); 
char host[20];
char port[10];
char parsed_url[20];  

int main(int argc, char *argv[])
{    
    string URL = {"http://localhost:4000/index.html"}; //default input 
    if (argc > 1){
        URL = argv[1]; 
    }
    cout << "Thomas Kelly - 16323455\n---CLIENT---\nSearch URL: " << URL << endl; 
    parseURL(URL);
    int portNum;
    int sss; 
    portNum = atoi(port); //convert to integer 
    int sock02 = socket(AF_INET, SOCK_STREAM, 0); //create socket 
    //address settings 
    struct sockaddr_in servAddr; 
    servAddr.sin_family = AF_INET; 
    servAddr.sin_port = htons(portNum);     
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
    //call buildRequest to form the message into a string a 
    char lAnsw[6] = {0}; 
    char buffer[500]; 
    char msg[40]; 
    int answ; 
    int reqLen =0, res=0, sent=0, res2=0;
   httpRequest req;
   cout << "Creating HTTP Request...\n";
   do {
        reqLen =0; res=0; sent=0; res2=0;
       if(lAnsw[0] == 'y'){ 
            cout << "Filename: ";
            cin >> parsed_url; cout << endl;   
            insertChar(parsed_url);
       }
       //set all request fields 
        req.setHost(host); 
        req.setMethod("GET");
        req.setUri(parsed_url);
       
        cout << "Set HTTP Version - Enter 1 or 0 - (Setting HTTP/1.1 will return bad request.)\n";
        cin >> answ; 
        if(answ == 1){
            req.setVer("HTTP/1.1");
        } else {
            req.setVer("HTTP/1.0");
        }
        req.createRequest();
    cout << "==================\n";
    //send that to the server 
    
    reqLen = req.getLength();
    
    do{
        res = send(sock02, req.convert().c_str(),(reqLen - sent),0);
        sent = sent + res; 
    } while (sent < reqLen);
    cout << "Server Response: \n";
    res2 = recv(sock02,msg, 40,0);
    if (res2 > 0){
        cout << msg; 
    }
    
    // cout << "---FILE---\n";
    res = recv(sock02, buffer, 500,0);
    if(res > 0){
        cout << buffer; 
    } 
     else if(res == 0){
        cout << "Connection Closed\n";
    } else {
        cout << "recv failed\n";
    }

    //Now buffer has the file contents! 
    //Need to write to the file 
    writeTo(buffer); //this writes the response to a file 
    
    cout << "Do you want to make another request?(yes/no)\n"; 
    cin >> lAnsw; 
    sss = send(sock02, lAnsw,1,0); //send the answer to server 
   
    if(sss == -1){
        perror("send");
    }
   
    //cout << "Resetting Buffer array...\n";
    memset(buffer, '\0', sizeof(buffer));
    //loop back around, only if the user has opted to 
   } while(lAnsw[0] == 'y');
    
    close(sock02);
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
        if(i > (7+j) && p == false){
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
        if(i > (8+j+k) && u == false){
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
    cout << "Parsed data: \nHost: " << host << "\nPort Number: " << port << "\nRequested File: "<< parsed_url << endl; 
}


void writeTo(char input[]){
    ofstream recFile; 
    cout << "\n> Saving response to the 'receiveFile'...\n";
    recFile.open("receiveFile.html", std::ofstream::out | std::ofstream::trunc);
    recFile << input; 
    recFile.close(); 
}

void insertChar(char word[]){
    char sample; 
    int count=0; 
    sample = word[count];
    while(sample != '\0') {
        sample = word[count]; 
        //cout << count; 
        count++; 
    } 
    //cout << "Size of word " << count << endl; 
    for(int i = count-1; i > -1;i--){
        sample = word[i]; 
        word[i+1] = sample; //move over 
    }
    word[0] = '/';
    //cout << word << endl; 
}