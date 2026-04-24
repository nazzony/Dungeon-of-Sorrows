#include "Game.h"
#include <chrono>
#include <thread>
#include <cstdlib>


Game::Game() : isRunning{true}, player(5, 5) {

    // flickering reduction

    // Grab control of the Windows console
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;

    // Get the current cursor settings, change visibility to false, and apply them
    GetConsoleCursorInfo(consoleHandle, &cursorInfo);
    cursorInfo.bVisible = false;
    SetConsoleCursorInfo(consoleHandle, &cursorInfo);




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
}

void Game::input() {

}
