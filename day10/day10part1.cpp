#include <iostream>
#include <string>

std::string generateNextSequence(const std::string& current_sequence) {
    std::string next_sequence = "";
    char current_digit = current_sequence[0];
    int count = 1;
    
    for (size_t i = 1; i < current_sequence.size(); ++i) {
        if (current_sequence[i] == current_digit) {
            count++;
        } else {
            next_sequence += std::to_string(count) + current_digit;
            count = 1;
            current_digit = current_sequence[i];
        }
    }
    
    next_sequence += std::to_string(count) + current_digit;
    
    return next_sequence;
}

int main() {
    std::string sequence = "1321131112";
    for (int i = 0; i < 40; ++i) {
        sequence = generateNextSequence(sequence);
    }
    
    std::cout << "Length of the resulting sequence after 40 iterations: " << sequence.length() << std::endl;
    
    return 0;
}
