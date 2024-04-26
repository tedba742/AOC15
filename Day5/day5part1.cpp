#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <array>
#include <sstream>
#include <algorithm>

struct NiceStrings {
    std::string text;
    bool hasThreeVowels;
    bool hasALetterThatAppearsTwiceInARow;
    bool isBadString;

    NiceStrings(std::string text, bool hasThreeVowels, bool hasALetterThatAppearsTwiceInARow, bool isBadString) : 
        text(text), hasThreeVowels(hasThreeVowels), hasALetterThatAppearsTwiceInARow(hasALetterThatAppearsTwiceInARow), isBadString(isBadString) {}
};

bool isVowel(char ch) {
    ch = std::tolower(ch);
    return ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u';
}

bool hasBadString(NiceStrings& s) {
    constexpr const char* badMatches[] = {"ab", "cd", "pq", "xy"};
    for(const auto& string : badMatches){
        if (s.text.find(string) != std::string::npos) {
            return true;
        }
    }
    return false;
}

bool hasTwoConsecutiveCharacters(NiceStrings s) {
    for(int i = 0; i < s.text.length() - 1; ++i){
        if(s.text[i] == s.text[i + 1]){
            return true;
        }
    }
    return false;
}

bool hasThreeVowels(NiceStrings& s) {
    int totalCount = 0;
    for(char c: s.text){
        if(isVowel(c)){
            totalCount++;
        }
    }
    return totalCount >= 3;
}

bool isItANiceString(NiceStrings& box) {
    bool isValid = true;
    isValid = hasThreeVowels(box) && hasTwoConsecutiveCharacters(box);
    if(hasBadString(box)) {
        return false;
    }
    return isValid;
}

int main() {
    // Open the file for reading
    std::ifstream file("input.txt");
    std::vector<NiceStrings> vec;

    // Check if the file was successfully opened
    if (!file.is_open()) {
        std::cerr << "Error: Unable to open file." << std::endl;
        return 1; // Exit the program with an error code
    }

    // Read the file line by line
    std::string line;
    while (std::getline(file, line)) {
        vec.push_back(NiceStrings(line, false, false, false));
    }
    file.close();

    int sum = 0;
    for (auto& box : vec) {
        if(isItANiceString(box)){
            sum++;
        }
    }
    std::cout << sum << std::endl;
    return 0;
}
