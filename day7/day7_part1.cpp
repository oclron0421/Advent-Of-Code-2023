#include <iostream> 
#include <fstream> 
#include <vector> 
#include <map> 
#include <array> 
#include <unordered_map>
#include <sstream> 
#include <string> 
#include <cstring> 
#include <algorithm> 
#include <cmath> 
using namespace std;

string filename = "day7.txt";
array<char, 13> cards = {'A', 'K', 'Q', 'J', 'T', '9', '8', '7', '6', '5', '4', '3', '2'};
unordered_map<char, int> cardValues = {
        {'A', 12},
        {'K', 11},
        {'Q', 10},
        {'J', 9},
        {'T', 8},
        {'9', 7},
        {'8', 6},
        {'7', 5},
        {'6', 4},
        {'5', 3},
        {'4', 2},
        {'3', 1},
        {'2', 0}
    };

int product = 0;  

class Deal{
    public: 
        string hand; 
        int bid; 
        int value;
        map<char, int> dupesInHand; 
        int decValue = 0;  
    Deal(string h, int b){
        hand = h; 
        bid = b; 
        for(int i = 0; i<h.length(); i++){
            decValue += cardValues.at(h.at(i))*pow(13,(h.length()-(i+1)));
        }
    }
};

int cardCount(string card, char targetCard){
    int count = 0; 
    for(int i = 0 ; i < card.length(); i++){
        if(card.at(i)==targetCard){
            count++;
        }
    }
    return count; 
}

bool compareByDecValue(Deal a, Deal b){
    return (a.decValue>b.decValue);
}

void printDealVector(vector<Deal>x){
    vector<Deal>::iterator itr; 
    for(itr = x.begin(); itr != x.end(); itr++){
        cout<<(*itr).hand<<endl;
    }
}

void assignRank(vector<Deal>& x, int& rank){
    vector<Deal>::iterator itr;
    for(itr = x.begin(); itr != x.end(); itr++){
        cout<<rank<<endl;
        (*itr).value = rank * (*itr).bid; 
        rank--;
    }
}

int getVectorValues(vector<Deal> x){
    vector<Deal>::iterator itr;
    int sum = 0; 
    for(itr = x.begin(); itr != x.end(); itr++){
        sum+=(*itr).value;
        // cout<<(*itr).value<<endl;
    }
    return sum; 
}

int main(){
    int rank = 0; 
    vector<Deal> deals; 
    vector<Deal> fiveOfAKind, fourOfAKind, fullHouse, threeOfAKind, twoPair, onePair, highCard; 
    ifstream ifile(filename);
    while(!ifile.eof()){
        string currentLine; 
        string storedHand;
        int storedBid; 
        getline(ifile, currentLine); 
        istringstream iss1(currentLine);
        iss1>>storedHand>>storedBid; 
        deals.emplace_back(storedHand, storedBid);
        rank++;
    }
    cout<<"rank: "<<rank;
    vector<Deal>::iterator dealItr; 
    for(dealItr = deals.begin(); dealItr<deals.end(); dealItr++){
        for(int i = 0; i < cards.size() ; i++){
            if(cardCount((*dealItr).hand, cards[i])>0){
                (*dealItr).dupesInHand.insert(pair<char, int>(cards[i],cardCount((*dealItr).hand, cards[i])));
                if(cardCount((*dealItr).hand, cards[i])==5){
                    fiveOfAKind.push_back((*dealItr));
                }else if (cardCount((*dealItr).hand, cards[i])==4){
                    fourOfAKind.push_back((*dealItr));
                }
            }
        }
    }
    
    for(dealItr = deals.begin(); dealItr<deals.end(); dealItr++){
        bool triples = false; 
        bool pair1 = false; 
        bool pair2 = false;
        bool penta = false; 
        bool quadra = false; 
        for(map<char, int>::iterator itr = (*dealItr).dupesInHand.begin();
             itr != (*dealItr).dupesInHand.end(); itr++){
            // cout<<"Card: "<<itr->first
            //     <<" Count: "<<itr->second<<endl;
            if(itr->second == 3){
                triples = true; 
            }else if (itr->second == 2 && !pair1){
                pair1 = true; 
            }else if (itr->second == 2 && pair1){
                pair2=true; 
            }else if (itr->second ==4){
                quadra = true; 
            }else if (itr->second == 5){
                penta = true;
            }
        }
        if(triples && !pair1 && !pair2 && !quadra && !penta){
            threeOfAKind.push_back((*dealItr));
        }else if(triples && pair1 && !pair2 && !quadra && !penta){
            fullHouse.push_back((*dealItr));
        }else if(!triples && pair1 && pair2 && !quadra && !penta){
            twoPair.push_back((*dealItr));
        }else if(!triples && pair1 && !pair2 && !quadra && !penta){
            onePair.push_back((*dealItr));
        }else if(!triples && !pair1 && !pair2 && !quadra && !penta){ 
            highCard.push_back((*dealItr));
        }
    }

    //sort the deals in the five of a kind vector first 


    sort(fiveOfAKind.begin(), fiveOfAKind.end(), compareByDecValue);
    sort(fourOfAKind.begin(), fourOfAKind.end(), compareByDecValue);
    sort(fullHouse.begin(), fullHouse.end(), compareByDecValue);
    sort(threeOfAKind.begin(), threeOfAKind.end(), compareByDecValue);
    sort(twoPair.begin(), twoPair.end(), compareByDecValue);
    sort(onePair.begin(), onePair.end(), compareByDecValue);
    sort(highCard.begin(), highCard.end(), compareByDecValue);
    
    printDealVector(fiveOfAKind); cout<<endl;
    printDealVector(fourOfAKind);cout<<endl;
    printDealVector(fullHouse);cout<<endl;
    printDealVector(threeOfAKind);cout<<endl;
    printDealVector(twoPair);cout<<endl;
    printDealVector(onePair);cout<<endl;
    printDealVector(highCard);cout<<endl;

    assignRank(fiveOfAKind, rank);
    assignRank(fourOfAKind, rank);
    assignRank(fullHouse, rank);
    assignRank(threeOfAKind, rank);
    assignRank(twoPair, rank);
    assignRank(onePair, rank);
    assignRank(highCard, rank);

    product=getVectorValues(fiveOfAKind)
            +getVectorValues(fourOfAKind)
            +getVectorValues(fullHouse)
            +getVectorValues(threeOfAKind)
            +getVectorValues(twoPair)
            +getVectorValues(onePair)
            +getVectorValues(highCard);

    cout<<endl<<product;

    return 0; 
}