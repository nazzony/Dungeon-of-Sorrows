#ifndef DUNGEON_OF_SORROWS_GAME_H
#define DUNGEON_OF_SORROWS_GAME_H

#include "../Entities/Player.h"
#include <conio.h>
#include <iostream>
#include "../World/Map.h"

class Game {
private:
    bool isRunning;
    Map grid;
    Player player;

public:
    Game();

    void handleInput();

    void run();

    void render();

    void input();

};


#endif //DUNGEON_OF_SORROWS_GAME_H