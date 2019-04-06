 #include<unordered_map>
  #include<iostream> 
  #include<fstream>
  using namespace std;


    int main(int argc,char **argv){

    //parses sample.txt to get myport port of neighbours and link cost for neighbours



    char ch[7]={'A','B','C','D','E','F','G'};
    char name='A';
    string name_string="";
    name_string+=name;
    int port[7];
    int myport;                                      //
    bool neighbours[7];
    int link_cost[7];
    string line;    
    int get_port_from;
    bool get_port_flag=true;
    ifstream myfile("sample.txt");                                        //file with initial info goes here
    int x,y,z,cost,flag=1,i=0,j=0;
    string x_string="",y_string="",z_string="",cost_string="";


    for(int i=0;i<7;i++){
        link_cost[i]=-1;
        neighbours[i]=false;
        port[i]=-1;
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
                        if(get_port_flag){
                            get_port_from=y;
                            get_port_flag=false;
                        }
                            
                        
                        neighbours[y]=true;
                        }
                    if(j==3){
                        flag++;
                        if(neighbours[y]){
                        port[y] = stoi(z_string);
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
        if((int)(currchar-'A')==get_port_from){
            while(j<3){
                
                if(a[i]==','){
                    i++;                
                    j++;
                }
                if(j==1){
                    y_string+=a[i];
                    }
                    
                if(j==2){
                    if(y_string==name_string)
                        get_port_flag=true;
                    z_string+=a[i];
                    }
                i++;
                }
            if(get_port_flag){
                myport=stoi(z_string);
                get_port_flag=false;
            }
        }
    }
        
    cout<<"port(A): "<<myport<<", neighbours of A: ";
        for(i=0;i<7;i++){

        if(neighbours[i]){
            cout<<ch[i]<<",link cost: "<<link_cost[i]<<", port: "<<port[i]<<"\n";    
        }

        }
}