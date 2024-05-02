#include <iostream>
#include <fstream>
#include <string>

int calculateStringDifference(const std::string& file_path) {
    int total_code_chars = 0;
    int total_memory_chars = 0;
    
    std::ifstream file(file_path);
    if (!file.is_open()) {
        std::cerr << "Error: Unable to open file\n";
        return 0;
    }
    
    std::string line;
    while (std::getline(file, line)) {
        size_t start = line.find_first_not_of(" \t");
        size_t end = line.find_last_not_of(" \t");
        if (start == std::string::npos || end == std::string::npos) {
            continue;
        }
        line = line.substr(start, end - start + 1);
        total_code_chars += line.size();
        
        // Remove the enclosing double quotes
        line = line.substr(1, line.size() - 2);
        for (size_t i = 0; i < line.size(); ++i) {
            if (line[i] == '\\') {
                if (line[i+1] == '\\') {
                    // Escaped backslash
                    ++i;
                } else if (line[i+1] == '"') {
                    // Escaped double quote
                    ++i;
                } else if (line[i+1] == 'x') {
                    // Hexadecimal escape sequence
                    i += 3;
                }
            }
            ++total_memory_chars;
        }
    }
    
    return total_code_chars - total_memory_chars;
}

int main() {
    std::string file_path = "input.txt";
    int difference = calculateStringDifference(file_path);
    std::cout << "Difference between code characters and memory characters: " << difference << std::endl;
}
