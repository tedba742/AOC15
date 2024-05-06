#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>

struct Item {
    std::string name;
    int cost;
    int damage;
    int armor;
};

struct Player {
    int hitPoints;
    int damage;
    int armor;
};

struct Boss {
    int hitPoints;
    int damage;
    int armor;
};

int calculateDamage(int attackerDamage, int defenderArmor) {
    int damage = attackerDamage - defenderArmor;
    return std::max(damage, 1);
}

bool simulateBattle(const Player& player, const Boss& boss) {
    int playerHitPoints = player.hitPoints;
    int bossHitPoints = boss.hitPoints;

    while (true) {
        bossHitPoints -= calculateDamage(player.damage, boss.armor);
        if (bossHitPoints <= 0) return true;

        playerHitPoints -= calculateDamage(boss.damage, player.armor);
        if (playerHitPoints <= 0) return false;
    }
}

int getTotalCost(const std::vector<Item>& items) {
    int totalCost = 0;
    for (const auto& item : items) {
        totalCost += item.cost;
    }
    return totalCost;
}

int getTotalDamage(const std::vector<Item>& items) {
    int totalDamage = 0;
    for (const auto& item : items) {
        totalDamage += item.damage;
    }
    return totalDamage;
}

int getTotalArmor(const std::vector<Item>& items) {
    int totalArmor = 0;
    for (const auto& item : items) {
        totalArmor += item.armor;
    }
    return totalArmor;
}

int main() {
    Player player{100, 0, 0};
    Boss boss{100, 8, 2};

    std::vector<Item> weapons = {
        {"Dagger", 8, 4, 0},
        {"Shortsword", 10, 5, 0},
        {"Warhammer", 25, 6, 0},
        {"Longsword", 40, 7, 0},
        {"Greataxe", 74, 8, 0}
    };

    std::vector<Item> armor = {
        {"Leather", 13, 0, 1},
        {"Chainmail", 31, 0, 2},
        {"Splintmail", 53, 0, 3},
        {"Bandedmail", 75, 0, 4},
        {"Platemail", 102, 0, 5},
        {"Nothing", 0, 0, 0}
    };

    std::vector<Item> rings = {
        {"Damage +1", 25, 1, 0},
        {"Damage +2", 50, 2, 0},
        {"Damage +3", 100, 3, 0},
        {"Defense +1", 20, 0, 1},
        {"Defense +2", 40, 0, 2},
        {"Defense +3", 80, 0, 3},
        {"Nothing", 0, 0, 0}
    };

    int maxGold = std::numeric_limits<int>::min();

    for (const auto& weapon : weapons) {
        for (const auto& arm : armor) {
            for (size_t i = 0; i <= rings.size(); ++i) {
                for (size_t j = 0; j <= rings.size(); ++j) {
                    if (i == j && i != 0) continue;

                    std::vector<Item> items = { weapon, arm };
                    if (i != 0) items.push_back(rings[i - 1]);
                    if (j != 0) items.push_back(rings[j - 1]);

                    int totalCost = getTotalCost(items);

                    Player equippedPlayer{100, getTotalDamage(items), getTotalArmor(items)};
                    if (!simulateBattle(equippedPlayer, boss)) {
                        maxGold = std::max(maxGold, totalCost);
                    }
                }
            }
        }
    }

    std::cout << "Most amount of gold spent and still lose: " << maxGold << std::endl;

    return 0;
}
