#include "Map.h"

Map::Map() {
    roomGrid.push_back("####################");
    for (int i = 0; i < 8; ++i) roomGrid.push_back("#..................#");
    roomGrid.push_back("####################");
}

std::string Map::render() {
    for (auto line : roomGrid) {
        std::cout << line << std::endl;
    }
}
