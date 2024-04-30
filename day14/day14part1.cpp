#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

struct Raindeer {
    std::string name;
    int flightSpeed;
    int flightDuration;
    int restingPeriod;

    Raindeer(std::string name, int flightSpeed, int flightDuration, int restingPeriod)
        : name(name), flightSpeed(flightSpeed), flightDuration(flightDuration), restingPeriod(restingPeriod) {}
};

int getWinner(std::vector<Raindeer> raindeers){
  // Rudolph can fly 22 km/s for 8 seconds, but then must rest for 165 seconds.
        int maxValue;

    for(const auto& raindeer: raindeers){
        int distanceTraveled{0};
        int currentFlightTime{0};
        for(int i = 0; i < 2503; i++){
            distanceTraveled += raindeer.flightSpeed;
            currentFlightTime++;
            if(currentFlightTime == raindeer.flightDuration){
                i += raindeer.restingPeriod;
                currentFlightTime = 0;
            }
        }   

        if(distanceTraveled > maxValue){
                       maxValue = distanceTraveled;
    }

    }
    
    return maxValue;
}
int main() {
    std::string filename = "input.txt";  // Replace "input.txt" with the path to your file

    // Extract reindeer information from the file
    std::ifstream file(filename);
    std::string line;
    std::vector<Raindeer> raindeers;

    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string name, filler, flightSpeed, duration, rest;
        iss >> name >> filler >> filler   >> flightSpeed >>  filler >>filler >> duration >> filler >> filler >> filler >> filler >> filler >> filler >>  rest >> filler;
        std:: cout << name << " " << flightSpeed << " " << duration << " " << rest << " " << std::endl;
        raindeers.emplace_back(name, std::stoi(flightSpeed), std::stoi(duration), std::stoi(rest));
    }

    for (const auto& reindeer : raindeers) {
        std::cout << "Name: " << reindeer.name << ", Flight Speed: " << reindeer.flightSpeed
                  << ", Flight Duration: " << reindeer.flightDuration << ", Resting Period: " << reindeer.restingPeriod << std::endl;
    }
    std::cout << getWinner(raindeers) << std::endl;
    return 0;
}
