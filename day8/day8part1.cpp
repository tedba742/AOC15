#include <string>
#include <fstream>
#include <iostream>
#include <algorithm>>

int main(){
    int fullStringCode{0};
    int amountOfCharacters{0};
    int sum{0};

    std::ifstream file("input.txt");

    // Check if the file was successfully opened
    if (!file.is_open()) {
        std::cerr << "Error: Unable to open file." << std::endl;
        return 1; // Exit the program with an error code
    }

    // Read the file line by line
    std::string line;
    while (std::getline(file, line)) {
        for(char c: line){
            if(c==isDigit() || c == is){
                fullStringCode++;
            }
        }
    }
    file.close();

    std::cout << sum << std::endl;
    return 0;
}

