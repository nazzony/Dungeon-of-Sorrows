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

    std::vector<std::string> logs;
    int steps = 1;

    //solid shade char 219
    //empty shade char 176
    std::string hpBar = std::string(10, char(176));
    std::string mpBar = std::string(10, char(176));
    std::string xpBar = std::string(10, char(176));

    std::string enemyHpBar = std::string(10, char(176));

    std::string resPhys = std::string(10, char(176));
    std::string resFire = std::string(10, char(176));
    std::string resPois = std::string(10, char(176));

public:
    Game();

    void handleInput();

    void run();

    void render();

    void nextLevel();

    int getCurrentLevel();
    int getCurrentGold();
    bool isPlayerDead();

    // quick access
    void drawQuickAccess();
    // controls
    void drawControls();
    // legend
    void drawLegend();
    // log
    void drawLog();
    void addLog(std::string s);
    // player stats
    void drawPlayerStats();
    // enemy stats
    void drawEnemyStats();
    // equipment
    void drawEquipment();
    // backpack
    void drawBackpack();
    // attributes
    void drawAttributes();
};


#endif //DUNGEON_OF_SORROWS_GAME_H