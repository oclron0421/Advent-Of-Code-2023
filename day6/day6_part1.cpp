#include <iostream>
#include <vector> 
#include <array> 
#include <cstring> 
#include <string>  
#include <fstream> 
#include <sstream> 
using namespace std;

string filename = "day6.txt";
long long product = 1; 

class Record{
    public: 
        long long time; 
        long long dist; 
    Record(long long t, long long d){
        time = t; 
        dist = d; 
    }
};

int main(){
    array<long long, 4> times;
    array<long long ,4> dists; 
    ifstream infile(filename);
    vector<Record> records; 
    string currentLine; 
    string result; 
    long long time, dist; 

    getline(infile, currentLine);
    for (char c:currentLine){
        if(isdigit(c)||isspace(c))
            result+=c;
    }
    istringstream iss1(result);
    long long i = 0; 
    while(iss1>>time){
        times[i]=time; 
        cout<<times[i]<<endl;
        i++;
    }
    
    result.clear();
    getline(infile, currentLine);
    for(char c:currentLine){
        if(isdigit(c)||isspace(c))
            result+=c;
    }
    istringstream iss2(result);
    i = 0; 
    while(iss2>>dist){
        dists[i]=dist;
        cout<<dists[i]<<endl;
        i++;
    }

    for(i=0; i<4; i++){
        records.emplace_back(times[i], dists[i]);
    }

    vector<Record>::iterator recordItr;

    for(recordItr = records.begin(); recordItr<records.end(); recordItr++){
        long long count = 0; 
        cout<<(*recordItr).time<<"\t"<<(*recordItr).dist<<endl;
        for(long long pt = 0; pt < (*recordItr).time; pt++){
            // cout<<pt<<endl;
            if((((*recordItr).time - pt)*pt) > (*recordItr).dist){
                count++;
                // cout<<count<<endl;
            }
        }
        product*=count;
    }

    cout<<product<<endl;

    return 0; 
}