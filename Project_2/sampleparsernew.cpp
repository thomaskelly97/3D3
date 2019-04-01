
  #include<unordered_map>
  #include<iostream> 
  #include<fstream>
  using namespace std;
  


  /*can copy these to declarations along with function declaration for the function following*/

  char ch[7]={'A','B','C','D','E','F','G'};												
  char name='A';
  int neighbour_ports[7];
  int port;                                      
  bool neighbours[7];
  int link_cost[7];
	





	int main(int argc,char **argv){

	//parses sample.txt to get myport port of neighbours and link cost for neighbours
	//will have to change the function signature when adding to router class .. either to void function_name()
	//or void function_name(char name) if u want to pass the name 	


	string name_string="";
	name_string+=name;
	string line;	
	int get_port_from;
	bool got_port=false;
	ifstream myfile("newsample.txt");										//file with initial info goes here
	int x,y,z,cost,flag=1,i=0,j=0;
	string x_string="",y_string="",z_string="",cost_string="";


	for(int i=0;i<7;i++){
		link_cost[i]=-1;
		neighbours[i]=false;
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
							neighbours[y]=true;
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
			if(neighbours[forcounter]==true)
				currneighbour=forcounter;
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

	}
		
	cout<<"port(A): "<<port<<", neighbours of A: ";
		for(i=0;i<7;i++){

		if(neighbours[i]){
			cout<<ch[i]<<",link cost: "<<link_cost[i]<<", port: "<<neighbour_ports[i]<<"\n";	
		}

		}
}
