#include "Game.h"
#include <chrono>
#include <thread>
#include <cstdlib>


Game::Game() : isRunning{true}, player(5, 5) {
    grid.spawnEntity(player.getX(), player.getY(), player.getIcon());
}

void Game::handleInput() {
    char input;
    if (_kbhit()) {

        input = char(_getch());

        std::cout << "You pressed letter: " << input << std::endl;
        switch (input) {
            case 'w':
                grid.spawnEntity(player.getX(), player.getY(), player.getPrev());
                player.moveUp();
                player.setPrev(grid.getCharAt(player.getX(), player.getY()));
                grid.spawnEntity(player.getX(), player.getY(), player.getIcon());
                break;
            case 's':
                grid.spawnEntity(player.getX(), player.getY(), player.getPrev());
                player.moveDown();
                player.setPrev(grid.getCharAt(player.getX(), player.getY()));
                grid.spawnEntity(player.getX(), player.getY(), player.getIcon());
                break;
            case 'a':
                grid.spawnEntity(player.getX(), player.getY(), player.getPrev());
                player.moveLeft();
                player.setPrev(grid.getCharAt(player.getX(), player.getY()));
                grid.spawnEntity(player.getX(), player.getY(), player.getIcon());
                break;
            case 'd':
                grid.spawnEntity(player.getX(), player.getY(), player.getPrev());
                player.moveRight();
                player.setPrev(grid.getCharAt(player.getX(), player.getY()));
                grid.spawnEntity(player.getX(), player.getY(), player.getIcon());
                break;
            default:
                break;
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
