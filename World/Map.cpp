#include "Map.h"
#include <cstdlib>

Map::Map() {
    drunkardsWalk();

    for (int y = 0; y < roomGrid.size(); ++y) {
        std::vector<bool> row;
        for (int x = 0; x < roomGrid[y].size(); ++x) {
            row.push_back(false);
        }
        explored.push_back(row);
    }
}

void Map::render() {

    for (int y = 0; y < roomGrid.size(); ++y) {
        for (int x = 0; x < roomGrid[y].size(); ++x) {
            if (explored[y][x] == true) {
                std::cout << roomGrid[y][x] << " ";
            } else {
                std::cout << "  ";
            }
        }
        std::cout << std::endl;
    }

}

void Map::spawnEntity(int x, int y, char icon) { roomGrid[y][x] = icon; }

char Map::getCharAt(int x, int y) { return roomGrid[y][x]; }

bool Map::isWalkable(int x, int y) {
    if (x < 0 || x > roomGrid[0].size()
        || y < 0 || y >= roomGrid.size()
        || roomGrid[y][x] == '#') {
        return false;
    }
    return true;
}

void Map::revealArea(int x, int y) {

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            int targetY = y + 1 - i;
            int targetX = x + 1 - j;

            if (targetY >= 0 && targetY < explored.size() &&
                targetX >= 0 && targetX < explored[0].size()) {
                explored[targetY][targetX] = true;
                }
        }
    }

}

void Map::drunkardsWalk() {
    for (int i = 0; i < 20; ++i) {
        roomGrid.push_back(std::string(20,'#'));
    }
    int digX = 5;
    int digY = 5;

    for (int i = 0; i < 100; ++i) {
        roomGrid[digY][digX] = char(249);

        switch (rand() % 4) {
            default: break;

            case 0: digY--; break;
            case 1: digY++; break;
            case 2: digX--; break;
            case 3: digX++; break;
        }

        if (digY <= 0) digY = 1;
        if (digY >= 19) digY = 18;
        if (digX <= 0) digX = 1;
        if (digX >= 19) digX = 18;
    }
}