#include <iostream>
#include <fstream>
#include <string>

int calculateStringDifference(const std::string& file_path) {
    int total_code_chars = 0;
    int total_encoded_chars = 0;
    
    std::ifstream file(file_path);    
    std::string line;
    while (std::getline(file, line)) {
        size_t start = line.find_first_not_of(" \t");
        size_t end = line.find_last_not_of(" \t");
        if (start == std::string::npos || end == std::string::npos) {
            continue;
        }
        line = line.substr(start, end - start + 1);
        total_code_chars += line.size();

        std::string encoded = "\"";
        for (char c : line) {
            if (c == '\"') {
                encoded += "\\\"";
            } else if (c == '\\') {
                encoded += "\\\\";
            } else {
                encoded += c;
            }
        }
        encoded += "\"";
        total_encoded_chars += encoded.size();
    }
    
    return total_encoded_chars - total_code_chars;
}

int main() {
    std::string file_path = "input.txt";
    int difference = calculateStringDifference(file_path);
    std::cout << "The total number of characters to represent the newly encoded strings minus the number of characters of code in each original string literal: " 
              << difference << std::endl;
}
