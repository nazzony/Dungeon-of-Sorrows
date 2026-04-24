#ifndef DUNGEON_OF_SORROWS_MAP_H
#define DUNGEON_OF_SORROWS_MAP_H

#include <vector>
#include <string>
#include <iostream>

class Map {
private:
    std::vector<std::string> roomGrid;

public:
    Map();

    void render();

    void spawnEntity(int x, int y, char icon);

    char getCharAt(int x, int y);

    bool isWalkable(int x, int y);

};


#endif //DUNGEON_OF_SORROWS_MAP_H