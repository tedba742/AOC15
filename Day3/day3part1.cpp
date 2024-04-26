#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <array>
#include <sstream>
#include <map>
#include <set>
#include <vector>

struct Coordinates{
    int x;
    int y;

    bool operator<(const Coordinates& other) const {
        if (x == other.x) {
            return y < other.y;
        }
        return x < other.x;
    }
};

Coordinates getNextPosition(char c, const Coordinates& currentPosition) {
    Coordinates nextPosition = currentPosition;
    if (c == '^') {
        nextPosition.y += 1;
    } else if (c == 'v') {
        nextPosition.y -= 1;
    } else if (c == '>') {
        nextPosition.x += 1;
    } else if (c == '<') {
        nextPosition.x -= 1;
    }
    return nextPosition;
}

int main() {
    // Open the file for reading
    std::ifstream file("input.txt");
    std::set<Coordinates> visitedLocations{};
    Coordinates currentPositionRobotSanta{0, 0};
    Coordinates currentPositionRealSanta{0, 0};

    if (!file.is_open()) {
    std::cerr << "Error: Unable to open file." << std::endl;
    return 1;
    }

    std::string line;
    while (std::getline(file, line)) {
        int counter{1};
        for (char c : line) {
            
            if(counter % 2 == 0){
                currentPositionRobotSanta = getNextPosition(c, currentPositionRobotSanta);
                visitedLocations.insert(currentPositionRobotSanta);
            } else {
                currentPositionRealSanta = getNextPosition(c, currentPositionRealSanta);
                visitedLocations.insert(currentPositionRealSanta);
            }
            counter++;
        }
    }

    std::cout << "Amount of houses that was visited by Santa: " << visitedLocations.size() << std::endl;
    // Close the file
    file.close();

    return 0;
}