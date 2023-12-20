#include <iostream> 
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cstring>
#include <list> 
using namespace std; 

string filename = "day4.txt";

bool is_num(char c) {
    return ('0' <= c && c <= '9');
}


void parse_game_num(std::string line, int &pos) {
    while (line[pos] != ':') {
        pos++;
    }
    while (!is_num(line[pos])) {
        pos++;
    }
}

int parse_num(std::string line, int &pos) {
    int val = 0;

    while (is_num(line[pos]) && pos < line.length()) {
        val = (val * 10) + (line[pos] - '0');
        pos++;
    }

    return val;
}

void parse_numbers_had(std::string line, std::list<int> &numbers_had, int &pos) {
    while (line[pos] != '|' && pos < line.length()) {
        if (is_num(line[pos])) {
            int num = parse_num(line, pos);
            numbers_had.push_back(num);
            pos++;
        }
        else {
            pos++;
        }
    }
}


void parse_winning_numbers(std::string line, std::list<int> &winning_numbers, int &pos) {
    while (pos < line.length()) {
        if (is_num(line[pos])) {
            int num = parse_num(line, pos);
            winning_numbers.push_back(num);
            pos++;
        }
        else {
            pos++;
        }
    }
}


void parse_line(std::string line, std::list<int> &numbers_had, std::list<int> &winning_numbers) {
    int pos=0;
    parse_game_num(line, pos);
    parse_numbers_had(line, numbers_had, pos);
    parse_winning_numbers(line, winning_numbers, pos);
}

int calculate_matches(std::list<int> numbers_had, std::list<int> winning_numbers) {
    int num_matches = 0;

    numbers_had.sort();
    winning_numbers.sort();

    for (auto number_owned : numbers_had) {
        for (auto winning_number : winning_numbers) {
            if (number_owned == winning_number) {
                num_matches++;
            }
        }
    }

    return num_matches;
}

int calculate_score(int num_matches) {
    int score = 0;
    if (num_matches > 0) {
        score = 1;
        for (int i=1; i<num_matches; i++) {
            score *= 2;
        }
    }

    return score;
}

int main(int argc, char **argv){
    
    fstream input_file;
    string currentline;
    input_file.open("day4.txt");
    const int cards_num = 223;
    int cardCopies[cards_num];
    int cardMatches[cards_num];

    //fill the array with one cause at least one card 
    for(int i = 0; i<cards_num; i++){
        cardCopies[i]=1;
    }

    int line = 0; 
    int total_score = 0;
    while (getline(input_file, currentline)) {
        std::list<int> numbers_had;
        std::list<int> winning_numbers;
        parse_line(currentline, numbers_had, winning_numbers);
        int num_matches = calculate_matches(numbers_had, winning_numbers);
        cardMatches[line] = num_matches;
        line++;
        total_score += calculate_score(num_matches);
    }
    for(int i = 0; i<224; i++){
        cout<<cardMatches[i]<<" ";
    }
    int totalCards = 0; 
    for(int currentCards = 0; currentCards<cards_num; currentCards++){
        if(cardMatches[currentCards]>0){
            for(int i = 1; currentCards + i < cards_num && i < cardMatches[currentCards]+1 ; i++){
                for(int j = 0; j < cardCopies[currentCards];j++){
                    cardCopies[currentCards+i]+=1;
                }
            }
        }
    }

    for(int i=0; i<cards_num;i++){
        totalCards+=cardCopies[i];
    }

    cout<<totalCards;
    return 0;
}