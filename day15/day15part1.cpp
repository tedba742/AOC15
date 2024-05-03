#include <iostream>
#include <vector>
#include <algorithm>

struct Ingredient {
    int capacity;
    int durability;
    int flavor;
    int texture;
};

int calculateCookieScore(const std::vector<Ingredient>& ingredients, const std::vector<int>& teaspoons) {
    int capacity = 0, durability = 0, flavor = 0, texture = 0;

    for (size_t i = 0; i < ingredients.size(); ++i) {
        capacity += ingredients[i].capacity * teaspoons[i];
        durability += ingredients[i].durability * teaspoons[i];
        flavor += ingredients[i].flavor * teaspoons[i];
        texture += ingredients[i].texture * teaspoons[i];
    }

    int total_score = std::max(0, capacity) * std::max(0, durability) * std::max(0, flavor) * std::max(0, texture);

    return total_score;
}

int findHighestCookieScore(const std::vector<Ingredient>& ingredients) {
    int highest_score = 0;

    std::vector<int> teaspoons(ingredients.size(), 0);
    for (int i = 0; i <= 100; ++i) {
        teaspoons[0] = i;
        for (int j = 0; j <= 100 - i; ++j) {
            teaspoons[1] = j;
            for (int k = 0; k <= 100 - i - j; ++k) {
                teaspoons[2] = k;
                teaspoons[3] = 100 - i - j - k;

                int score = calculateCookieScore(ingredients, teaspoons);
                highest_score = std::max(highest_score, score);
            }
        }
    }

    return highest_score;
}

int main() {
    std::vector<Ingredient> ingredients = {
        {-1, -2, 6, 3},
        {2, 3, -2, -1}
    };

    int highest_score = findHighestCookieScore(ingredients);
    std::cout << "Total score of the highest-scoring cookie: " << highest_score << std::endl;

    return 0;
}
