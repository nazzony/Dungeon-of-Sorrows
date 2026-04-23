#ifndef DUNGEON_OF_SORROWS_GAME_H
#define DUNGEON_OF_SORROWS_GAME_H

#include <string>
#include <iostream>

class Game {
private:
    bool isRunning;

public:
    Game();

    void handleInput();

    void run();

    void render();

    void input();

};


#endif //DUNGEON_OF_SORROWS_GAME_H