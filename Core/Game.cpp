#include "Game.h"
#include <chrono>
#include <thread>
#include <cstdlib>
#include <cmath>


Game::Game() : isRunning{true}, player(1 , 1), currentLevel{1} {
    // flickering reduction

    // Grab control of the Windows console
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;

    // Get the current cursor settings, change visibility to false, and apply them
    GetConsoleCursorInfo(consoleHandle, &cursorInfo);
    cursorInfo.bVisible = false;
    SetConsoleCursorInfo(consoleHandle, &cursorInfo);

    // -------------
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
                    }
                    break;
                }
            }



            for (int i = 0; i < items.size(); ++i) {
                if (targetX == items[i].getX() && targetY == items[i].getY()) {

                    if (items[i].getLootType() == 0) {
                        player.setHP(player.getHP() + 3);
                        actionMessage = "You found a glowing Potion! +3 HP";
                    } else if (items[i].getLootType() == 1) {
                        int foundGold = rand() % 20 + 30;
                        currentGold += foundGold;
                        actionMessage = "You found a stash of coins! +" + std::to_string(foundGold) + " Gold";
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
                } else {
                    actionMessage = "You carefully tread through the shadows...";
                }

            }
        }
    }
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
    // flickering reduction part 2
    // Teleport the invisible cursor to the top-left corner
    COORD cursorPosition;
    cursorPosition.X = 0;
    cursorPosition.Y = 0;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursorPosition);

    grid.render();
    std::cout << std::endl << std::endl << actionMessage << "                         " << std::endl;
    std::cout << "Depth: " << currentLevel << "   |   HP: " << player.getHP() << "   |   Gold: " << currentGold << "    ";
}

void Game::nextLevel() {
    ++currentLevel;

    grid = Map();

    actionMessage = "You descend deeper into the dungeon...";

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
