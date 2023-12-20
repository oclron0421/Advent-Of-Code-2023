#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

int main(){
    ifstream infile;

    vector<int> numberList;

    infile.open("calibration.txt");
    string currentLine, currentNum;
    int digitPos;
    while(!infile.eof()){
        getline(infile, currentLine);

        digitPos = currentLine.find_first_of("1234567890");
        currentNum += currentLine[digitPos];

        digitPos = currentLine.find_last_of("1234567890");
        currentNum += currentLine[digitPos];

        numberList.push_back(stoi(currentNum));

        currentLine.clear();
        currentNum.clear();
    }
    infile.close();

    int sum = 0;
    for(int i = 0; i < numberList.size(); i++){
        cout << numberList.at(i) << endl;
        sum += numberList.at(i);
    }

    cout << "Sum: " << sum << endl;
}