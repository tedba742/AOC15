#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <vector>
#include <algorithm>

// Structure to store happiness relationships
struct Happiness {
    std::unordered_map<std::string, int> values;

    // Add happiness value for a given person pair
    void add(const std::string& source, const std::string& target, int value) {
        values[source + target] = value;
    }

    // Get happiness value for a given pair of people
    int get(const std::string& source, const std::string& target) const {
        auto it = values.find(source + target);
        if (it != values.end()) {
            return it->second;
        }
        return 0; // Default value if not found
    }
};

// Function to parse input and fill the happiness structure
void parseInput(const std::string& filename, Happiness& happiness) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Unable to open file." << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string source, verb, target, realVerb;
        int value;
        iss >> source >> verb >> realVerb >> value >> verb >> verb >> verb >> verb >> verb >> verb >> target;
        std::cout << source << " " << realVerb << " " << value << " " << target;
        if (realVerb == "gain") {
            happiness.add(source, target.substr(0, target.size() - 1), value);
        } else if (realVerb == "lose") {
            happiness.add(source, target.substr(0, target.size() - 1), -value);
        }
    }
    file.close();
}

// Function to calculate total happiness for a seating arrangement
int calculateTotalHappiness(const std::vector<std::string>& arrangement, const Happiness& happiness) {
    int totalHappiness = 0;
    for (size_t i = 0; i < arrangement.size(); ++i) {
        const std::string& person = arrangement[i];
        const std::string& leftNeighbor = arrangement[(i == 0) ? (arrangement.size() - 1) : (i - 1)];
        const std::string& rightNeighbor = arrangement[(i == arrangement.size() - 1) ? 0 : (i + 1)];
        totalHappiness += happiness.get(person, leftNeighbor);
        totalHappiness += happiness.get(person, rightNeighbor);
    }
    return totalHappiness;
}

// Function to find the maximum total happiness among all possible seating arrangements
int findMaxTotalHappiness(const std::vector<std::string>& people, Happiness& happiness) {
    int maxTotalHappiness = 0;
    std::vector<std::string> arrangement(people.size());
    std::copy(people.begin(), people.end(), arrangement.begin());
    do {
        int totalHappiness = calculateTotalHappiness(arrangement, happiness);
        maxTotalHappiness = std::max(maxTotalHappiness, totalHappiness);
    } while (std::next_permutation(arrangement.begin(), arrangement.end()));
    return maxTotalHappiness;
}

int main() {
    std::string filename = "input.txt";  // Replace "input.txt" with the path to your file
    Happiness happiness;
    parseInput(filename, happiness);

    // Extract unique people from the happiness relationships
    std::unordered_map<std::string, bool> uniquePeople;
    std::ifstream file(filename);
    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string source, verb, target, realVerb;
        iss >> source >> verb >> realVerb >> realVerb >> verb >> verb >> verb >> verb >> verb >> verb >> target;
        uniquePeople[source] = true;
        uniquePeople[target.substr(0, target.size() - 1)] = true;
    }
    file.close();

    // Store unique people in a vector
    std::vector<std::string> people;
    for (const auto& entry : uniquePeople) {
        people.push_back(entry.first);
    }

    // Find the maximum total happiness among all possible seating arrangements
    int maxTotalHappiness = findMaxTotalHappiness(people, happiness);
    std::cout << "Maximum total happiness: " << maxTotalHappiness << std::endl;

    return 0;
}
