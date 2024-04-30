#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>

void findCombinations(const std::vector<int>& jars, int index, int target, int currentSum, int& count) {
    if (currentSum == target) {
        count++;
        return;
    }
    if (index >= jars.size() || currentSum > target) {
        return;
    }

    findCombinations(jars, index + 1, target, currentSum + jars[index], count);

    // Exclude the current container
    findCombinations(jars, index + 1, target, currentSum, count);
}

int main(int argc, char **argv) {
  std::string line;
  std::ifstream file("input.txt");
  std::vector<int> jars{};
  while (std::getline(file, line)) {
    jars.push_back(std::stoi(line));
  }

    int targetVolume = 150;
    int count = 0;
    findCombinations(jars, 0, targetVolume, 0, count);

    std::cout << "Number of different combinations: " << count << std::endl;
  return 0;
}