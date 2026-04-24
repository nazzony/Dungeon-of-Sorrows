#include "Game.h"
#include <chrono>
#include <thread>
#include <cstdlib>


Game::Game() : isRunning{true} {}

void Game::handleInput() {
    char input;
    if (_kbhit()) {

        input = char(_getch());

        std::cout << "You pressed letter: " << input << std::endl;
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
