#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <regex>
#include <map>

using namespace std;

int partOne(vector<string> inputList)
{
    int output = 0;
    map<string, int> maxValues = {{"blue", 14},
                                  {"red", 12},
                                  {"green", 13}};
    for (string line : inputList)
    {
        regex game("Game\\s(\\d+)");
        smatch game_match;
        int id;
        if (regex_search(line, game_match, game))
        {
            id = stoi(game_match[1]);
        }

        line = game_match.suffix().str();

        regex color("(\\d+)\\s(blue|red|green)");
        smatch color_match;
        stringstream colorStream(line);
        string draw;
        map<string, int> maxColor = {};
        while (getline(colorStream, draw, ';'))
        {
            while (regex_search(draw, color_match, color))
            {
                int amount = stoi(color_match[1]);
                string color = color_match[2];
                auto result = maxColor.emplace(color, amount);
                if (!result.second)
                {
                    int val = maxColor.at(color);
                    if (val < amount)
                    {
                        maxColor.at(color) = amount;
                    }
                }
                draw = color_match.suffix().str();
            }
        }
        if (maxValues.at("green") < maxColor.at("green"))
        {
            continue;
        }
        if (maxValues.at("blue") < maxColor.at("blue"))
        {
            continue;
        }
        if (maxValues.at("red") < maxColor.at("red"))
        {
            continue;
        }
        output += id;
    }
    return output;
}

int partTwo(vector<string> inputList)
{
    int output = 0;
    for (string line : inputList)
    {
        line = line.erase(0, line.find(':') + 2);

        regex color("(\\d+)\\s(blue|red|green)");
        smatch color_match;
        stringstream colorStream(line);
        string draw;
        map<string, int> maxColor = {};
        while (getline(colorStream, draw, ';'))
        {
            while (regex_search(draw, color_match, color))
            {
                int amount = stoi(color_match[1]);
                string color = color_match[2];
                auto result = maxColor.emplace(color, amount);
                if (!result.second)
                {
                    int val = maxColor.at(color);
                    if (val < amount)
                    {
                        maxColor.at(color) = amount;
                    }
                }
                draw = color_match.suffix().str();
            }
        }
        output += maxColor.at("red") * maxColor.at("green") * maxColor.at("blue");
    }

    return output;
}
int main()
{
    ifstream infile("day2.txt");
    vector<string> inputList{};
    string line;
    while (getline(infile, line))
    {
        inputList.push_back(line);
    }
    infile.close();

    cout << partOne(inputList) << endl;
    cout << partTwo(inputList) << endl;
    
    return 0;
}