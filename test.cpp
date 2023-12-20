#include <iostream>
#include <algorithm>
#include <vector>

int countDuplicates(const std::vector<char>& array) {
    std::vector<char> sortedArray = array;
    std::sort(sortedArray.begin(), sortedArray.end());

    int duplicateCount = 0;
    for (size_t i = 1; i < sortedArray.size(); ++i) {
        if (sortedArray[i] == sortedArray[i - 1]) {
            duplicateCount++;
        }
    }

    return duplicateCount;
}

int main() {
    std::vector<char> myArray = {'a', 'b', 'c', 'a', 'd', 'e', 'f', 'c', 'g', 'h', 'g'};
    int duplicates = countDuplicates(myArray);

    std::cout << "Number of duplicates: " << duplicates << std::endl;

    return 0;
}