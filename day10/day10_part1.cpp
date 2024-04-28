#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>
using namespace std;

string filename = "day10.txt";
unordered_map<char, pair<pair<int, int>, pair<int, int>>> direction = {
    {'|', {{0, 1}, {0, -1}}},  // N, S
    {'-', {{1, 0}, {-1, 0}}},  // W, E
    {'L', {{1, 1}, {-1, -1}}}, // N, E
    {'J', {{-1, 1}, {1, -1}}}, // N, W
    {'7', {{1, 1}, {-1, -1}}}, // W, S
    {'F', {{-1, 1}, {1, -1}}}  // E, S
};

class Point {
  public:
    char pipe;
    pair<int, int> coordinates;
    char source;
    Point(char p, pair<int, int> xy) {
        pipe = p;
        coordinates = xy;
    }

    Point() {
        pipe = '.';
        coordinates = make_pair(0, 0);
    }
};

Point findStarting(vector<vector<Point>> map) {
    vector<vector<Point>>::iterator outerItr;
    vector<Point>::iterator innerItr;
    Point p = Point();
    for (outerItr = map.begin(); outerItr != map.end(); outerItr++) {
        for (innerItr = outerItr->begin(); innerItr != outerItr->end(); innerItr++) {
            if ((*innerItr).pipe == 'S') {
                cout << (*innerItr).coordinates.first << " " << (*innerItr).coordinates.second;
                return *innerItr;
            }
        }
    }
    return p;
}

Point nextPoint(Point currentPoint) {
    pair<int, int> coordinates;
    char pipe;
    if (currentPoint.pipe == '|' && currentPoint.source == 'S') {
    }
}

Point checkNorth(Point currentPoint, vector<vector<Point>> map) {
    Point p = map[currentPoint.coordinates.first][currentPoint.coordinates.second - 1];
    return p;
}

Point checkSouth(Point currentPoint, vector<vector<Point>> map) {
    Point p = map[currentPoint.coordinates.first][currentPoint.coordinates.second + 1];
    return p;
}

Point checkWest(Point currentPoint, vector<vector<Point>> map) {
    Point p = map[currentPoint.coordinates.first - 1][currentPoint.coordinates.second];
    return p;
}

Point checkEast(Point currentPoint, vector<vector<Point>> map) {
    Point p = map[currentPoint.coordinates.first + 1][currentPoint.coordinates.second];
    return p;
}

int main() {
    ifstream infile(filename);
    vector<vector<Point>> map;
    int x, y, steps;
    y = 0;
    steps = 0;
    while (!infile.eof()) {
        x = 0;
        string currentLine;
        getline(infile, currentLine);

        vector<Point> row; // Change to Point type instead of char
        pair<int, int> coordinates;

        for (char &pipe : currentLine) {
            row.emplace_back(pipe, make_pair(x, y));
            x++;
        }
        map.push_back(row); // Add the row to the map vector
        y++;
    }

    Point currentPoint = findStarting(map);
    if (checkNorth(currentPoint, map).pipe == '|')

        // check where nsew for the first valid point,
        // go to the next valid point and input the source point
        // after that follow the next point and continuously input the source point in the next point in the map

        // all done while the currentPOint isnt the start
        return 0;
}
