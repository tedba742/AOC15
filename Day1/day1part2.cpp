#include <iostream>
#include <fstream>
#include <string>

int main() {
    // Open the file for reading
    std::ifstream file("input.txt");

    // Check if the file was successfully opened
    if (!file.is_open()) {
        std::cerr << "Error: Unable to open file." << std::endl;
        return 1; // Exit the program with an error code
    }

    // Read the file line by line
    std::string line;
    int floorLevel{0};
    int currentPosition{0};
    while (std::getline(file, line)) {
       for(char c : line){
        currentPosition++;
            if(c == '('){
                floorLevel++;
            } else {
                floorLevel--;
            }

            if(floorLevel == -1){
                std::cout << currentPosition << std::endl;
                break;
            }
       }
    }

    // Close the file
    file.close();

    std::cout << floorLevel << std::endl;
    return 0;
}
