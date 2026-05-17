#ifndef DUNGEON_OF_SORROWS_GAMEENGINE_H
#define DUNGEON_OF_SORROWS_GAMEENGINE_H

#include "Game.h"
#include "../utilities.h"
#include <iostream>
#include <conio.h>

enum GameState {
    MAIN_MENU,
    PLAYING,
    GAME_OVER,
    DEVELOPMENT,
    EXIT,
};

class GameEngine {
public:
    GameEngine();
    void run();

private:
    GameState currentState;

    int lastDepth;
    int lastGold;

    void stateMainMenu();
    void statePlaying();
    void stateDevelopment();
    void stateGameOver();
};


#endif //DUNGEON_OF_SORROWS_GAMEENGINE_H