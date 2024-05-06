#include <iostream>
#include <vector>
#include <algorithm>

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
    return std::max(damage, 1); // Minimum damage is 1
}

bool simulateBattle(const Player& player, const Boss& boss) {
    int playerHitPoints = player.hitPoints;
    int bossHitPoints = boss.hitPoints;

    while (true) {
        bossHitPoints -= calculateDamage(player.damage, boss.armor);
        if (bossHitPoints <= 0) return true; // Player wins

        playerHitPoints -= calculateDamage(boss.damage, player.armor);
        if (playerHitPoints <= 0) return false; // Boss wins
    }
}

int getTotalCost(const Item& weapon, const Item& armor, const std::vector<Item>& rings, size_t ringIndex1, size_t ringIndex2) {
    int totalCost = weapon.cost + armor.cost;
    if (ringIndex1 < rings.size()) totalCost += rings[ringIndex1].cost;
    if (ringIndex2 < rings.size()) totalCost += rings[ringIndex2].cost;
    return totalCost;
}

int getTotalDamage(const Item& weapon, const Item& armor, const std::vector<Item>& rings, size_t ringIndex1, size_t ringIndex2) {
    int totalDamage = weapon.damage + armor.damage;
    if (ringIndex1 < rings.size()) totalDamage += rings[ringIndex1].damage;
    if (ringIndex2 < rings.size()) totalDamage += rings[ringIndex2].damage;
    return totalDamage;
}

int getTotalArmor(const Item& armor, const std::vector<Item>& rings, size_t ringIndex1, size_t ringIndex2) {
    int totalArmor = armor.armor;
    if (ringIndex1 < rings.size()) totalArmor += rings[ringIndex1].armor;
    if (ringIndex2 < rings.size()) totalArmor += rings[ringIndex2].armor;
    return totalArmor;
}

int main() {
    Player player{100, 0, 0}; // Initial player stats
    Boss boss{100, 8, 2}; // Boss stats (puzzle input)

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
        {"Platemail", 102, 0, 5}
    };

    std::vector<Item> rings = {
        {"Damage +1", 25, 1, 0},
        {"Damage +2", 50, 2, 0},
        {"Damage +3", 100, 3, 0},
        {"Defense +1", 20, 0, 1},
        {"Defense +2", 40, 0, 2},
        {"Defense +3", 80, 0, 3}
    };

    int minGold = std::numeric_limits<int>::max();

    for (const auto& weapon : weapons) {
        for (const auto& arm : armor) {
            for (size_t i = 0; i <= rings.size(); ++i) {
                for (size_t j = 0; j <= rings.size(); ++j) {
                    if (i == j && i != 0) continue;

                    int totalCost = getTotalCost(weapon, arm, rings, i, j);
                    int totalDamage = getTotalDamage(weapon, arm, rings, i, j);
                    int totalArmor = getTotalArmor(arm, rings, i, j);

                    Player equippedPlayer{100, totalDamage, totalArmor};
                    if (simulateBattle(equippedPlayer, boss)) {
                        minGold = std::min(minGold, totalCost);
                    }
                }
            }
        }
    }

    std::cout << "Minimum amount of gold needed to win: " << minGold << std::endl;

    return 0;
}
