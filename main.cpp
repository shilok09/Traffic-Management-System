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

int main() {
    int totalVertexs = 26; 
    roadNetworks city(totalVertexs);  
    read_and_Build(city);  
    city.displayRoad(); 
}
