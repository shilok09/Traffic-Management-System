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

class roadNetworks{
private:
    int numOfVertex;
    road **roadKiList;

public:
    roadNetworks(){numOfVertex=0;roadKiList=nullptr;}  
    roadNetworks(int n){  
        numOfVertex = n;
        roadKiList = new road*[n];  //initialising list for storing graph in adjacency list manner
        for (int i = 0; i < n; i++) {
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
};
void read_and_Build(roadNetworks &roads){
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
void read_And_addVehicle(CongestionMonitoring &rastyyy){
    ifstream file("FILE NAME HERE.csv");
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

        rastyyy.add(src, dest); 
    }

    file.close();
}

int main() {
    // int totalVertexs = 26; 
    // roadNetworks city(totalVertexs);  
    // read_and_Build(city);  
    // city.displayRoad(); 
    CongestionMonitoring roads;
    read_And_addVehicle(roads);
    roads.display();
    }

