#include "GameEngine.h"
#include <vector>
#include <string>

GameEngine::GameEngine() : currentState{MAIN_MENU}, lastDepth{1}, lastGold{0} {
}

void GameEngine::run() {
    while (currentState != EXIT) {
        switch (currentState) {
            case MAIN_MENU: stateMainMenu(); break;
            case PLAYING: statePlaying(); break;
            case DEVELOPMENT: stateDevelopment(); break;
            case GAME_OVER: stateGameOver(); break;
            default: break;
        }
    }
}

void GameEngine::stateMainMenu() {
    system("cls");
    Sleep(50);

    //for clion use 0
    //for bash use 1
    bool terminal = 0;
    int menuX;
    int menuY;
    int mult;

    if (!terminal) {
        menuX = 40;
        menuY = 0;
        mult = 1;
    } else {
        menuX = 55;
        menuY = 3;
        mult = 2;
    }

    setConsoleColor(1);

    std::vector<std::string> title = {
        "    ____  __  __  _   __  ______  ______  ____   _   __",
        "   / __ \\/ / / / / | / / / ____/ / ____/ / __ \\ / | / /",
        "  / / / / / / / /  |/ / / / __  / __/   / / / //  |/ /",
        " / /_/ / /_/ / / /|  / / /_/ / / /___  / /_/ // /|  /",
        "/_____/\\____/ /_/ |_/  \\____/ /_____/  \\____//_/ |_/",
        "\t",
        "\t\t   ____   ______",
        "\t\t  / __ \\ / ____/",
        "\t\t / / / // /_",
        "\t\t/ /_/ // __/",
        "\t\t\\____//_/",
        "\t",
        "   _____   ____   ____   ____   ____  _       __  _____",
        "  / ___/  / __ \\ / __ \\ / __ \\ / __ \\| |     / / / ___/",
        "  \\__ \\  / / / // /_/ // /_/ // / / /| | /| / /  \\__ \\",
        " ___/ / / /_/ // _, _// _, _// /_/ / | |/ |/ /  ___/ /",
        "/____/  \\____//_/ |_|/_/ |_| \\____/  |__/|__/  /____/"
    };

    for (int i = 0; i < title.size(); ++i) {
        gotoXY(menuX, menuY + i);
        std::cout << title[i] << std::flush;
    }

    menuY = menuY + title.size() + 1;

    setConsoleColor(7);
    gotoXY(menuX - 4, menuY);
    std::cout << "==============================================================" << std::flush;

    int textOffset = 23;
    setConsoleColor(14);
    gotoXY(menuX + textOffset, menuY + 1 * mult);
    std::cout << "[1] Play" << std::flush;
    gotoXY(menuX + textOffset, menuY + 2 * mult);
    std::cout << "[2] Unlocks" << std::flush;
    gotoXY(menuX + textOffset, menuY + 3 * mult);
    std::cout << "[3] Settings" << std::flush;
    gotoXY(menuX + textOffset, menuY + 4 * mult);
    std::cout << "[4] Quit" << std::flush;

    setConsoleColor(7);
    gotoXY(menuX - 4, menuY + 5 * mult);
    std::cout << "==============================================================" << std::flush;
    gotoXY(menuX + 13, menuY + 6 * mult);
    std::cout << "Press a number to continue" << std::flush;

    setConsoleColor(8);
    gotoXY(menuX + textOffset + 50, menuY + 26);
    std::cout << " made by nazzony" << std::flush;

    setConsoleColor(7);

    char choice = _getch();
    if (choice == '1') currentState = PLAYING;
    else if (choice == '2') currentState = DEVELOPMENT;
    else if (choice == '3') currentState = DEVELOPMENT;
    else if (choice == '4') currentState = EXIT;
}

void GameEngine::statePlaying() {
    Game game;
    game.run();

    int lastDepth = game.getCurrentLevel();
    int lastGold = game.getCurrentGold();

    if (game.isPlayerDead()) {
        currentState = GAME_OVER;
    } else {
        currentState = MAIN_MENU;
    }
}

void GameEngine::stateDevelopment() {
    system("cls");
    setConsoleColor(4);
    std::cout << "\t This Page is Still in Development\n\n";
    std::cout << "\t Press Q to Return\n";
    setConsoleColor(7);
    char choice = _getch();
    if (choice == 'q' || choice == 'Q') currentState = MAIN_MENU;
}


void GameEngine::stateGameOver() {
    system("cls");
    setConsoleColor(4);
    std::cout << "\n\n\t\t *** YOU DIED *** \n\n";
    setConsoleColor(7);

    std::cout << "\t You made it to Depth: " << lastDepth << "\n";
    std::cout << "\t You collected " << lastGold << " Gold.\n\n";
    std::cout << "\t Press any key to return to Main Menu...\n";

    _getch();
    currentState = MAIN_MENU;
}
