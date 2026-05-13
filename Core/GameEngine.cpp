#include "GameEngine.h"

GameEngine::GameEngine() : currentState{MAIN_MENU}, lastDepth{1}, lastGold{0} {}

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
    setConsoleColor(1);
    std::cout << R"(
                                                                      ____  __  __  _   __  ______  ______  ____   _   __
                                                                     / __ \/ / / / / | / / / ____/ / ____/ / __ \ / | / /
                                                                    / / / / / / / /  |/ / / / __  / __/   / / / //  |/ /
                                                                   / /_/ / /_/ / / /|  / / /_/ / / /___  / /_/ // /|  /
                                                                  /_____/\____/ /_/ |_/  \____/ /_____/  \____//_/ |_/

                                                                                         ____   ______
                                                                                        / __ \ / ____/
                                                                                       / / / // /_
                                                                                      / /_/ // __/
                                                                                      \____//_/

                                                                     _____   ____   ____   ____   ____  _       __  _____
                                                                    / ___/  / __ \ / __ \ / __ \ / __ \| |     / / / ___/
                                                                   \__ \  / / / // /_/ // /_/ // / / /| | /| / /  \__ \
                                                                  ___/ / / /_/ // _, _// _, _// /_/ / | |/ |/ /  ___/ /
                                                                 /____/  \____//_/ |_|/_/ |_| \____/  |__/|__/  /____/
    )" << '\n';

    setConsoleColor(7);  // Reset to Gray for the menu options

    std::cout << "\t                                                     ==============================================================\n";
    setConsoleColor(14);
    std::cout << "\t                                                                              [1] Play                    \n";
    std::cout << "\t                                                                              [2] Unlocks                 \n";
    std::cout << "\t                                                                              [3] Settings                \n";
    std::cout << "\t                                                                              [4] Quit                    \n";
    setConsoleColor(7);
    std::cout << "\t                                                     ==============================================================\n";
    std::cout << "\t                                                                        Press a number to continue        \n";

    setConsoleColor(8);
    std::cout << "\n\n\n\n\n\n";
    std::cout << "                                                                                                                                                                    made by nazzony";
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
