#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;

string filename = "day3.txt";
string first, second, third; 
int sum = 0; 
char arr[140][140];
int main(){
    ifstream file(filename);
    string line;
    int lineNo=0;
    int num;
    while(getline(file, line)){
        for(int i = 0; i<line.size();i++){
            arr[lineNo][i]=line[i];
        }
        lineNo++;
    }

    for(int i = 0; i < 140; i++){
        for(int j = 0; j < 140; j++){
            
            if(isdigit(arr[i][j])){
                first = arr[i][j];
                if(isdigit(arr[i][j+1])){
                    j++;
                    second = arr[i][j];
                    if(isdigit(arr[i][j+1])){
                        j++;
                        third = arr[i][j];
                        num = stoi(first.append(second.append(third)));
                        
                        //check for any other dots around the number 
                        if(!((i-1)<0)){       //check if there is a row above the number or not
                            if((i+1)<139){
                                if((j-3)<0){
                                    if(arr[i-1][j]!='.'||arr[i-1][j-1]!='.'||arr[i-1][j-2]!='.'||arr[i-1][j+1]!='.'
                                    ||arr[i][j+1]!='.'
                                    ||arr[i+1][j-2]!='.'||arr[i+1][j-1]!='.'||arr[i+1][j]!='.'||arr[i+1][j+1]!='.'){
                                        cout<<"42:"<<num<<endl;
                                        sum+=num;
                                    }
                                }
                                else if((j+1)>139){
                                    if(arr[i-1][j-3]!='.'||arr[i-1][j-2]!='.'||arr[i-1][j-1]!='.'||arr[i-1][j]!='.'
                                    ||arr[i][j-3]!='.'
                                    ||arr[i+1][j-3]!='.'||arr[i+1][j-2]!='.'||arr[i+1][j-1]!='.'||arr[i+1][j]!='.'){
                                        cout<<"50:"<<num<<endl;
                                        sum+=num;
                                    }
                                }else{
                                    if(arr[i-1][j-3]!='.'||arr[i-1][j-2]!='.'||arr[i-1][j-1]!='.'||arr[i-1][j]!='.'||arr[i-1][j+1]!='.'
                                    ||arr[i][j-3]!='.'||arr[i][j+1]!='.'
                                    ||arr[i+1][j-3]!='.'||arr[i+1][j-2]!='.'||arr[i+1][j-1]!='.'||arr[i+1][j]!='.'||arr[i+1][j+1]!='.'){
                                        cout<<"57:"<<num<<endl;
                                        sum+=num;
                                    }
                                }
                            }else{
                                if(j-3<0){
                                    if(arr[i-1][j-2]!='.'||arr[i-1][j-1]!='.'||arr[i-1][j]!='.'||arr[i-1][j+1]!='.'
                                    ||arr[i][j+1]!='.'){
                                        cout<<"65:"<<num<<endl;
                                        sum+=num;
                                    }
                                }else if(j+1>139){
                                    if(arr[i-1][j-3]!='.'||arr[i-1][j-2]!='.'||arr[i-1][j-1]!='.'||arr[i-1][j]!='.'
                                    ||arr[i][j-3]!='.'){
                                        cout<<"71:"<<num<<endl;
                                        sum+=num; 
                                    }
                                }else{
                                    if(arr[i-1][j-3]!='.'||arr[i-1][j-2]!='.'||arr[i-1][j-1]!='.'||arr[i-1][j]!='.'||arr[i-1][j+1]!='.'
                                    ||arr[i][j-3]!='.'||arr[i][j+1]!='.'){
                                        cout<<"77:"<<num<<endl;
                                        sum+=num;
                                    }
                                }
                            } 
                        }else{
                            if(j-3<0){
                                if(arr[i][j+1]
                                    ||arr[i+1][j-2]!='.'||arr[i+1][j-1]!='.'||arr[i+1][j]!='.'||arr[i+1][j+1]!='.'){
                                    cout<<"86:"<<num<<endl;
                                    sum+=num;
                                }
                            }
                            else if(j+1>139){
                                if(arr[i][j-3]!='.'
                                    ||arr[i+1][j-3]!='.'||arr[i+1][j-2]!='.'||arr[i+1][j-1]!='.'||arr[i+1][j]!='.'){
                                    cout<<"93:"<<num<<endl;
                                    sum+=num;
                                }
                            }else{
                                if(arr[i][j-3]!='.'||arr[i][j+1]!='.'
                                ||arr[i+1][j-3]!='.'||arr[i+1][j-2]!='.'||arr[i+1][j-1]!='.'||arr[i+1][j]!='.'||arr[i+1][j+1]!='.'){
                                    cout<<"99:"<<num<<endl;
                                    sum+=num;
                                }
                            }
                        }
                    }else {
                        num = stoi(first.append(second));
                        if(!(i-1<0)){       //check if there is a row above the number or not
                            if((i+1)<140){
                                if(j-2<0){
                                    if(arr[i-1][j]!='.'||arr[i-1][j-1]!='.'||arr[i-1][j+1]!='.'
                                    ||arr[i][j+1]!='.'
                                    ||arr[i+1][j-1]!='.'||arr[i+1][j]!='.'||arr[i+1][j+1]!='.'){
                                        cout<<"113:"<<num<<endl;
                                        sum+=num;
                                    }
                                }
                                else if(j+1>139){
                                    if(arr[i-1][j-2]!='.'||arr[i-1][j-1]!='.'||arr[i-1][j]!='.'
                                    ||arr[i][j-2]!='.'
                                    ||arr[i+1][j-2]!='.'||arr[i+1][j-1]!='.'||arr[i+1][j]!='.'){
                                        cout<<"121:"<<num<<endl;
                                        sum+=num;
                                    }
                                }else{
                                    if(arr[i-1][j-2]!='.'||arr[i-1][j-1]!='.'||arr[i-1][j]!='.'||arr[i-1][j+1]!='.'
                                    ||arr[i][j-2]!='.'||arr[i][j+1]!='.'
                                    ||arr[i+1][j-2]!='.'||arr[i+1][j-1]!='.'||arr[i+1][j]!='.'||arr[i+1][j+1]!='.'){
                                        cout<<"128:"<<num<<endl;
                                        sum+=num;
                                    }
                                }
                            }else{
                                if(j-2<0){
                                    if(arr[i-1][j-1]!='.'||arr[i-1][j]!='.'||arr[i-1][j+1]!='.'
                                    ||arr[i][j+1]!='.'){
                                        cout<<"136:"<<num<<endl;
                                        sum+=num;
                                    }
                                }else if(j+1>139){
                                    if(arr[i-1][j-2]!='.'||arr[i-1][j-1]!='.'||arr[i-1][j]!='.'
                                    ||arr[i][j-2]!='.'){
                                        cout<<"142:"<<num<<endl;
                                        sum+=num; 
                                    }
                                }else{
                                    if(arr[i-1][j-2]!='.'||arr[i-1][j-1]!='.'||arr[i-1][j]!='.'||arr[i-1][j+1]!='.'
                                    ||arr[i][j-2]!='.'||arr[i][j+1]!='.'){
                                        cout<<"148:"<<num<<endl;
                                        sum+=num;
                                    }
                                }
                            } 
                        }else{
                            if(j-2<0){
                                if(arr[i][j+1]!='.'
                                    ||arr[i+1][j-1]!='.'||arr[i+1][j]!='.'||arr[i+1][j+1]!='.'){
                                    cout<<"157:"<<num<<endl;
                                    sum+=num;
                                }
                            }
                            else if(j+1>139){
                                if(arr[i][j-2]!='.'
                                    ||arr[i+1][j-2]!='.'||arr[i+1][j-1]!='.'||arr[i+1][j]!='.'){
                                    cout<<"164:"<<num<<endl; 
                                    sum+=num;
                                }
                            }else{
                                if(arr[i][j-2]!='.'||arr[i][j+1]!='.'
                                ||arr[i+1][j-2]!='.'||arr[i+1][j-1]!='.'||arr[i+1][j]!='.'||arr[i+1][j+1]!='.'){
                                    cout<<"170:"<<num<<endl;
                                    sum+=num;
                                }
                            }
                        }
                    }
                }else{ 
                    num = stoi(first);
                        if(!(i-1<0)){       //check if there is a row above the number or not
                            if((i+1)<140){
                                if(j-1<0){
                                    if(arr[i-1][j]!='.'||arr[i-1][j+1]!='.'
                                    ||arr[i][j+1]!='.'
                                    ||arr[i+1][j]!='.'||arr[i+1][j+1]!='.'){
                                        cout<<"184:"<<num<<endl;
                                        sum+=num;
                                    }
                                }
                                else if(j+1>139){
                                    if(arr[i-1][j-1]!='.'||arr[i-1][j]!='.'
                                    ||arr[i][j-1]!='.'
                                    ||arr[i+1][j-1]!='.'||arr[i+1][j]!='.'){
                                        cout<<"192:"<<num<<endl;
                                        sum+=num;
                                    }
                                }else{
                                    if(arr[i-1][j-1]!='.'||arr[i-1][j]!='.'||arr[i-1][j+1]!='.'
                                    ||arr[i][j-1]!='.'||arr[i][j+1]!='.'
                                    ||arr[i+1][j-1]!='.'||arr[i+1][j]!='.'||arr[i+1][j+1]!='.'){
                                        cout<<"199:"<<num<<endl;
                                        sum+=num;
                                    }
                                }
                            }else{
                                if(j-1<0){
                                    if(arr[i-1][j]!='.'||arr[i-1][j+1]!='.'
                                    ||arr[i][j+1]!='.'){
                                        cout<<"207:"<<num<<endl;
                                        sum+=num;
                                    }
                                }else if(j+1>139){
                                    if(arr[i-1][j-1]!='.'||arr[i-1][j]!='.'
                                    ||arr[i][j-1]!='.'){
                                        cout<<"213:"<<num<<endl;
                                        sum+=num; 
                                    }
                                }else{
                                    if(arr[i-1][j-1]!='.'||arr[i-1][j]!='.'||arr[i-1][j+1]!='.'
                                    ||arr[i][j-1]!='.'||arr[i][j+1]!='.'){
                                        cout<<"219:"<<num<<endl;
                                        sum+=num;
                                    }
                                }
                            } 
                        }else{
                            if(j-1<0){
                                if(arr[i][j+1]!='.'
                                    ||arr[i+1][j]!='.'||arr[i+1][j+1]!='.'){
                                    cout<<"228:"<<num<<endl;
                                    sum+=num;
                                }
                            }
                            else if(j+1>139){
                                if(arr[i][j-1]!='.'
                                    ||arr[i+1][j-1]!='.'||arr[i+1][j]!='.'){
                                    cout<<"235:"<<num<<endl; 
                                    sum+=num;
                                }
                            }else{
                                if(arr[i][j-1]!='.'||arr[i][j+1]!='.'
                                ||arr[i+1][j-1]!='.'||arr[i+1][j]!='.'||arr[i+1][j+1]!='.'){
                                    cout<<"240:"<<num<<endl;
                                    sum+=num;
                                }
                            }
                        }

                }
            }
        }
    }
    cout<<sum;
    return 0;
}

