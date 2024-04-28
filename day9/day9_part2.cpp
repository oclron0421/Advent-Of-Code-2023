#include <iostream> 
#include <vector> 
#include <fstream> 
#include <sstream> 
#include <cstring> 
#include <string> 
#include <algorithm> 
using namespace std; 

string filename = "day9.txt";

bool checkIfZeroVector(vector<int> x){
    vector<int>::iterator itr; 
    for(itr = x.begin(); itr!=x.end(); itr++){
        if(*itr!=0){
            return false;
        }
        // cout<<*itr<<" ";
    }
    return true;
}
int sumOfVector(vector<int> vec){
    int sum = 0; 
    for(int num:vec){
        sum+=num;
    }
    return sum;
}

void alterVector(std::vector<int>& x) {
    for (size_t i = 1; i < x.size(); i += 2) {
        x[i] *= -1;
    }
}

int getNextNumber(vector<int> x){
    vector<int>::iterator itr; 
    int nextNum; 
    vector<int> tempVector; 
    vector<int> toAdd; 
    toAdd.push_back(x.back());
    while(true){
        tempVector.clear();
        for(itr=x.begin(); itr!=x.end()-1; itr++){
            if(itr+1 != x.end()){
                tempVector.push_back(*itr-*(itr+1));
            } else {
                break;
            }
        }
        if(checkIfZeroVector(tempVector)){
            break;
        }
        x = tempVector; 
        toAdd.push_back(tempVector.back());
        // cout<<tempVector.back();
    }
    alterVector(toAdd);

    return sumOfVector(toAdd);
}


int main(){
    ifstream infile(filename);
    vector<vector<int>> seqs;
    int sum = 0; 
    while(!infile.eof()){
        string currentLine;
        int num; 
        vector<int> seq;
        getline(infile, currentLine);
        istringstream iss1(currentLine);
        while(iss1>>num){
            seq.push_back(num);
        }
        reverse(seq.begin(), seq.end());
        seqs.push_back(seq);
    }

    vector<vector<int>>::iterator seqItr; 
    for(seqItr=seqs.begin(); seqItr!=seqs.end(); seqItr++){
        vector<int> x = *seqItr;  // Convert iterator to a vector
        sum += getNextNumber(x);
        cout<<getNextNumber(x)<<endl;
    }
    cout<<sum;

    return 0; 
}