#include "Game.h"
#include <chrono>
#include <thread>
#include <cstdlib>
#include <cmath>


Game::Game() : isRunning{true}, player(5, 5), enemy(15, 6), currentLevel{1} {
    actionMessage = "You Enter The Dark Dungeon...";

    // flickering reduction

    // Grab control of the Windows console
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;

    // Get the current cursor settings, change visibility to false, and apply them
    GetConsoleCursorInfo(consoleHandle, &cursorInfo);
    cursorInfo.bVisible = false;
    SetConsoleCursorInfo(consoleHandle, &cursorInfo);

    // -------------

    grid.spawnEntity(player.getX(), player.getY(), player.getIcon());
    grid.revealArea(player.getX(), player.getY());

    grid.spawnEntity(enemy.getX(), enemy.getY(), enemy.getIcon());

    grid.spawnEntity(18, 7, '>');
}

void Game::handleInput() {
    char input;
    bool attacked = false;
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
                    grid.spawnEntity(targetX, targetY, char(250));
                    actionMessage = "Congrats! You defeated an enemy";
                }

            }
            else if (grid.isWalkable(targetX, targetY)) {

                grid.spawnEntity(player.getX(), player.getY(), player.getPrev());

                player.setX(targetX);
                player.setY(targetY);

                player.setPrev(grid.getCharAt(player.getX(), player.getY()));

                grid.spawnEntity(player.getX(), player.getY(), player.getIcon());
                grid.revealArea(player.getX(), player.getY());

            }
        }
        if (input == 'q' || input == 'Q') isRunning = false;

        if (!attacked) {
            int distX = std::abs(player.getX() - enemy.getX());
            int distY = std::abs(player.getY() - enemy.getY());

            if (player.getPrev() == '>') {
                actionMessage = "Press Space to Descend";
            } else if (distX <= 1 && distY <= 1 && enemy.getHP() > 0) {
                actionMessage = "A hostile enemy is near. HP: " + std::to_string(enemy.getHP());
            } else {
                actionMessage = "You carefully tread through the shadows...";
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
    std::cout << "Depth: " << currentLevel;
}

void Game::nextLevel() {
    ++currentLevel;

    grid = Map();

    player.setX(5);
    player.setY(5);
    player.setPrev('.');
    grid.spawnEntity(player.getX(), player.getY(), player.getIcon());

    enemy.setX(3);
    enemy.setY(8);
    enemy.setHP(3);
        grid.spawnEntity(enemy.getX(), enemy.getY(), enemy.getIcon());

    grid.spawnEntity(18, 7, '>');


    grid.revealArea(player.getX(), player.getY());

    actionMessage = "You descend deeper into the dungeon...";
}
