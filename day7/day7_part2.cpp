#include <iostream> 
#include <fstream> 
#include <sstream> 
#include <vector> 
#include <unordered_map>
#include <map> 
#include <algorithm> 
#include <string> 
#include <array> 
#include <cstring> 
#include <cmath>
using namespace std; 

string filename = "day7.txt";
array<char, 13> cards = {'A', 'K', 'Q', 'J', 'T', '9', '8', '7', '6', '5', '4', '3', '2'};
unordered_map<char, int> cardValues = {
        {'A', 12},
        {'K', 11},
        {'Q', 10},
        {'T', 9},
        {'9', 8},
        {'8', 7},
        {'7', 6},
        {'6', 5},
        {'5', 4},
        {'4', 3},
        {'3', 2},
        {'2', 1},
        {'J', 0}
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


void assignRank(vector<Deal>& x, int& rank){
    vector<Deal>::iterator itr;
    for(itr = x.begin(); itr != x.end(); itr++){
        cout<<rank<<endl;
        (*itr).value = rank * (*itr).bid; 
        rank--;
    }
}

bool compareByDecValue(Deal a, Deal b){
    return (a.decValue>b.decValue);
}

int checkHand(Deal x){
    int result = -1;
    bool penta = false; 
    bool quadra = false; 
    bool triples = false; 
    bool pair1 = false; 
    bool pair2 = false; 

    for(map<char, int>::iterator itr = x.dupesInHand.begin();
        itr != x.dupesInHand.end(); itr++ ){
            if(itr->second == 5){ 
                penta = true;
            } else if(itr->second == 4){
                quadra = true; 
            } else if(itr->second == 3){
                triples =true;
            } else if(itr->second == 2 && !pair1){
                pair1 = true;
            } else if(itr->second == 2 && pair1){
                pair2 = true;
            }
        }
    
    if(penta&&!quadra&&!triples&&!pair1&&!pair2){
        result = 5;     //five of a kind
    }else if(!penta&&quadra&&!triples&&!pair1&&!pair2){
        result = 41;    //four of a kind
    }else if(!penta&&!quadra&&triples&&pair1&&!pair2){
        result = 32;    //full house
    }else if(!penta&&!quadra&&triples&&!pair1&&!pair2){
        result = 311;   //three of a kind
    }else if(!penta&&!quadra&&!triples&&pair1&&pair2){
        result = 221;   //two pairs
    }else if(!penta&&!quadra&&!triples&&pair1&&!pair2){
        result = 2111;  //one pair
    }else if(!penta&&!quadra&&!triples&&!pair1&&!pair2){
        result = 0;     //high card
    }
    return result; 
}

int cardCount(string card, char targetCard){
    int count = 0; 
    for(int i = 0 ; i < card.length(); i++){
        if(card.at(i)==targetCard){
            count++;
        }
    }
    return count; 
}
int checkJokers(string card){
    int count = 0;
    for(int i = 0; i<card.length(); i++){
        if(card.at(i)=='J'){
            count++;
        }
    }
    return count;
}

void printDealVector(vector<Deal>x){
    vector<Deal>::iterator itr; 
    for(itr = x.begin(); itr != x.end(); itr++){
        cout<<(*itr).hand<<endl;
        map<char, int>::iterator mapItr; 
        for(mapItr=(*itr).dupesInHand.begin();mapItr!=(*itr).dupesInHand.end();mapItr++){
            cout<<"Key: "<<mapItr->first<<" Value: "<<mapItr->second<<endl;
        }
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
    vector<Deal> deals, dealsWithJ; 
    vector<Deal> fiveOfAKind, fourOfAKind, fullHouse, threeOfAKind, twoPair, onePair, highCard; 
    ifstream ifile(filename);
    while(!ifile.eof()){
        string currentLine; 
        string storedHand;
        int storedBid; 
        getline(ifile, currentLine); 
        istringstream iss1(currentLine);
        iss1>>storedHand>>storedBid; 
        
        if(storedHand.find("J")!=std::string::npos){
            dealsWithJ.emplace_back(storedHand, storedBid);
        }else {
            deals.emplace_back(storedHand, storedBid);
        }
        rank++;
    }

    vector<Deal>::iterator dealItr; 
    for(dealItr = deals.begin(); dealItr<deals.end(); dealItr++){
        for(int i = 0; i < cards.size() ; i++){
            if(cardCount((*dealItr).hand, cards[i])>0){
                (*dealItr).dupesInHand.insert(pair<char, int>(cards[i],cardCount((*dealItr).hand, cards[i])));
            }
        }
        if(checkHand(*dealItr)==5){
            fiveOfAKind.push_back(*dealItr);
        }else if(checkHand(*dealItr)==41){
            fourOfAKind.push_back(*dealItr);
        }else if(checkHand(*dealItr)==32){
            fullHouse.push_back(*dealItr);
        }else if(checkHand(*dealItr)==311){
            threeOfAKind.push_back(*dealItr);
        }else if(checkHand(*dealItr)==221){
            twoPair.push_back(*dealItr);
        }else if(checkHand(*dealItr)==2111){
            onePair.push_back(*dealItr);
        }else if(checkHand(*dealItr)==0){
            highCard.push_back(*dealItr);
        }
    }
    
    for(dealItr = dealsWithJ.begin(); dealItr<dealsWithJ.end();dealItr++){
        for(int i = 0; i < cards.size() ; i++){
            if(cardCount((*dealItr).hand, cards[i])>0){
                (*dealItr).dupesInHand.insert(pair<char, int>(cards[i],cardCount((*dealItr).hand, cards[i])));
            }
        }
        if((checkHand(*dealItr)==5)){
            if((*dealItr).hand=="JJJJJ"){
                (*dealItr).hand = "AAAAA";
                fiveOfAKind.push_back(*dealItr);
                }
        }else if(checkHand(*dealItr)==41||checkHand(*dealItr)==32){
            int nonJ = (*dealItr).hand.find_first_not_of('J');
            char toChange = (*dealItr).hand.at(nonJ);
            for(int i = 0; i < (*dealItr).hand.length(); i++){
                if((*dealItr).hand.at(i)=='J'){
                    (*dealItr).hand[i] = toChange;
                }
            }
            fiveOfAKind.push_back(*dealItr);
        }else if(checkHand(*dealItr)==311){
            //check for the highest card of the 2 and then make the jokers into them 
            char highestCard = 'J';
            for(int i = 0; i<(*dealItr).hand.length();i++){
                if(cardValues[(*dealItr).hand.at(i)]>cardValues[highestCard]){
                    highestCard = (*dealItr).hand.at(i);
                }
            }
            for(int i = 0; i < (*dealItr).hand.length(); i++){
                if((*dealItr).hand.at(i)=='J'){
                    (*dealItr).hand[i] = highestCard;
                }
            }
            fourOfAKind.push_back(*dealItr);
        }else if(checkHand(*dealItr)==221){
            //if joker pair = 4 of a kind,  if not full house 
            int noOfJokers = checkJokers((*dealItr).hand);
            if(noOfJokers == 2){
                char toChange;
                map<char,int>::iterator mapItr; 
                for(mapItr = (*dealItr).dupesInHand.begin(); mapItr != (*dealItr).dupesInHand.end(); mapItr++){
                    if(mapItr->second==2){
                        toChange = mapItr->first;
                        break;
                    }
                }
                for(int i = 0; i<(*dealItr).hand.length();i++){
                    if((*dealItr).hand.at(i)=='J'){
                        (*dealItr).hand[i] = toChange;
                    }
                }
                fourOfAKind.push_back(*dealItr);
            }else if(noOfJokers==1){
                char toChange; 
                map<char, int>::iterator mapItr; 
                mapItr = (*dealItr).dupesInHand.begin();
                toChange = mapItr->first; 
                for(int i = 0; i<(*dealItr).hand.length();i++){
                    if((*dealItr).hand.at(i)=='J'){
                        (*dealItr).hand[i] = toChange;
                    }  
                }
                fullHouse.push_back(*dealItr);
            }
        }else if(checkHand(*dealItr)==2111){
            char highestCard = 'J';
            for(int i = 0; i<(*dealItr).hand.length();i++){
                if(cardValues[(*dealItr).hand.at(i)]>cardValues[highestCard]){
                    highestCard = (*dealItr).hand.at(i);
                }
            }
            for(int i = 0; i < (*dealItr).hand.length(); i++){
                if((*dealItr).hand.at(i)=='J'){
                    (*dealItr).hand[i] = highestCard;
                }
            } 
            threeOfAKind.push_back(*dealItr); 
        }else if(checkHand(*dealItr)==0){
            char highestCard; 
            map<char, int>::iterator mapItr; 
            mapItr = (*dealItr).dupesInHand.begin();
            highestCard = mapItr->first;
            for(int i = 0; i < (*dealItr).hand.length(); i++){
                if((*dealItr).hand.at(i)=='J'){
                    (*dealItr).hand[i] = highestCard;
                }
            } 
            onePair.push_back(*dealItr);
        }
    }
    
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