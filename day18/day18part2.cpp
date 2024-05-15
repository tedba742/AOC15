#include <iostream>
#include <fstream>
#include <vector>

const int GRID_SIZE = 100;

int countNeighborsOn(const std::vector<std::vector<char>>& grid, int row, int col) {
    int count = 0;
    for (int dr = -1; dr <= 1; ++dr) {
        for (int dc = -1; dc <= 1; ++dc) {
            if (dr == 0 && dc == 0) continue;
            int r = row + dr;
            int c = col + dc;
            if (r >= 0 && r < GRID_SIZE && c >= 0 && c < GRID_SIZE && grid[r][c] == '#') {
                count++;
            }
        }
    }
    return count;
}

void simulateStep(std::vector<std::vector<char>>& grid) {
    std::vector<std::vector<char>> newGrid = grid;
    for (int row = 0; row < GRID_SIZE; ++row) {
        for (int col = 0; col < GRID_SIZE; ++col) {
            int neighborsOn = countNeighborsOn(grid, row, col);
            if (grid[row][col] == '#') {
                if (neighborsOn != 2 && neighborsOn != 3) {
                    newGrid[row][col] = '.';
                }
            } else {
                if (neighborsOn == 3) {
                    newGrid[row][col] = '#';
                }
            }
        }
    }
    newGrid[0][0] = newGrid[0][GRID_SIZE-1] = newGrid[GRID_SIZE-1][0] = newGrid[GRID_SIZE-1][GRID_SIZE-1] = '#';
    grid = newGrid;
}

int main() {
    std::ifstream file("input.txt");
    if (!file.is_open()) {
        std::cerr << "Failed to open input file." << std::endl;
        return 1;
    }

    std::vector<std::vector<char>> grid(GRID_SIZE, std::vector<char>(GRID_SIZE));

    for (int i = 0; i < GRID_SIZE; ++i) {
        for (int j = 0; j < GRID_SIZE; ++j) {
            file >> grid[i][j];
        }
    }

    grid[0][0] = grid[0][GRID_SIZE-1] = grid[GRID_SIZE-1][0] = grid[GRID_SIZE-1][GRID_SIZE-1] = '#';

    for (int i = 0; i < 100; ++i) {
        simulateStep(grid);
    }

    int lightsOn = 0;
    for (int i = 0; i < GRID_SIZE; ++i) {
        for (int j = 0; j < GRID_SIZE; ++j) {
            if (grid[i][j] == '#') {
                lightsOn++;
            }
        }
    }
    std::cout << "Number of lights on after 100 steps: " << lightsOn << std::endl;

}
