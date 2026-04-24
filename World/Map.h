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

    std::string render();

};


#endif //DUNGEON_OF_SORROWS_MAP_H