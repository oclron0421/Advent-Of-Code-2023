#include <iostream>
#include <fstream> 
#include <sstream> 
#include <cstring> 
#include <unordered_map>
#include <utility>
#include <string>
#include <iterator>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std; 

string filename = "day8.txt";




class Node{
    public:
        string rightBranch; 
        string leftBranch; 
        string node; 
        Node(string r, string l, string n){
            node = n; 
            rightBranch = r; 
            leftBranch = l;
        }
};

int main(){
    int count = 0; 
    ifstream infile(filename);
    string currentLine; 
    getline(infile, currentLine);
    string directions = currentLine; 
    vector<Node> nodes; 
    getline(infile, currentLine);
    while(!infile.eof()){
        getline(infile, currentLine);
        size_t startKey = currentLine.find_first_of("=");
        size_t startValues = currentLine.find_first_of("(");
        size_t endValues = currentLine.find_first_of(")");

        std::string key = currentLine.substr(0, startKey - 1);
        std::string valueString = currentLine.substr(startValues + 1, endValues - startValues - 1);
        size_t commaPos = valueString.find_first_of(",");
        std::string value1 = valueString.substr(0, commaPos);
        std::string value2 = valueString.substr(commaPos + 2); // +2 to skip the space after the comma


        cout<<"Left Node: "<< value1 << " Right Node: "<< value2<<endl;
        nodes.emplace_back(value2, value1, key);
    }


    string::iterator it = directions.begin(); 
    vector<Node>::iterator nodesItr = find_if(nodes.begin(), nodes.end(), [](const Node& node){
                                                                            return node.node == "AAA";
                                                                        }); 
    while (nodesItr != nodes.end() && (*nodesItr).node != "ZZZ") {
        if (it == directions.end()) {
            it = directions.begin();
        }
        cout<<"Node: "<<(*nodesItr).node<<endl;
        if (*it == 'R' && !(*nodesItr).rightBranch.empty()) {
            string rightNode = (*nodesItr).rightBranch;
            nodesItr = find_if(nodes.begin(), nodes.end(), [rightNode](const Node& node) {
                return node.node == rightNode;
            });
            cout<<(*nodesItr).node<<endl;
            cout<<"right"<<endl;
        } else if (*it == 'L' && !(*nodesItr).leftBranch.empty()) {
            string leftNode = (*nodesItr).leftBranch;
            nodesItr = find_if(nodes.begin(), nodes.end(), [leftNode](const Node& node) {
                return node.node == leftNode;
            });
            cout<<(*nodesItr).node<<endl;
            cout<<"left"<<endl;
        } else {
            cout<<"error has occured";
            break;
        }
        ++it;
        count++;
    }
    cout<<count;
    return 0; 
}