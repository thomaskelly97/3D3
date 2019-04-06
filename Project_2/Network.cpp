   
#include <string>
#include <fstream>
#include <iostream>

using namespace std;

void RemoveLineContaining(const char* inputfile, const char* outputfile, const char* RemoveContaining);
void RemoveRouter(const char* inputfile, const char* outputfile);
void Initialise(const char* inputfile);
void InjectTraffic();

int main ()
{
    const char* in = "start-router";
    const char* out = "start-router-changed";

    Initialise(in);
    InjectTraffic();

    RemoveRouter(in,out);
    
    return 0;
}

void Initialise(const char* inputfile){
    cout << "\nInitialising Network...";
    const char * command = "./";
    const char * cmd;
    string fullcmd;
    fullcmd += command;
    fullcmd += inputfile;
    cmd = fullcmd.c_str();
    system(cmd);
}

void InjectTraffic(){
    system("./inject_msg");
}


void RemoveRouter(const char* inputfile, const char* outputfile){

    char response;
    string Name;
    const char* name;
    bool recieved = true;
    cout << "\nWould you like to shut down a router? (Y/N) ";

    while(recieved){
        cin >> response;
        if(response != 'Y' || response != 'y' || response != 'N' ||  response != 'n')
            recieved = false;
        else 
            cout << "Invalid input : Format--> Y or N" ;
    }
    if(response == 'Y' || response == 'y'){

        cout << "\nPlease name router you would like to shut off ";
        cin >> Name;
        name = Name.c_str();
        system("killall xterm");
        RemoveLineContaining(inputfile, outputfile, name);
        Initialise(outputfile);         
        InjectTraffic();    
    }
}

void RemoveLineContaining(const char* inputfile, const char* outputfile, const char* RemoveContaining){

    string line;
    ifstream myfile(inputfile);
    ofstream out(outputfile);
    const char* letter = RemoveContaining;


    if(!inputfile){
        cout << "Could not find " << inputfile << endl;
    }

    else if(!outputfile){
        cout << "Could not find " << outputfile << endl;
    }

    else{
        while (getline(myfile, line))
        {
            if(line.find(letter) != string::npos){
                line.insert(0,"\n");
                size_t nFPos = line.find(letter);
                size_t secondNL = line.find('\n', nFPos);
                size_t firstNL = line.rfind('\n', nFPos);
                line.erase(firstNL, secondNL - firstNL);
                line.assign("");
            }
            else
                out << line << "\n";
        }
    }
}
