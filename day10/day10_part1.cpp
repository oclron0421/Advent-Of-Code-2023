#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>
using namespace std;
#define LENGTH 5
#define DEPTH 5

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
    Point(char p, pair<int, int> c) {
        pipe = p;
        coordinates = c;
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
                return *innerItr;
            }
        }
    }
    return p;
}

void goUp(Point &currentPoint, vector<vector<Point>> map) {
    currentPoint = map[currentPoint.coordinates.second - 2][currentPoint.coordinates.first];
}

void goDown(Point &currentPoint, vector<vector<Point>> map) {
    currentPoint = map[currentPoint.coordinates.second + 2][currentPoint.coordinates.first];
}

void goLeft(Point &currentPoint, vector<vector<Point>> map) {
    currentPoint = map[currentPoint.coordinates.second][currentPoint.coordinates.first - 2];
}

void goRight(Point &currentPoint, vector<vector<Point>> map) {
    currentPoint = map[currentPoint.coordinates.second][currentPoint.coordinates.first + 2];
}

void goUpRight(Point &currentPoint, vector<vector<Point>> map) {
    currentPoint = map[currentPoint.coordinates.second - 1][currentPoint.coordinates.first + 1];
}

void goUpLeft(Point &currentPoint, vector<vector<Point>> map) {
    currentPoint = map[currentPoint.coordinates.second - 1][currentPoint.coordinates.first - 1];
}

void goDownRight(Point &currentPoint, vector<vector<Point>> map) {
    currentPoint = map[currentPoint.coordinates.second + 1][currentPoint.coordinates.first + 1];
}

void goDownLeft(Point &currentPoint, vector<vector<Point>> map) {
    currentPoint = map[currentPoint.coordinates.second + 1][currentPoint.coordinates.first - 1];
}

Point checkNorth(Point currentPoint, vector<vector<Point>> map) {
    if (currentPoint.coordinates.second - 1 >= 0) {
        Point p = map[currentPoint.coordinates.second - 1][currentPoint.coordinates.first];
        return p;
    } else {
        Point p = Point();
        return p;
    }
}

Point checkSouth(Point currentPoint, vector<vector<Point>> map) {
    if (currentPoint.coordinates.second + 1 < DEPTH) {
        Point p = map[currentPoint.coordinates.second + 1][currentPoint.coordinates.first];
        return p;
    } else {
        Point p = Point();
        return p;
    }
}

Point checkWest(Point currentPoint, vector<vector<Point>> map) {
    if (currentPoint.coordinates.first - 1 >= 0) {
        Point p = map[currentPoint.coordinates.second][currentPoint.coordinates.first - 1];
        return p;
    } else {
        Point p = Point();
        return p;
    }
}

Point checkEast(Point currentPoint, vector<vector<Point>> map) {
    if (currentPoint.coordinates.first + 1 < LENGTH) {
        Point p = map[currentPoint.coordinates.second][currentPoint.coordinates.first + 1];
        return p;
    } else {
        Point p = Point();
        return p;
    }
}

bool isSameAsPreviousPoint(Point currentPoint, Point previousPoint) {
    if (currentPoint.coordinates.first == previousPoint.coordinates.first && currentPoint.coordinates.second == previousPoint.coordinates.second) {
        return true;
    } else {
        return false;
    }
}

void go(Point &currentPoint, Point &previousPoint, Point &startPoint, vector<vector<Point>> map) {
    if (checkEast(currentPoint, map).pipe != '.' && checkEast(currentPoint, map).pipe != '|' && checkEast(currentPoint, map).pipe != 'L' && checkEast(currentPoint, map).pipe != 'F' && checkEast(currentPoint, map).pipe != '-' && !isSameAsPreviousPoint(checkEast(currentPoint, map), previousPoint)) {

        switch (checkEast(currentPoint, map).pipe) {
        case '-':
            // execute right
            previousPoint = checkEast(currentPoint, map);
            goRight(currentPoint, map);
            break;
        case 'J':
            // execute up right
            previousPoint = checkEast(currentPoint, map);
            goUpRight(currentPoint, map);
            break;
        case '7':
            // execute down right
            previousPoint = checkEast(currentPoint, map);
            goDownRight(currentPoint, map);
            break;
        case 'S':
            if (isSameAsPreviousPoint(checkEast(currentPoint, map), previousPoint)) {
                previousPoint = currentPoint;
            } else {
                currentPoint = startPoint;
                break;
            }
        }
    } else if (checkSouth(currentPoint, map).pipe != '.' && checkSouth(currentPoint, map).pipe != '7' && checkSouth(currentPoint, map).pipe != 'F' && checkSouth(currentPoint, map).pipe != '-' && !isSameAsPreviousPoint(checkSouth(currentPoint, map), previousPoint)) {

        switch (checkSouth(currentPoint, map).pipe) {
        case '|':
            // execute down
            previousPoint = checkSouth(currentPoint, map);
            goDown(currentPoint, map);
            break;
        case 'L':
            // execute down right
            previousPoint = checkSouth(currentPoint, map);
            goDownRight(currentPoint, map);
            break;
        case 'J':
            // execute down left
            previousPoint = checkSouth(currentPoint, map);
            goDownLeft(currentPoint, map);
            break;
        case 'S':
            if (isSameAsPreviousPoint(checkSouth(currentPoint, map), previousPoint)) {
                previousPoint = checkSouth(currentPoint, map);
                break;
            } else {
                currentPoint = startPoint;
                break;
            }
        }
    } else if (checkWest(currentPoint, map).pipe != '.' && checkWest(currentPoint, map).pipe != 'J' && checkWest(currentPoint, map).pipe != '7' && checkWest(currentPoint, map).pipe != '|' && !isSameAsPreviousPoint(checkWest(currentPoint, map), previousPoint)) {

        switch (checkWest(currentPoint, map).pipe) {
        case '-':
            // execute left
            previousPoint = checkWest(currentPoint, map);
            goLeft(currentPoint, map);
            break;
        case 'L':
            // execute up left
            previousPoint = checkWest(currentPoint, map);
            goUpLeft(currentPoint, map);
            break;
        case 'F':
            // execute down left
            previousPoint = checkWest(currentPoint, map);
            goDownLeft(currentPoint, map);
            break;
        case 'S':
            if (isSameAsPreviousPoint(checkWest(currentPoint, map), previousPoint)) {
                previousPoint = checkWest(currentPoint, map);
                break;
            } else {
                currentPoint = startPoint;
                break;
            }
        }

    } else if (checkNorth(currentPoint, map).pipe != '.' && checkNorth(currentPoint, map).pipe != 'L' && checkNorth(currentPoint, map).pipe != 'J' && checkNorth(currentPoint, map).pipe != '-' && !isSameAsPreviousPoint(checkNorth(currentPoint, map), previousPoint)) {

        switch (checkNorth(currentPoint, map).pipe) {
        case '|':
            // execute up
            previousPoint = checkNorth(currentPoint, map);
            goUp(currentPoint, map);
            break;
        case 'F':
            // execute up right
            previousPoint = checkNorth(currentPoint, map);
            goUpRight(currentPoint, map);
            break;
        case '7':
            // execute up left
            previousPoint = checkNorth(currentPoint, map);
            goUpLeft(currentPoint, map);
            break;
        case 'S':
            if (isSameAsPreviousPoint(checkNorth(currentPoint, map), previousPoint)) {
                previousPoint = checkNorth(currentPoint, map);
                break;
            } else {
                currentPoint = startPoint;
                break;
            }
        }
    } else {
        cout << "All directions are empty";
    }
}

int main() {
    ifstream infile(filename);
    vector<vector<Point>> map;
    Point previousPoint;
    int x, y, steps;
    int count = 0;
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

    Point startPoint = findStarting(map);

    Point currentPoint = startPoint;

    do {
        go(currentPoint, previousPoint, startPoint, map);
        count++;
        cout << currentPoint.pipe << ", " << currentPoint.coordinates.first << ", " << currentPoint.coordinates.second << endl;
    } while (currentPoint.pipe != 'S');

    cout << count;

    return 0;
}
