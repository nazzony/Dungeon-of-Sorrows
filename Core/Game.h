#ifndef DUNGEON_OF_SORROWS_GAME_H
#define DUNGEON_OF_SORROWS_GAME_H

#include <windows.h>
#include "../Entities/Player.h"
#include <conio.h>
#include <vector>
#include <string>
#include "../World/Map.h"
#include "../Entities/Enemy.h"
#include "../Entities/Item.h"

class Game {
private:
    bool isRunning;

    Map grid;

    Player player;

    std::vector<Enemy> enemies;

    std::string actionMessage;

    int currentLevel;

    std::vector<Item> items;
    int currentGold = 0;

public:
    Game();

    void handleInput();

    void run();

    void render();

    void nextLevel();

};


#endif //DUNGEON_OF_SORROWS_GAME_H