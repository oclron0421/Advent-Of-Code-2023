#include <iostream> 
#include <fstream>
#include <string>
#include <cstring> 
#include <vector>
#include <sstream> 
#include <cmath>
using namespace std; 

string filename = "day4.txt";

int main(){
    ifstream infile(filename);
    string currentLine;
    int score;
    int scoreSum = 0;   
    while(!infile.eof()){
        getline(infile, currentLine);
        vector<int> winningNums;
        vector<int> nums;
        currentLine.erase(0,10);
        cout<<currentLine<<endl;
        size_t found = currentLine.find("|");
        string winningNumbers = currentLine.substr(0, found);
        string numbers = currentLine.substr(found+2);
        
        int winningNum;
        istringstream iss1(winningNumbers);
        while(iss1 >> winningNum){
            winningNums.push_back(winningNum);
        }

        int num; 
        istringstream iss2(numbers);
        while(iss2 >> num){
            nums.push_back(num);
        }

        vector<int>::iterator winningItr;
        vector<int>::iterator numItr; 
        
        for(winningItr=winningNums.begin(); winningItr<winningNums.end(); winningItr++){
            for(numItr=nums.begin(); numItr<nums.end(); numItr++){
                if((*winningItr)==(*numItr)){
                    score++;
                    cout<<score<<endl;
                }
            }
        }
        
        scoreSum+=pow(2, (score-1));
        score = 0; 
        cout<<"Sum:"<<scoreSum<<endl;
    }

    cout<<"FINAL Sum:"<<scoreSum<<endl;

    return 0; 
}