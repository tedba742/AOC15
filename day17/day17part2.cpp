#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

void findCombinations(const std::vector<int>& jars, int index, int target, int currentSum, int currentContainers, int& minContainers, int& count) {
    if (currentSum == target) {
        if (currentContainers < minContainers) {
            minContainers = currentContainers;
            count = 1;
        } else if (currentContainers == minContainers) {
            count++;
        }
        return;
    }
    if (index >= jars.size() || currentSum > target) {
        return;
    }

    findCombinations(jars, index + 1, target, currentSum + jars[index], currentContainers + 1, minContainers, count);
    findCombinations(jars, index + 1, target, currentSum, currentContainers, minContainers, count);
}

int main() {
    std::string line;
    std::ifstream file("input.txt");
    std::vector<int> jars;
    while (std::getline(file, line)) {
        jars.push_back(std::stoi(line));
    }

    int targetVolume = 150;
    int minContainers = INT_MAX;
    int count = 0;

    findCombinations(jars, 0, targetVolume, 0, 0, minContainers, count);

    std::cout << "Number of different ways to use minimum containers: " << count << std::endl;

    return 0;
}
