#include <fstream>
#include <iostream>
#include <queue>
#include <string>
#include <utility>
#include <vector>

struct Point {
    std::pair<int, int> coordinates;
    char pipe;
};

int main() {
    std::vector<std::vector<Point>> points;
    std::ifstream inputFile("day10.txt");
    std::queue<Point> queuePoints;
    std::vector<Point> visitedPoints;
    // parsing in the txt file
    Point startingPoint;
    if (inputFile.is_open()) {
        std::string line;
        int y = 0;
        while (std::getline(inputFile, line)) {
            std::vector<Point> pointsInLine;
            for (int x = 0; x < line.size(); x++) {
                Point point;
                point.coordinates = std::make_pair(x, y);
                // if (line[x] == '.') {
                //     point.pipe = '\0';
                // } else {
                //     point.pipe = line[x];
                // }
                point.pipe = line[x];
                pointsInLine.push_back(point);
                if (point.pipe == 'S') {
                    startingPoint = point;
                }
            }
            points.push_back(pointsInLine);
            y++;
        }
        inputFile.close();

    } else {
        std::cout << "Failed to open the input file." << std::endl;
    }

    // finding the starting point
    Point currentPoint = startingPoint;

    for (int i = 0; i < points.size(); i++) {
        for (int j = 0; j < points[i].size(); j++) {
            std::cout << points[i][j].pipe;
        }
        std::cout << std::endl;
    }
    // BFS

    return 0;
}