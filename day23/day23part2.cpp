#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

struct Instruction {
    std::string operation;
    char registerName;
    int offset;

    Instruction(const std::string& op, char reg, int off) : operation(op), registerName(reg), offset(off) {}
};

void hlf(int& reg) {
    reg /= 2;
}

void tpl(int& reg) {
    reg *= 3;
}

void inc(int& reg) {
    reg++;
}

int jmp(int currentInstruction, int offset) {
    return currentInstruction + offset;
}

int jie(int currentInstruction, int& reg, int offset) {
    if (reg % 2 == 0) {
        return currentInstruction + offset;
    }
    return currentInstruction + 1;
}

int jio(int currentInstruction, int& reg, int offset) {
    if (reg == 1) {
        return currentInstruction + offset;
    }
    return currentInstruction + 1;
}

int main() {
    std::fstream file("input.txt");
    std::vector<Instruction> program;

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string op, reg;
        char registerName;
        int offset;
        iss >> op >> reg;

        if (op == "jmp") {
            offset = std::stoi(reg);
            program.emplace_back(op, ' ', offset);
        } else {
            registerName = reg[0];
            iss >> offset;
            program.emplace_back(op, registerName, offset);
        }
    }

    int a = 1, b = 0;
    int currentInstruction = 0;
    while (currentInstruction >= 0 && currentInstruction < program.size()) {
        const Instruction& instr = program[currentInstruction];
        if (instr.operation == "hlf") {
            if (instr.registerName == 'a') {
                hlf(a);
            } else {
                hlf(b);
            }
        } else if (instr.operation == "tpl") {
            if (instr.registerName == 'a') {
                tpl(a);
            } else {
                tpl(b);
            }
        } else if (instr.operation == "inc") {
            if (instr.registerName == 'a') {
                inc(a);
            } else {
                inc(b);
            }
        } else if (instr.operation == "jmp") {
            currentInstruction = jmp(currentInstruction, instr.offset);
            continue;
        } else if (instr.operation == "jie") {
            currentInstruction = jie(currentInstruction, (instr.registerName == 'a' ? a : b), instr.offset);
            continue;
        } else if (instr.operation == "jio") {
            currentInstruction = jio(currentInstruction, (instr.registerName == 'a' ? a : b), instr.offset);
            continue;
        }
        currentInstruction++;
    }

    std::cout << "Value in register b: " << b << std::endl;

    return 0;
}
