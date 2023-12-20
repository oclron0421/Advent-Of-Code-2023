#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>

using namespace std;

int main() {
    ifstream file("day3.txt");
    if (!file.is_open()) {
        cerr << "Error opening file" << endl;
        return 1;
    }

    string line;
    vector<string> input;

    while (getline(file, line)) {
        if (!line.empty()) {
            input.push_back(line);
        }
    }

    file.close();

    int rows = 140;
    int cols = 140;

    unordered_map<string, vector<int>> gearsDic;

    auto findGears = [&gearsDic](const string& str, int num, int i, int j) {
        j = (j == -1) ? 0 : j;
        for (size_t k = 0; k < str.length(); k++) {
            char ch = str[k];
            if (ch == '*') {
                string ind = to_string(i) + "-" + to_string(j + k);
                gearsDic[ind].emplace_back(num);
            }
        }
    };

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            char n = input[i][j];
            if (!isdigit(n)) continue;

            int num = n - '0';
            while (++j < cols) {
                if (isdigit(input[i][j])) {
                    num = num * 10 + (input[i][j] - '0');
                } else {
                    break;
                }
            }

            string top = (i == 0) ? "" : input[i - 1].substr(j - num, num);
            string btm = (i == rows - 1) ? "" : input[i + 1].substr(j - num, num);
            string lft = (j - num >= 0) ? input[i].substr(j - num, num) : "";
            string rgt = (j < cols) ? input[i].substr(j, num) : "";

            findGears(top, num, i - 1, j - num);
            findGears(btm, num, i + 1, j - num);
            findGears(lft, num, i, j - num);
            findGears(rgt, num, i, j);
        }
    }

    int v = 0;
    for (const auto& entry : gearsDic) {
        if (entry.second.max_size() == 2) {
            v += entry.second[0] * entry.second[1];
        }
    }

    cout << v << endl;

    return 0;
}
