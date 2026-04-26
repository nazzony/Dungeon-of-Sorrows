#ifndef DUNGEON_OF_SORROWS_GAME_H
#define DUNGEON_OF_SORROWS_GAME_H

#include <windows.h>
#include "../Entities/Player.h"
#include <conio.h>
#include <iostream>
#include <string>
#include "../World/Map.h"
#include "../Entities/Enemy.h"

class Game {
private:
    bool isRunning;
    Map grid;
    Player player;
    Enemy enemy;
    std::string actionMessage;
    int currentLevel;

public:
    Game();

    void handleInput();

    void run();

    void render();

    void nextLevel();

};


#endif //DUNGEON_OF_SORROWS_GAME_H