#include <iostream> 
#include <vector> 
#include <queue>
#include <fstream> 
#include <string>
#include <cstring> 
#include <sstream> 
#include <array> 
using namespace std; 

string filename = "day5.txt";
long long ID = 1; 
class Map{
    public:
        long long source = 0; 
        long long dest = 0; 
        long long length = 0; 
        long long id = 0; 
    Map(long long s, long long d, long long l, long long Id){
        dest = d; 
        source = s; 
        length = l; 
        id = Id;
    }
};

bool inRange(long long x, long long d, long long r){
    if(x>=d && x<=(d+r))
        return true;
    else 
        return false; 
}

long long findLowestValue(const std::vector<long long>& inputVector) {
    if (inputVector.empty()) {
        // Handle the case where the vector is empty (you may choose to return a special value or throw an exception)
        std::cerr << "Error: Empty vector provided.\n";
        return -1; // Returning -1 as a special value indicating an error or an empty vector
    }

    // Initialize the minimum value with the first element of the vector
    long long minValue = inputVector[0];

    // Iterate through the vector to find the minimum value
    for (size_t i = 1; i < inputVector.size(); ++i) {
        if (inputVector[i] < minValue) {
            minValue = inputVector[i];
        }
    }

    return minValue;
}

int main(){
    vector<Map> maps;
    vector<long long> seeds, locations;
    string line; 
    ifstream infile(filename);
    array <long long, 3> map; 
    getline(infile, line);
    line.erase(0,7);
    long long seed, num; 
    istringstream iss1(line);
    while(iss1>>seed){
        seeds.push_back(seed);
        // cout<<seed<<" ";
    }
    
    while(!infile.eof()){
        //check if its numbers or string 
        getline(infile, line);
        istringstream iss2(line);
        if(isdigit(line.front())){
            long long i = 0; 
            while(iss2>>num && i < 3){
                map[i]=num;
                i++;
            }
            if(!map.empty()){
                maps.push_back(Map(map[0],map[1],map[2], ID-1));
                //cout<<maps.back().dest<<" "<< maps.back().source<< " "<<maps.back().length << " " <<maps.back().id << " "<< endl;
            }
        }
        else{
            ID++;
        }
    }

    vector<long long>::iterator seedItr; 
    vector<Map>::iterator mapItr; 
    long long location = 0; 
    long long id;
    for(seedItr = seeds.begin(); seedItr<seeds.end();seedItr++){
        id = 1;
        location = *seedItr;
        for(mapItr = maps.begin(); mapItr<maps.end(); mapItr++){
            //cout<<(*mapItr).dest<<" "<<(*mapItr).source<<" "<<(*mapItr).length<<" "<<(*mapItr).id<<" "<< id<<endl;
            if(inRange(location, (*mapItr).dest, (*mapItr).length)&&(*mapItr).id==id){
                size_t index = distance(maps.begin(), mapItr);
                // cout<< "Index: "<< index<<" ";
                location =  location + ((*mapItr).source-(*mapItr).dest);
                while (mapItr != maps.end() && (*mapItr).id == id) {
                    mapItr++;
                    index = distance(maps.begin(), mapItr);
                    // cout<< endl<<"Index: "<< index<<" "<<" id "<<(*mapItr).id<<" ";
                }
                id = (*mapItr).id;      
                // cout<<"id "<<id<<" ";
                mapItr--;
                // cout<<location<<" "<<endl; 
            }else {
                location = location;
                // cout<<" not in range ";
                // cout<<location<<" "<<endl;  
                id = (*mapItr).id;
            }
        }
        locations.push_back(location);
        // cout<<endl;
        
        cout<<endl<<location;
    }

    cout<<endl<<findLowestValue(locations);
    
    return 0; 
}