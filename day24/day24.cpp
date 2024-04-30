#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <limits>

void findCombinations(const std::vector<int>& weights, std::vector<int>& current, int target, std::vector<std::vector<int>>& combinations, int index) {
    if (target == 0) {
        combinations.push_back(current);
        return;
    }
    for (int i = index; i < weights.size(); ++i) {
        if (weights[i] <= target) {
            current.push_back(weights[i]);
            findCombinations(weights, current, target - weights[i], combinations, i + 1);
            current.pop_back();
        }
    }
}

std::vector<std::vector<int>> findAllCombinations(const std::vector<int>& weights, int target) {
    std::vector<std::vector<int>> combinations;
    std::vector<int> current;
    findCombinations(weights, current, target, combinations, 0);
    return combinations;
}

long long calculateQE(const std::vector<int>& group) {
    long long qe = 1;
    for (int weight : group) {
        qe *= weight;
    }
    return qe;
}

int main() {
    std::fstream file("input.txt");
    std::vector<int> weights;
    int weight;
    int totalWeight = 0;

    while (file >> weight) {
        weights.push_back(weight);
        totalWeight += weight;
    }

    int targetWeight = totalWeight / 3;
    auto combinations = findAllCombinations(weights, targetWeight);

    std::vector<int> idealGroup;
    int minFirstGroupSize ;
    for (const auto& combination : combinations) {
        if (combination.size() < minFirstGroupSize) {
            idealGroup = combination;
            minFirstGroupSize = combination.size();
        }
    }

    long long quantumEntanglement = calculateQE(idealGroup);

    std::cout << "Quantum Entanglement of the First Group: " << quantumEntanglement << std::endl;

    return 0;
}
