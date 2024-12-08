#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
using namespace std;

struct road {
    char dest;       
    int dist;        
    road* next;      
    road(char d,int s,road* nextRoad=nullptr):dest(d),dist(s),next(nextRoad){}
};
class vehicle
{   public:
    string V;
    string path;
    string curr;
    int l=1;
    vehicle(string v="", string p="")
    {
        V=v;
        path=p;
        for(int i=0; i<2; i++)
        {
            if(p[i]!='\0')
            {
            curr+=p[i];
            }
        }
        cout<<"current: "<<curr<<endl;
       
    }
    void change_Current()
    {
        curr="";
       for(int i=l; i<2+l; i++)
        {
            if(path[i]!='\0')
            {
            curr+=path[i];
            }
        }
        cout<<"current: "<<curr<<endl;
        l++;
    }
    string current_path()
    {
        return curr;
    }
};
struct track{
    string road;     
    int vehicleCount; 
    track *next;  
    track(){road="",vehicleCount=0,next=nullptr;}
    track(string r, int c):road(r),vehicleCount(c),next(nullptr) {}
};
class CongestionMonitoring{
private:
    track* table[27];
    int hashFunction(char src, char dest) {
        int hash = src + dest;
        return hash%27;
}
public:
    CongestionMonitoring(){
        for (int i=0;i<27; i++) {
            table[i]=nullptr;
        }
    }
    void add(char src,char dest) {
       string roadKey = string(1, src) + " to " + string(1, dest);//concating starting vertex and ending vertex i.e A + B = AB
        int index=hashFunction(src,dest);

        track* temp=table[index];
        while(temp){
            if(temp->road == roadKey){
                temp->vehicleCount++;
                return;
            }
            temp=temp->next;
        }
        //IF NOT FOUND
        track* nawaTrack=new track(roadKey, 1);
        nawaTrack->next=table[index];
        table[index]=nawaTrack;
    }
    void display(){
        for(int i=0;i<27;i++) {
            track* temp=table[i];
            while(temp){
                cout<<temp->road<<" | Vehicles: "<<temp->vehicleCount<<endl;
                temp=temp->next;
            }
        }
    }
};
class roadNetworks{
private:
    int numOfVertex;
    road **roadKiList;
    int T_vehicle=32;
    vehicle*v;

public:
    roadNetworks(){numOfVertex=0;roadKiList=nullptr;}  
    roadNetworks(int n)
    {  
        v=new vehicle[32];
        numOfVertex = n;
        roadKiList = new road*[n];  //initialising list for storing graph in adjacency list manner
        for (int i = 0; i < n; i++) 
        {
            roadKiList[i] = nullptr; 
        }
    }
    void addRoads(char src, char dest, int dist, bool oneWay=false) {
        int srcIndex=src-'A';  
        int destIndex=dest-'A';

        roadKiList[srcIndex]=new road(dest, dist, roadKiList[srcIndex]);

        if (!oneWay) {
            roadKiList[destIndex]=new road(src, dist, roadKiList[destIndex]);
        }
    }
    void displayRoad(){
        for(int i=0;i<numOfVertex;i++) {
            cout<<char('A'+i)<<": ";
            road* temp=roadKiList[i];
            while(temp){
                cout<<" -> ("<<temp->dest<<", "<<temp->dist<<" km)";
                temp = temp->next;
            }
            cout<<endl;
        }
    }

int min(int dist[],bool v[],int T)
{
int min=1e9;
int index=-1;
    for(int k=0; k<T; k++) 
    {
        if(v[k]==false && dist[k]<=min) 
        {
            min=dist[k];
            index=k;
        }
    }
return index;
}

string ShortestPath(char start,char end) 
{
int s=start-'A'; 
int e=end-'A';
int*dist=new int[numOfVertex]; 
char*p=new char[numOfVertex]; 
bool*v=new bool[numOfVertex]; 
for(int i=0;i<numOfVertex;i++)
    {
        dist[i]=1e9;
        p[i]='\0';
        v[i]=false;
    }
dist[s]=0;           
for(int c=0;c<numOfVertex;c++) 
    {
        
        int u=min(dist,v,numOfVertex);
        v[u]=true; 
        if(u==e)//if end vertex is found then break
        break;
       
        road*temp=roadKiList[u]; 
    while(temp!=NULL)
     { 
     //Comparing the neighbours of source vertex to get the shortest distance. so in each iteration the node will move on to the next neighbour
    int l=temp->dest-'A'; 
    int weight=temp->dist;  
    if(v[l]==false) 
    { 
        if(dist[u]!=1e9)
         { 
            if(dist[u]+weight<dist[l])
             { 
                dist[l]=dist[u]+weight;  
                p[l]='A'+u;            
             }
        }
    }

    temp=temp->next;
    }
    }
if(dist[e]==1e9)
{
  cout<<"No path was found."<<endl;
  return "";
}
else 
{
cout<<"Shortest distance:"<<dist[e]<<endl;
char a=end;
int i;
string V;
while(a!='\0') 
{
     V+=a;
       i=a-'A';
       a=p[i];
}
string temp;
int j=0;
int size=0;
//reverse string
while(V[size]!='\0')
{
    size++;
}
while(size>0)
{
    temp+=V[size-1];
    j++;
    size--;
}
V=temp;
//cout<<V;
delete[] dist;
delete[] p;
delete[] v;
return V;
     }
}

void read_vehicle() {
    ifstream file("vehicles.csv");
    string line;

    if (!file.is_open()) {
        cout << "Error in opening file..." << endl;
        return;
    }

    getline(file, line); 
    int index = 0;
    while (getline(file, line)) 
    {
        stringstream ss(line);
        string vehicle_ID;
        string src;
        string dest;

        getline(ss, vehicle_ID, ',');  
        getline(ss, src, ',');        
        getline(ss, dest, ',');        

        char start = src[0];
        char end = dest[0];
        string path=ShortestPath(start, end);
         
            v[index]=vehicle(vehicle_ID, path);
            cout<<"Vehicle " <<vehicle_ID << ": Path = " <<path<<endl;
            index++;
        
    }

    file.close();
}
void changeCurrent(int i)
{
    v[i].change_Current();
}
void read_And_addVehicle(CongestionMonitoring &rastyyy)
 {
    for (int i = 0; i < 31; i++)
     {  
        string vehiclePath = v[i].path;
        int pathlength;
        int pathLength = vehiclePath.length();
        for(int j=0; j<pathLength-1;j++)
         {  
            char src=vehiclePath[j];
            char dest=vehiclePath[j + 1];
            rastyyy.add(src, dest);  
        }
    }
}
void emergencyVehicleRouting()
{
        char start, end;
        cout<<"Enter start and end intersections for emergency vehicle: ";
        cin>>start; 
        cin>>end;
        cout << "Emergency Vehicle is being routed..." << endl;
        string path=ShortestPath(start, end);
        cout << "Emergency Vehicle path: " << path << endl;
}

};
void read_and_Build(roadNetworks &roads)
{
    ifstream file("road_network.csv");
    string line;
    
    if (!file.is_open()){
        cout<<"Error in opening file..."<<endl;
        return;
    }

    getline(file, line);

    while (getline(file, line)){
        stringstream ss(line);
        char src, dest;
        int dist;

        ss>>src; 
        ss.ignore();  
        ss>>dest;   
        ss.ignore(); 
        ss>>dist; 

        roads.addRoads(src, dest, dist); 
    }
    file.close();
}
class Status{
     public:
     char start;
     char end;
     string status;
     Status* next;
     Status(char s, char e, string stat){
        start= s;
        end= e;
        status= stat;
        next=NULL;
     }

};
class RoadStatusList{
    public:
       Status* head;
       RoadStatusList(){
          head=NULL;
       }
       void addStatus(char s, char e, string stat){
          Status* newstatus= new Status(s, e, stat);
           if(head==NULL){
              head=newstatus;
           }else{
             Status* temp=head;
               while(temp->next!=NULL){
                   temp=temp->next;
               }
               temp->next=newstatus;
           }
       }
       void display(){
             cout<<"-----Blocked Roads-----"<<endl;
             Status* temp=head;
             while(temp!=NULL){
                if(temp->status=="Blocked")
                 cout<<temp->start<<" to "<<temp->end<<" is "<<temp->status<<"."<<endl;
                  temp=temp->next;
             }
         
         }
};
class RoadClosure{
      public:
      RoadStatusList statuses;
      void loadData(){
	    string line;
	    string info;
	   
	    string status;
	    char start;
	    char end;
	    int lines=0;
	    
	    
	    ifstream myFile("road_closures.csv");
	    
	    while(getline(myFile, line)){
	    
		if(lines!=0 && !line.empty() ){
		
		  stringstream ss(line);
	          getline(ss, info, ',');
	          start= info[0];
	          if (info==""){
	             continue;
	          }
	          getline(ss, info, ',');
	          end= info[0];
	          
	          getline(ss, info, ',');
	          status= info;
	         
	          statuses.addStatus(start, end, status);
	          
	          }
	         
	         lines++;
	    
	   
	      }
	    myFile.close();
         } 
         void blockRoad(){
              string road;
              cout<<"Enter road to block(start, end): ";
              cin>>road;
              if(road.length()!=2){
                  cout<<"Invalid Input!"<<endl;
              }else{
                 char start=toupper(road[0]);
                 char end=toupper(road[1]);
                 statuses.addStatus(start, end, "Blocked");
                 display();
                 //vehicle routing system
              }
            }
         void display(){
             statuses.display();
         }

};


int main() {
    int totalVertexs = 26; 
    roadNetworks city(totalVertexs);  
    read_and_Build(city); 
    city.displayRoad(); 
  while(!exit)
  {
    int choice;
        cout<<"-----Simulation Dashboard-----"<<endl;
        cout<<"1. Display City Traffic Network"<<endl;
        cout<<"2. Display Traffic Signal Status"<<endl;
        cout<<"3. Display Congestion Status"<<endl;
        cout<<"4. Display Blocked Roads"<<endl;
        cout<<"5. Handle Emergency Vehicle Routing"<<endl;
        cout<<"6. Block Road due to Accident"<<endl;
        cout<<"7. Simulate Vehicle Routing"<<endl;
        cout<<"8. Exit Simulation"<<endl;
        cout<<"Enter your choice: ";
        cin>>choice;
        switch(choice){
            case 1:
               city.displayRoad(); 
               break;
            case 2: 
              // traffic.display();
               break;
            case 3:
               
               break;
            case 4:
              // closure.display();
               break;
            case 5:
               break;
            case 6:
              // closure.blockRoad();
               break;
            case 7:
               break;
            case 8:
              // exit= true;
               break;
            default:
               cout<<"Invalid Choice!"<<endl;
               break;
        }
        }
    cout<<"Assigning shortest path to vehicles:"<<endl;
    city.read_vehicle();
    city.changeCurrent(4);
    CongestionMonitoring roads;
    city.read_And_addVehicle(roads);
    roads.display();
    return 0;
    
}
