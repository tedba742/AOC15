#include <iostream>
#include <vector>
#include <array>
struct House {
    int houseNumber;
    int amountOfPresents;
    House(int houseNumber, int amountOfPresents) : houseNumber(houseNumber), amountOfPresents(amountOfPresents) {}
};

void deliverPresents(std::vector<House> houses, int i, long long target, int flag){
    House newHouse(i, 0);
    houses.push_back(newHouse);
    for(auto& house : houses){
        house.amountOfPresents += house.houseNumber * 10;
        if(house.amountOfPresents >= target){
            std::cout << house.houseNumber << std::endl;
            flag = 1;
        }
    }

}

int main() {
    long long target = 34000000;
    std::vector<House> houses;
    int i = 1;
    int flag = 0;
    while (true) {

        deliverPresents(houses, i, target, flag);     
        i++;
        if(flag == 1){
            break;
        }
    }
    return 0;
}