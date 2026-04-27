#include <iostream>
#include <cstdlib>
#include <ctime>

#include "Core/Game.h"

using namespace std;

int main() {

    srand(time(0));

    Game game;

    game.run();

}