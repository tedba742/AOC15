#include <iostream>
#include <vector>

int deliverPresents(int targetPresents) {
    int maxHouseNumber = targetPresents / 11;
    std::vector<int> presents(maxHouseNumber, 0);

    for (int elfNumber = 1; elfNumber < maxHouseNumber; ++elfNumber) {
        int housesVisited = 0;
        for (int houseNumber = elfNumber; houseNumber < maxHouseNumber && housesVisited < 50; houseNumber += elfNumber) {
            presents[houseNumber] += elfNumber * 11;
            housesVisited++;
        }
    }

    for (int houseNumber = 1; houseNumber < maxHouseNumber; ++houseNumber) {
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
}
