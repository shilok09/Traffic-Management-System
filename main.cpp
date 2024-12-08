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
    string priority;
    int l=1;
    vehicle(string v="", string p="",string prior="Low")
    {
        V=v;
        path=p;
        priority=prior;
        for(int i=0; i<2; i++)
        {
            if(p[i]!='\0')
            {
            curr+=p[i];
            }
        }
        //cout<<"current: "<<curr<<endl;
       
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
       void display()
       {
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
	    
		if(lines!=0 && !line.empty() )
        {
		
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

class roadNetworks{
private:
    int numOfVertex;
    road **roadKiList;

public:
  int T_vehicle;
  vehicle*v;
  RoadStatusList status;
    roadNetworks(){numOfVertex=0;roadKiList=nullptr;}  
    roadNetworks(int n)
    {    T_vehicle=30;
        v=new vehicle[100];
        numOfVertex=n;
        roadKiList=new road*[n];  //initialising list for storing graph in adjacency list manner
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

string ShortestPath(char start, char end) {
    int s = start - 'A';
    int e = end - 'A';
    int* dist = new int[numOfVertex];
    char* p = new char[numOfVertex];
    bool* v = new bool[numOfVertex];
    for (int i = 0; i < numOfVertex; i++) {
        dist[i] = 1e9;
        p[i] = '\0';
        v[i] = false;
    }
    dist[s] = 0;

    for (int c = 0; c < numOfVertex; c++) {
        int u = min(dist, v, numOfVertex);
        v[u] = true;
        if (u == e) break;

        road* temp = roadKiList[u];
        while (temp != NULL) {
            char a = 'A' + u;  // Source node
            char b = temp->dest; // Destination node
            // Check if road is blocked or under repair before considering it
            if(!isBlocked(a, b)) {
                int l=temp->dest - 'A';
                int weight = temp->dist;
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
        }

            temp = temp->next;
        }
    }

    if (dist[e] == 1e9) {
        cout << "No path was found." << endl;
        return "";
    } else {
        cout << "Shortest distance: " << dist[e] << endl;
        char a = end;
        int i;
        string V;
        while (a != '\0') {
            V += a;
            i = a - 'A';
            a = p[i];
        }

        string temp;
        int j = 0;
        int size = 0;
        while (V[size] != '\0') {
            size++;
        }
        while (size > 0) {
            temp += V[size - 1];
            j++;
            size--;
        }
        V = temp;

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
           // cout<<"Vehicle " <<vehicle_ID << ": Path = " <<path<<endl;
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
bool isBlocked(char start, char end) 
{           
    Status* temp = status.head;
    while (temp != NULL) {
        //cout<<temp->start<<temp->end<<temp->status;
        if (temp->start == start && temp->end == end && (temp->status=="Blocked" || temp->status=="Under Repair")) {
            cout<<start<<end<<endl;
            return true;
        }
        temp = temp->next;
        
    }
    return false;
}


void handleEmergencyVehicle()
   {    char start;
        char end;
        cout<<"Enter start and end intersection for emergency vehicle:"<<endl;
        cin>>start>>end;
        string path=ShortestPath(start, end);
        cout<<"Emergency Vehicle is being routed....:"<<endl;
        if (!path.empty()) {
            cout << "Emergency Vehicle Path: " << path << endl;
        }
    }

    void readEmergencyVehicles() 
    {
    ifstream file("emergency_vehicles.csv");
    if (!file.is_open()) 
    {
        cout << "Failed to open emergency vehicle file!" << endl;
        return;
    }

    string line;
    getline(file, line); 

    while (getline(file, line)) 
    {
        stringstream ss(line);
        string vehicleID;
        string src;
        string dest;
        string priority;

        getline(ss, vehicleID, ',');
        getline(ss, src, ',');
        getline(ss, dest, ',');
        getline(ss, priority, ',');

        
        char start = src[0];
        char end = dest[0];
        string path=ShortestPath(start, end);

            if (!path.empty()) {
                v[T_vehicle] = vehicle(vehicleID, path, priority); 
                T_vehicle++;
               /* cout << "Added Emergency Vehicle: " << vehicleID 
                     << ", Path: " << path 
                     << ", Priority: " << priority << endl;
                     */
            
        }
    }

    file.close();
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
class Signal{
    public:
     char intersection;
     int greenTime;
     int vehicleDensity;
     bool emergencyVehicle;
     Signal* next;
     
     Signal(char i='*', int g='*', int v=0, bool e=false){
        intersection=i;
        greenTime= g;
        vehicleDensity=v;
        emergencyVehicle= e;
        next=NULL;
     }
    
};
//priority queue (array of object Signal) Maxheap
class PriorityQueue{
     public:
     int capacity;
     int size;
     Signal* queue;
     
     PriorityQueue(){
         size= 0;
         capacity= 26;
         queue= new Signal[capacity];
     }
     
     ~PriorityQueue(){
         delete[] queue;
     }
     
      void swap(Signal& signal1 , Signal& signal2){
             Signal temp=signal1;
             signal1=signal2;
             signal2= temp;
             
	     
      }
      
      void heapify(int index){
            int max=index;
            int right= (2*index)+2;
            int left=(2*index)+1;
            if(right<size){
		    if(queue[right].emergencyVehicle==true && queue[max].emergencyVehicle==false){
		        max=right;
                     }else if(queue[right].vehicleDensity> queue[max].vehicleDensity){
                        max=right;
                     }
            }
            if(left< size){
		    if(queue[left].emergencyVehicle==true && queue[max].emergencyVehicle==false){
		        max=left;
		    }else if(queue[left].vehicleDensity> queue[max].vehicleDensity){
		        max=left;
		    }
            }
            if(max!=index){
                swap(queue[index], queue[max]);
                heapify(max);
            }
            
      }
      void add(Signal signal){
         if(size<capacity){
            queue[size]=signal;
            int curr= size;
            size++;
            
            while(curr!=0 && queue[curr].vehicleDensity> queue[(curr- 1)/2].vehicleDensity){
            if(queue[curr].emergencyVehicle==false && queue[(curr- 1)/2].emergencyVehicle==true){
                swap(queue[curr],queue[(curr- 1)/2]);
                curr= (curr-1) /2;
            }else if(queue[curr].emergencyVehicle==false && queue[(curr- 1)/2].emergencyVehicle==false && queue[curr].vehicleDensity> queue[(curr- 1)/2].vehicleDensity){
               swap(queue[curr],queue[(curr- 1)/2]);
               curr= (curr-1) /2;
            }else{
                break;
            }
            }
         }
      }
      Signal del_getMax(){
          if(size>0){
             Signal max=queue[0];
             queue[0]= queue[size-1];
             size--;
             
             heapify(0);
             return max;
          }
      }
};
//list storing all intersections with their green time
class SignalList{
    public:
       Signal* head;
       SignalList(){
          head=NULL;
       }
       
       void addSignal(char i,int g){
          Signal* newsignal= new Signal(i,g);
           if(head==NULL){
              head=newsignal;
           }else{
             Signal* temp=head;
               while(temp->next!=NULL){
                   temp=temp->next;
               }
               temp->next=newsignal;
           }
       }
       
       void display(){
             cout<<"-----Traffic Signal Status-----"<<endl;
             Signal* temp=head;
             while(temp!=NULL){
                 cout<<"Intersection "<<temp->intersection<<" Green Time: "<<temp->greenTime<<"s"<<endl;
                  temp=temp->next;
             }
         
         }
};

class TrafficSignalManagement{
     public:
        SignalList signals;
        PriorityQueue queue;
        void loadData(){
	    string line;
	    string info;
	   
	    int greenTime;
	    char intersection;
	    int lines=0;
	    
	    
	    ifstream myFile("traffic_signals.csv");
	    
	    while(getline(myFile, line)){
		if(lines!=0 && !line.empty()){
		
		  stringstream ss(line);
	          
	          getline(ss, info, ',');
	          intersection= info[0];
	          
	          getline(ss, info, ',');
	          greenTime= stoi(info);
	         
	          signals.addSignal(intersection, greenTime);
	          
	          }
	         
	         lines++;
	    
	   
	      }
	    myFile.close();
         } 
         void addVehicleDensity(){
              
         }
         void addEmergencyVehicle(){}
         void addToHeap(){
             Signal* temp= signals.head;
             while(temp!=NULL){
                queue.add(*temp);
                temp=temp->next;
             }
         }
         void CalculateGreenTime(){}
         
         void display(){
             signals.display();
         }
};


int main() {
  bool exit= false;
  RoadClosure closure;
  CongestionMonitoring roads;
  closure.loadData();
 // TrafficSignalManagement traffic;
 // traffic.loadData();
    int totalVertexs = 26; 
    roadNetworks city(totalVertexs);  
    read_and_Build(city); 
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
            cout<<"Assigning shortest path to vehicles:"<<endl;
            city.read_vehicle();
            city.read_And_addVehicle(roads);
            roads.display();
            break;
    case 4:
            closure.display();
             break;
    case 5:
            cout<<"Adding emergency vehicles:" <<endl;
            city.readEmergencyVehicles(); 
            cout<<"All Vehicles and Paths:" <<endl;
            for(int i = 0; i < city.T_vehicle; i++) 
            {
             if (!city.v[i].V.empty()) {
                 cout << "Vehicle: " << city.v[i].V 
                 << ", Path: " << city.v[i].path 
                 << ", Priority: " << city.v[i].priority << endl;
                                       }
            }
            city.handleEmergencyVehicle();
               break;
    case 6:
              closure.blockRoad();
              city.handleEmergencyVehicle();
               break;
    case 7:
               break;
    case 8:
               exit= true;
               break;
    default:
               cout<<"Invalid Choice!"<<endl;
               break;
        }
}
    return 0;

    
}
