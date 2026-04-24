#include "Game.h"
#include <chrono>
#include <thread>
#include <cstdlib>


Game::Game() : isRunning{true}, player(5, 5) {
    grid.spawnEntity(player.getX(), player.getY(), player.getIcon());
    grid.revealArea(player.getX(), player.getY());
}

void Game::handleInput() {
    char input;
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
            default: break;
        }

        if (needToMove && grid.isWalkable(targetX, targetY)) {
            grid.spawnEntity(player.getX(), player.getY(), player.getPrev());

            player.setX(targetX);
            player.setY(targetY);

            player.setPrev(grid.getCharAt(player.getX(), player.getY()));

            grid.spawnEntity(player.getX(), player.getY(), player.getIcon());
            grid.revealArea(player.getX(), player.getY());
        }

        if (input == 'q' || input == 'Q') isRunning = false;

    }
}

void Game::run() {
    render();
    while (isRunning) {
        handleInput();
        render();
        std::this_thread::sleep_for(std::chrono::milliseconds(16));
    }
}

void Game::render() {
    system("cls");
    grid.render();
}

void Game::input() {

}
