#include <iostream>
#include <vector>

int deliverPresents(int targetPresents) {
    std::vector<int> presents(targetPresents / 10, 0);

    for (int elfNumber = 1; elfNumber < targetPresents / 10; ++elfNumber) {
        for (int houseNumber = elfNumber; houseNumber < targetPresents / 10; houseNumber += elfNumber) {
            presents[houseNumber] += elfNumber * 10;
        }
    }

    for (int houseNumber = 0; houseNumber < targetPresents / 10; ++houseNumber) {
        if (presents[houseNumber] >= targetPresents) {
            return houseNumber;
        }
    }

    return -1;
}

int main() {
    int targetPresents = 34000000;

    int lowestHouseNumber = deliverPresents(targetPresents);
    std::cout << "Lowest house number to receive at least " << targetPresents << " presents: " << lowestHouseNumber << std::endl;

    return 0;
}
