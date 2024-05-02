#include <iostream>
#include <string>

bool isValidPassword(const std::string& password) {
    bool straight = false;
    bool has_pairs = false;
    int pairs_count = 0;
    
    for (size_t i = 0; i < password.size() - 2; ++i) {
        if (password[i] == password[i + 1] - 1 && password[i] == password[i + 2] - 2) {
            straight = true;
            break;
        }
    }
    
    for (size_t i = 0; i < password.size() - 1; ++i) {
        if (password[i] == password[i + 1]) {
            pairs_count++;
            i++;
        }
    }
    has_pairs = (pairs_count >= 2);
    
    bool has_forbidden_chars = (password.find_first_of("iol") != std::string::npos);
    
    return straight && has_pairs && !has_forbidden_chars;
}

std::string incrementPassword(std::string password) {
    for (int i = password.size() - 1; i >= 0; --i) {
        if (password[i] == 'z') {
            password[i] = 'a';
        } else {
            password[i]++;
            break;
        }
    }
    return password;
}

std::string findNextPassword(std::string current_password) {
    do {
        current_password = incrementPassword(current_password);
    } while (!isValidPassword(current_password));
    
    return current_password;
}

int main() {
    std::string current_password = "cqjxjnds";
    std::string next_password = findNextPassword(current_password);
    std::cout << "Santa's next password should be: " << next_password << std::endl;  
}
