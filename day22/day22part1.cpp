#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>
#include <unordered_map>
#include <limits>

struct State {
    int playerHp;
    int playerMana;
    int bossHp;
    int bossDamage;
    int shieldTimer;
    int poisonTimer;
    int rechargeTimer;
    int manaSpent;
    int playerArmor;

    bool operator>(const State& other) const {
        return manaSpent > other.manaSpent;
    }
};

struct Spell {
    std::string name;
    int cost;
    int damage;
    int healing;
    int armor;
    int duration;
    int manaGain;
};

const Spell spells[] = {
    {"Magic Missile", 53, 4, 0, 0, 0, 0},
    {"Drain", 73, 2, 2, 0, 0, 0},
    {"Shield", 113, 0, 0, 7, 6, 0},
    {"Poison", 173, 3, 0, 0, 6, 0},
    {"Recharge", 229, 0, 0, 0, 5, 101}
};

const int MAX_MANA = std::numeric_limits<int>::max();

bool isEffectActive(const State& state, const std::string& effect) {
    if (effect == "Shield") return state.shieldTimer > 0;
    if (effect == "Poison") return state.poisonTimer > 0;
    if (effect == "Recharge") return state.rechargeTimer > 0;
    return false;
}

void applyEffects(State& state) {
    if (state.shieldTimer > 0) {
        state.shieldTimer--;
        if (state.shieldTimer == 0) {
            state.playerArmor = 0;
        }
    }
    if (state.poisonTimer > 0) {
        state.bossHp -= 3;
        state.poisonTimer--;
    }
    if (state.rechargeTimer > 0) {
        state.playerMana += 101;
        state.rechargeTimer--;
    }
}


bool playerTurn(State& state, const Spell& spell) {
    state.playerMana -= spell.cost;
    state.manaSpent += spell.cost;

    if (state.playerMana < 0) return false;

    if (spell.name == "Magic Missile") {
        state.bossHp -= spell.damage;
    } else if (spell.name == "Drain") {
        state.bossHp -= spell.damage;
        state.playerHp += spell.healing;
    } else if (spell.name == "Shield") {
        state.shieldTimer = spell.duration;
        state.playerArmor = spell.armor;
    } else if (spell.name == "Poison") {
        state.poisonTimer = spell.duration;
    } else if (spell.name == "Recharge") {
        state.rechargeTimer = spell.duration;
    }

    return true;
}

bool bossTurn(State& state) {
    int damage = std::max(1, state.bossDamage - state.playerArmor);
    state.playerHp -= damage;
    return state.playerHp > 0;
}

int findMinimumManaToWin(State initialState) {
    std::priority_queue<State, std::vector<State>, std::greater<State>> pq;
    pq.push(initialState);

    int minMana = MAX_MANA;

    while (!pq.empty()) {
        State current = pq.top();
        pq.pop();

        applyEffects(current);
        if (current.bossHp <= 0) {
            minMana = std::min(minMana, current.manaSpent);
            continue;
        }

        for (const auto& spell : spells) {
            if (isEffectActive(current, spell.name)) continue;
            State nextState = current;
            if (playerTurn(nextState, spell)) {
                applyEffects(nextState);
                if (nextState.bossHp <= 0) {
                    minMana = std::min(minMana, nextState.manaSpent);
                    continue;
                }

                if (bossTurn(nextState)) {
                    pq.push(nextState);
                }
            }
        }
    }

    return minMana;
}


int main() {
    std::ifstream file("input.txt");
    if (!file.is_open()) {
        std::cerr << "Failed to open input file." << std::endl;
        return 1;
    }

    int bossHp, bossDamage;
    file >> bossHp >> bossDamage;

    State initialState = {50, 500, 71, 10, 0, 0, 0, 0, 0};
    int result = findMinimumManaToWin(initialState);
    std::cout << "Least amount of mana to win: " << result << std::endl;

    return 0;
}
