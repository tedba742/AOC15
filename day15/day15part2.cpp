#include <iostream>
#include <vector>
#include <algorithm>

struct Ingredient {
    std::string name;
    int capacity;
    int durability;
    int flavor;
    int texture;
    int calories;
};

int calculateScore(int tspSprinkles, int tspButterscotch, int tspChocolate, int tspCandy, const std::vector<Ingredient> &ingredients) {
    int totalCapacity = std::max(0, ingredients[0].capacity * tspSprinkles +
                                      ingredients[1].capacity * tspButterscotch +
                                      ingredients[2].capacity * tspChocolate +
                                      ingredients[3].capacity * tspCandy);

    int totalDurability = std::max(0, ingredients[0].durability * tspSprinkles +
                                         ingredients[1].durability * tspButterscotch +
                                         ingredients[2].durability * tspChocolate +
                                         ingredients[3].durability * tspCandy);

    int totalFlavor = std::max(0, ingredients[0].flavor * tspSprinkles +
                                    ingredients[1].flavor * tspButterscotch +
                                    ingredients[2].flavor * tspChocolate +
                                    ingredients[3].flavor * tspCandy);

    int totalTexture = std::max(0, ingredients[0].texture * tspSprinkles +
                                      ingredients[1].texture * tspButterscotch +
                                      ingredients[2].texture * tspChocolate +
                                      ingredients[3].texture * tspCandy);

    int totalCalories = ingredients[0].calories * tspSprinkles +
                        ingredients[1].calories * tspButterscotch +
                        ingredients[2].calories * tspChocolate +
                        ingredients[3].calories * tspCandy;

    if (totalCalories != 500) {
        return 0;
    }

    return totalCapacity * totalDurability * totalFlavor * totalTexture;
}

int main() {
    std::vector<Ingredient> ingredients = {
        {"Sprinkles", 2, 0, -2, 0, 3},
        {"Butterscotch", 0, 5, -3, 0, 3},
        {"Chocolate", 0, 0, 5, -1, 8},
        {"Candy", 0, -1, 0, 5, 8}
    };

    int maxScore = 0;

    for (int tspSprinkles = 0; tspSprinkles <= 100; ++tspSprinkles) {
        for (int tspButterscotch = 0; tspButterscotch <= 100 - tspSprinkles; ++tspButterscotch) {
            for (int tspChocolate = 0; tspChocolate <= 100 - tspSprinkles - tspButterscotch; ++tspChocolate) {
                int tspCandy = 100 - tspSprinkles - tspButterscotch - tspChocolate;

                int score = calculateScore(tspSprinkles, tspButterscotch, tspChocolate, tspCandy, ingredients);
                maxScore = std::max(maxScore, score);
            }
        }
    }

    std::cout << "Highest scoring cookie with exactly 500 calories has score: " << maxScore << std::endl;
}
