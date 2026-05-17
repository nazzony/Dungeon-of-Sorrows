#include "Game.h"
#include <chrono>
#include <thread>
#include <cstdlib>
#include <cmath>
#include <execution>

#include "../utilities.h"


Game::Game() : isRunning{true}, player(1 , 1), currentLevel{1} {
    actionMessage = "You Enter The Dark Dungeon...";

    // Player Spawner
    player.setX(grid.getStartX());
    player.setY(grid.getStartY());
    player.setPrev(char(249));
    grid.spawnEntity(player.getX(), player.getY(), player.getIcon());
    grid.revealArea(player.getX(), player.getY());

    int randX, randY;

    bool foundSafeSpot = false;
    while (!foundSafeSpot) {
        randX = rand() % 38 + 1;
        randY = rand() % 18 + 1;

        if (grid.getCharAt(randX, randY) == char(249)) {
            foundSafeSpot = true;
        }
    }

    //Enemy spawner
    int maxEnemies = 3;

    for (int i = 0; i < maxEnemies; ++i) {

        foundSafeSpot = false;

        while (!foundSafeSpot) {
            randX = rand() % 38 + 1;
            randY = rand() % 18 + 1;

            if (grid.getCharAt(randX, randY) == char(249) &&
            !(randX == player.getX() && randY == player.getY())) {
                foundSafeSpot = true;
            }
        }

        Enemy enemy(randX, randY);
        enemy.setPrev(char(249));
        grid.spawnEntity(enemy.getX(), enemy.getY(), enemy.getIcon());
        enemies.push_back(enemy);
    }

    // Item Spawner
    int maxItems = 4;

    for (int i = 0; i < maxItems; ++i) {

        foundSafeSpot = false;

        while (!foundSafeSpot) {
            randX = rand() % 38 + 1;
            randY = rand() % 18 + 1;

            if (grid.getCharAt(randX, randY) == char(249) &&
            !(randX == player.getX() && randY == player.getY())) {
                foundSafeSpot = true;
            }
        }

        Item item(randX, randY);
        item.setPrev(char(249));
        grid.spawnEntity(item.getX(), item.getY(), item.getIcon());
        items.push_back(item);
    }

    // Exit spawner
    foundSafeSpot = false;
    while (!foundSafeSpot) {
        randX = rand() % 38 + 1;
        randY = rand() % 18 + 1;

        if (grid.getCharAt(randX, randY) == char(249)) {
            foundSafeSpot = true;
        }
    }
    grid.spawnEntity(randX, randY, '>');
}

void Game::handleInput() {
    char input;
    bool attacked = false;
    bool pickedUpItem = false;

    if (_kbhit()) {

        input = char(_getch());

        int targetX = player.getX();
        int targetY = player.getY();
        bool needToMove = false;

        switch (input) {
            case 'w': targetY--; needToMove = true; break;
            case 's': targetY++; needToMove = true; break;
            case 'a': targetX--; needToMove = true; break;
            case 'd': targetX++; needToMove = true; break;
            case ' ':
                if (player.getPrev() == '>') {
                    nextLevel();
                }
                break;
            default: break;
        }

        if (needToMove) {

            for (Enemy& enemy : enemies) {
                if (targetX == enemy.getX() && targetY == enemy.getY() && enemy.getHP() > 0) {

                    enemy.takeDamage(1);
                    attacked = true;
                    actionMessage = "You Hit an Enemy! | Remaining HP: " + std::to_string(enemy.getHP());
                    addLog(actionMessage);


                    grid.spawnEntity(player.getX(), player.getY(), player.getPrev());
                    grid.spawnEntity(enemy.getX(), enemy.getY(), player.getIcon());

                    render();
                    std::this_thread::sleep_for(std::chrono::milliseconds(100));

                    grid.spawnEntity(player.getX(), player.getY(), player.getIcon());

                    grid.spawnEntity(targetX, targetY, '*');
                    render();
                    std::this_thread::sleep_for(std::chrono::milliseconds(50));

                    if (enemy.getHP() > 0) {
                        grid.spawnEntity(targetX, targetY, 'E');
                    }
                    if (enemy.getHP() <= 0) {
                        grid.spawnEntity(targetX, targetY, char(249));
                        actionMessage = "Congrats! You defeated an enemy";
                        addLog(actionMessage);

                    }
                    break;
                }
            }



            for (int i = 0; i < items.size(); ++i) {
                if (targetX == items[i].getX() && targetY == items[i].getY()) {

                    if (items[i].getLootType() == 0) {
                        player.setHP(player.getHP() + 3);
                        actionMessage = "You found a glowing Potion! +3 HP";
                        addLog(actionMessage);

                    } else if (items[i].getLootType() == 1) {
                        int foundGold = rand() % 20 + 30;
                        currentGold += foundGold;
                        actionMessage = "You found a stash of coins! +" + std::to_string(foundGold) + " Gold";
                        addLog(actionMessage);

                    }

                    grid.spawnEntity(targetX, targetY, char(249));
                    items.erase(items.begin() + i);

                    pickedUpItem = true;
                    break;
                }
            }

            if (!attacked && grid.isWalkable(targetX, targetY)) {

                grid.spawnEntity(player.getX(), player.getY(), player.getPrev());

                player.setX(targetX);
                player.setY(targetY);

                player.setPrev(grid.getCharAt(player.getX(), player.getY()));

                grid.spawnEntity(player.getX(), player.getY(), player.getIcon());
                grid.revealArea(player.getX(), player.getY());

            }

        }

        if (input == 'q' || input == 'Q') isRunning = false;

        if (!attacked && !pickedUpItem) {
            if (player.getPrev() == '>') {
                actionMessage = "Press Space to Descend";
                addLog(actionMessage);

            }
            else {
                bool enemyNear = false;
                int enemyHp = 0;

                for (Enemy& enemy : enemies) {
                    int distX = std::abs(player.getX() - enemy.getX());
                    int distY = std::abs(player.getY() - enemy.getY());

                    if (distX <= 1 && distY <= 1 && enemy.getHP() > 0) {
                        enemyNear = true;
                        enemyHp = enemy.getHP();
                        break;
                    }
                }

                if (enemyNear) {
                    actionMessage = "A hostile enemy is near. HP: " + std::to_string(enemyHp);
                    addLog(actionMessage);

                } else {
                    actionMessage = "You carefully tread through the shadows...";
                    addLog(actionMessage);
                }

            }
        }
    }
    if (player.getHP() <= 0) { isRunning = false; }
}

void Game::run() {
    system("cls");
    render();
    while (isRunning) {
        handleInput();
        render();
        std::this_thread::sleep_for(std::chrono::milliseconds(16));
    }
}

void Game::render() {
    gotoXY(0, 0);

    // dungeon map
    drawWindow(0, 0, 84, 34, "DUNGEON", 4);
    // quick access
    drawQuickAccess();
    //controls
    drawControls();
    // legend
    drawLegend();
    // action log
    drawLog();
    // player stats
    drawPlayerStats();
    // enemy
    drawEnemyStats();
    // equipment
    drawEquipment();
    // backpack
    drawBackpack();
    // attributes
    drawAttributes();

    // setConsoleColor(7); // Normal text
    // gotoXY(85 + 2, 3); std::cout << "Depth: " << currentLevel;
    // gotoXY(85 + 2, 4); std::cout << "HP:    " << player.getHP() << "   ";
    // gotoXY(85 + 2, 5); std::cout << "Gold:  " << currentGold << "   ";


    grid.render(2, 1);

    // std::string paddedMessage = actionMessage;
    // while (paddedMessage.length() < 45 - 4) {
    //     paddedMessage += " ";
    // }

    // setConsoleColor(7);
    // gotoXY(85 + 2, 11);
    // std::cout << paddedMessage;

    gotoXY(0, 22);
}

void Game::nextLevel() {
    ++currentLevel;

    grid = Map();

    actionMessage = "You descend deeper into the dungeon...";
    addLog(actionMessage);

    // Player spawner
    player.setX(grid.getStartX());
    player.setY(grid.getStartY());
    player.setPrev(char(249));
    grid.spawnEntity(player.getX(), player.getY(), player.getIcon());
    grid.revealArea(player.getX(), player.getY());

    int randX, randY;

    bool foundSafeSpot = false;
    while (!foundSafeSpot) {
        randX = rand() % 38 + 1;
        randY = rand() % 18 + 1;

        if (grid.getCharAt(randX, randY) == char(249)) {
            foundSafeSpot = true;
        }
    }

    //Enemy spawner
    enemies.clear();
    int maxEnemies = 3;

    for (int i = 0; i < maxEnemies; ++i) {

        foundSafeSpot = false;

        while (!foundSafeSpot) {
            randX = rand() % 38 + 1;
            randY = rand() % 18 + 1;

            if (grid.getCharAt(randX, randY) == char(249) &&
            !(randX == player.getX() && randY == player.getY())) {
                foundSafeSpot = true;
            }
        }

        Enemy enemy(randX, randY);
        enemy.setPrev(char(249));
        grid.spawnEntity(enemy.getX(), enemy.getY(), enemy.getIcon());
        enemies.push_back(enemy);
    }

    // Item Spawner
    items.clear();
    int maxItems = 4;

    for (int i = 0; i < maxItems; ++i) {

        foundSafeSpot = false;

        while (!foundSafeSpot) {
            randX = rand() % 38 + 1;
            randY = rand() % 18 + 1;

            if (grid.getCharAt(randX, randY) == char(249) &&
            !(randX == player.getX() && randY == player.getY())) {
                foundSafeSpot = true;
            }
        }

        Item item(randX, randY);
        item.setPrev(char(249));
        grid.spawnEntity(item.getX(), item.getY(), item.getIcon());
        items.push_back(item);
    }

    // Exit spawner
    foundSafeSpot = false;
    while (!foundSafeSpot) {
        randX = rand() % 38 + 1;
        randY = rand() % 18 + 1;

        if (grid.getCharAt(randX, randY) == char(249)) {
            foundSafeSpot = true;
        }
    }
    grid.spawnEntity(randX, randY, '>');
}

int Game::getCurrentGold() { return currentGold; }
int Game::getCurrentLevel() { return currentLevel; }
bool Game::isPlayerDead() { return player.getHP() <= 0; }


void Game::drawQuickAccess() {
    drawWindow(0, 34, 45, 8, "QUICK ACCESS", 15);

    gotoXY(3, 35);
    std::cout << "[1] Health Potion" << std::flush;

    gotoXY(3, 36);
    std::cout << "[2] Mana Potion" << std::flush;

    gotoXY(3, 37);
    std::cout << "[3] Skill 1" << std::flush;

    gotoXY(3, 38);
    std::cout << "[4] Skill 2" << std::flush;

    gotoXY(3, 39);
    std::cout << "[5] Something" << std::flush;

    gotoXY(3, 40);
    std::cout << "[6] Something" << std::flush;

    for (int i = 0; i < 6; ++i) {
        gotoXY(33, 35 + i);
        std::cout << "(x0)" << std::flush;
    }
}


void Game::drawControls() {
    drawWindow(45, 34, 45, 4, "CONTROLS", 8);

    gotoXY(48, 35);
    std::cout << "[W/A/S/D] Move" << std::flush;

    gotoXY(48, 36);
    std::cout << "[Q] Quit" << std::flush;

    gotoXY(71, 35);
    std::cout << "[SPACE] Descend" << std::flush;
}


void Game::drawLegend() {
    drawWindow(45, 38, 45, 4, "LEGEND", 8);

    gotoXY(48, 39);
    std::cout << "@ : Player" << std::flush;

    gotoXY(48, 40);
    std::cout << "# : Wall" << std::flush;

    gotoXY(64, 39);
    std::cout << "E : Enemy" << std::flush;

    gotoXY(64, 40);
    std::cout << char(249) << " : Floor" << std::flush;

    gotoXY(78, 39);
    std::cout << "* : Loot" << std::flush;

    gotoXY(78, 40);
    std::cout << "> : Exit" << std::flush;
}

void Game::drawLog() {
    drawWindow(0, 42, 90, 8, "ACTION LOG", 14);
    for (int i = 0; i < logs.size(); ++i) {
        gotoXY(1, 43 + i);
        std::cout << logs.at(i);
    }
}

void Game::addLog(std::string s) {
    std::string message = "[Turn " + std::to_string(steps) + "] " + s;
    message.append(85 - message.length(), ' ');
    logs.push_back(message);
    if (logs.size() > 6) {
        logs.erase(logs.begin());
    }
    ++steps;
}

void Game::drawPlayerStats() {
    drawWindow(84, 0, 36, 17, "PLAYER STATS", 11);

    gotoXY(87, 2);
    std::cout << "Name: nazzony" << std::flush;

    gotoXY(87, 4);
    std::cout << "Class: Warrior" << std::flush;

    gotoXY(87, 6);
    std::cout << "Level: 1" << std::flush;

    gotoXY(102, 6);
    std::cout << "Depth: " << currentLevel << std::flush;

    gotoXY(87, 8);
    std::cout << "HP: [" << hpBar << "]  0/10" << std::flush;

    gotoXY(87, 10);
    std::cout << "MP: [" << mpBar << "]  0/10" << std::flush;

    gotoXY(87, 12);
    std::cout << "XP: [" << xpBar << "]  0/100" << std::flush;

    gotoXY(87, 14);
    std::cout << "Gold: " << currentGold << std::flush;
}

void Game::drawEnemyStats() {
    drawWindow(84, 17, 36, 17, "ENEMY", 12);

    gotoXY(87, 18);
    std::cout << "TARGET: Venherskyi" << std::flush;

    gotoXY(87, 20);
    std::cout << "   / \\__     " << std::flush;
    gotoXY(87, 21);
    std::cout << "  (    @\\___ " << std::flush;
    gotoXY(87, 22);
    std::cout << "  /         O" << std::flush;
    gotoXY(87, 23);
    std::cout << " /   (_____/ " << std::flush;
    gotoXY(87, 24);
    std::cout << "/_____/      " << std::flush;

    gotoXY(87, 26);
    std::cout << "Level: 1" << std::flush;

    gotoXY(87, 28);
    std::cout << "HP: [" << enemyHpBar << "]  0/10" << std::flush;

    gotoXY(87, 30);
    std::cout << "ATK: 2-4" << std::flush;

    gotoXY(102, 30);
    std::cout << "DEF: 1" << std::flush;

    gotoXY(87, 32);
    std::cout << "Something about enemy type" << std::flush;
}

void Game::drawEquipment() {
    drawWindow(120, 0, 36, 17, "EQUIPMENT", 13);

    //armor
    gotoXY(121, 2);
    std::cout << "ARMOR:" << std::flush;

    gotoXY(122, 3);
    std::cout << "Head: [Empty]" << std::flush;

    gotoXY(122, 4);
    std::cout << "Chest: Leather Tunic" << std::flush;
    gotoXY(148, 4);
    std::cout << "(DEF 2)" << std::flush;

    gotoXY(122, 5);
    std::cout << "Hands: [Empty]" << std::flush;

    gotoXY(122, 6);
    std::cout << "Legs: Cloth Pants" << std::flush;
    gotoXY(148, 6);
    std::cout << "(DEF 1)" << std::flush;

    gotoXY(122, 7);
    std::cout << "Boots: [Empty]" << std::flush;

    //weapon
    gotoXY(121, 9);
    std::cout << "WEAPON:" << std::flush;

    gotoXY(122, 10);
    std::cout << "R-Hand: Iron Longsword" << std::flush;
    gotoXY(148, 10);
    std::cout << "(ATK 4)" << std::flush;

    gotoXY(122, 11);
    std::cout << "L-Hand: Wooden Shield" << std::flush;
    gotoXY(148, 11);
    std::cout << "(DEF 2)" << std::flush;

    //Accessory
    gotoXY(121, 13);
    std::cout << "ACCESSORY:" << std::flush;

    gotoXY(122, 14);
    std::cout << "Ring: Ruby Signet" << std::flush;
    gotoXY(148, 14);
    std::cout << "(HP 5)" << std::flush;

    gotoXY(122, 15);
    std::cout << "Amulet: [Empty]" << std::flush;
}

void Game::drawBackpack() {
    drawWindow(120, 17, 36, 17, "BACKPACK", 10);

    gotoXY(130, 19);
    std::cout << "SLOTS: 0/12" << std::flush;

    for (int i = 0; i < 34; ++i) {
        gotoXY(121 + i, 20);
        std::cout << char(196) << std::flush;
    }

    for (int i = 1; i < 13; ++i) {
        gotoXY(122, 20 + i);
        std::cout << "[" << i << "] " << "--- Empty ---" << std::flush;
    }

}

void Game::drawAttributes() {
    drawWindow(90, 34, 66, 16, "ATTRIBUTES", 11);

    //primary
    gotoXY(93, 36);
    std::cout << "-- PRIMARY --" << std::flush;
    gotoXY(93, 37);
    std::cout << "Strength:" << std::flush;
    gotoXY(114, 37);
    std::cout << "14" << std::flush;
    gotoXY(93, 38);
    std::cout << "Dexterity:" << std::flush;
    gotoXY(114, 38);
    std::cout << "18" << std::flush;
    gotoXY(93, 39);
    std::cout << "Intelligence:" << std::flush;
    gotoXY(114, 39);
    std::cout << "10" << std::flush;
    gotoXY(93, 40);
    std::cout << "Constitution:" << std::flush;
    gotoXY(114, 40);
    std::cout << "12" << std::flush;

    //primary
    gotoXY(125, 36);
    std::cout << "-- DERIVED COMBAT --" << std::flush;
    gotoXY(125, 37);
    std::cout << "Melee Damage:" << std::flush;
    gotoXY(139, 37);
    std::cout << "8 - 12" << std::flush;
    gotoXY(125, 38);
    std::cout << "Critical Hit:" << std::flush;
    gotoXY(139, 38);
    std::cout << "5%" << std::flush;
    gotoXY(125, 39);
    std::cout << "Dodge Chance:" << std::flush;
    gotoXY(139, 39);
    std::cout << "12%" << std::flush;
    gotoXY(125, 40);
    std::cout << "Armor Class:" << std::flush;
    gotoXY(139, 40);
    std::cout << "4" << std::flush;

    //resistance
    gotoXY(93, 42);
    std::cout << "-- RESISTANCES --" << std::flush;
    gotoXY(93, 44);
    std::cout << "Physical: [" << resPhys << "] 0%" << std::flush;
    gotoXY(93, 46);
    std::cout << "Fire: [" << resFire << "] 0%" << std::flush;
    gotoXY(93, 48);
    std::cout << "Poison: [" << resPhys << "] 0%" << std::flush;

    //status
    gotoXY(125, 42);
    std::cout << "-- STATUS --" << std::flush;
    gotoXY(125, 44);
    std::cout << "Condition: Healthy" << std::flush;
    gotoXY(125, 46);
    std::cout << "Movement: Normal" << std::flush;
    gotoXY(125, 48);
    std::cout << "Vision: Darkvision" << std::flush;
}
