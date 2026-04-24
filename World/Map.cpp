#include "Map.h"

Map::Map() {
    roomGrid.push_back("####################");
    for (int i = 0; i < 8; ++i)
        roomGrid.push_back("#..................#");
    roomGrid.push_back("####################");
}

void Map::render() {
    for (auto line : roomGrid) {
        std::cout << line << std::endl;
    }
}

void Map::spawnEntity(int x, int y, char icon) { roomGrid[y][x] = icon; }

char Map::getCharAt(int x, int y) { return roomGrid[y][x]; }

bool Map::isWalkable(int x, int y) {
    if (x < 0 || x > roomGrid[0].size()
        || y < 0 || y > roomGrid.size()
        || roomGrid[y][x] == '#') {
        return false;
    }
    return true;
}
