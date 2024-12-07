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

void ShortestPath(char start,char end) 
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
}
else 
{
cout<<"Shortest distance:"<<dist[e]<<endl;
char a=end;
int i=-1;
a=end;
i=-1;
char s1=start;
int s2;
char s3=end;
cout<<start;
while(a!=p[end-'A']) 
{       
        s3=end;
        cout<<"->";
        while(p[i]!=s1)
        {
            s2=i;
            i=s3-'A';
            s3=p[i];
        }
        a=p[s2];
        cout<<a; 
        s1=a;
}
cout<<"->";
cout<<end<<endl;

delete[] dist;
    delete[] p;
    delete[] v;
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
    char start;
    char end;
    cout<<"Enter points: "<<endl;
    cout<<"Start: ";
    cin>>start;
    cout<<"  End: ";
    cin>>end;
    city.ShortestPath(start, end);
}