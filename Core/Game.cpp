#include "Game.h"

Game::Game() : isRunning{true} {}

void Game::handleInput() {
    std::cout << "Quiting program" << std::endl;
    isRunning = false;
}

void Game::run() {
    render();
    while (isRunning) {
        input();
        render();
    }
}

void Game::render() {

}

void Game::input() {
    std::string input;

    std::cout << "Input:";
    std::cin >> input;

    if (input == "Q" || input == "q") {
        handleInput();
    }

}
