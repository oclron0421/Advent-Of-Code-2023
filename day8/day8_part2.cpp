#include <iostream> 
#include <vector>
#include <fstream> 
#include <cstring> 
#include <string> 
#include <algorithm>
#include <iterator>
#include <numeric> 
using namespace std; 

string filename = "day8.txt";

class Node{
    public:
        string mainNode;
        string rightNode; 
        string leftNode;
        Node(string m, string r, string l){
            mainNode = m;
            rightNode = r;
            leftNode = l;
        }
};

long long findGCD(long long a, long long b) {
    while (b != 0) {
        long long temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// Function to find the least common multiple (LCM) of two numbers
long long findLCM(long long a, long long b) {
    return (a * b) / findGCD(a, b);
}

// Function to find the LCM of a vector of integers
long long findLCMOfVector(const std::vector<long long>& numbers) {
    if (numbers.empty()) {
        return 1;
    }

    long long result = numbers[0];
    for (size_t i = 1; i < numbers.size(); ++i) {
        result = findLCM(result, numbers[i]);
    }

    return result;
}

int main(){
    long long count = 0; 
    ifstream infile(filename);
    string currentLine;
    vector<Node> nodes; 
    vector<long long> counts; 
    getline(infile, currentLine);
    string directions = currentLine;
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
        nodes.emplace_back(key, value2, value1);
    }  

    string::iterator it = directions.begin();
    vector<Node>::iterator nodeItr; 
    for(nodeItr = nodes.begin(); nodeItr != nodes.end(); nodeItr++){
        if((*nodeItr).mainNode.at(2)!='A'){
            continue;
        }else{
            count=0;
            vector<Node>::iterator nodeItr2 = nodeItr;
            while (nodeItr2 != nodes.end() && (*nodeItr2).mainNode.at(2) != 'Z'){
                if(it==directions.end()){
                    it=directions.begin();
                }
                if(*it=='R'&&!(*nodeItr2).rightNode.empty()){
                    string right = (*nodeItr2).rightNode;
                    nodeItr2 = find_if(nodes.begin(), nodes.end(),[right](const Node& node){
                                                            return node.mainNode == right;
                    });
                } else if(*it=='L' && !(*nodeItr2).leftNode.empty()){
                    string left = (*nodeItr2).leftNode;
                    nodeItr2 = find_if(nodes.begin(), nodes.end(), [left](const Node& node){
                                                                    return node.mainNode == left;
                    });
                }
            it++;
            count++;
            }
            cout<<count<<endl;
            counts.push_back(count);
        }
    }
    cout<< findLCMOfVector(counts);
    return 0; 
}