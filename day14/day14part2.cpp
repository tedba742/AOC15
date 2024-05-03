#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>

struct Raindeer {
    std::string name;
    int flightSpeed;
    int flightDuration;
    int restingPeriod;

    Raindeer(std::string name, int flightSpeed, int flightDuration, int restingPeriod)
        : name(name), flightSpeed(flightSpeed), flightDuration(flightDuration), restingPeriod(restingPeriod) {}
};

std::map<std::string, int> getWinner(std::vector<Raindeer>& raindeers) {
    std::map<std::string, int> points;
    std::map<std::string, int> distances;

    for (const auto& raindeer : raindeers) {
        points[raindeer.name] = 0;
        distances[raindeer.name] = 0;
    }

    for (int second = 1; second <= 2503; ++second) {
        for (auto& raindeer : raindeers) {
            if (second % (raindeer.flightDuration + raindeer.restingPeriod) <= raindeer.flightDuration && second % (raindeer.flightDuration + raindeer.restingPeriod) > 0) {
                distances[raindeer.name] += raindeer.flightSpeed;
            }
        }
        int maxDistance = 0;
        for (const auto& distance : distances) {
            if (distance.second > maxDistance) {
                maxDistance = distance.second;
            }
        }
        for (auto& point : points) {
            if (distances[point.first] == maxDistance) {
                ++point.second;
            }
        }
    }

    return points;
}

int main() {
    std::string filename = "input.txt";

    std::ifstream file(filename);
    std::string line;
    std::vector<Raindeer> raindeers;

    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string name, filler, flightSpeed, duration, rest;
        iss >> name >> filler >> filler   >> flightSpeed >>  filler >>filler >> duration >> filler >> filler >> filler >> filler >> filler >> filler >>  rest >> filler;
        raindeers.emplace_back(name, std::stoi(flightSpeed), std::stoi(duration), std::stoi(rest));
    }

    auto points = getWinner(raindeers);
    
    int maxPoints = 0;
    for (const auto& point : points) {
        if (point.second > maxPoints) {
            maxPoints = point.second;
        }
    }

    std::cout << "Winning reindeer points: " << maxPoints << std::endl;

    return 0;
}
