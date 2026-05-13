#include <iostream>
#include <cstdlib>
#include <ctime>

#include "utilities.h"
#include "Core/GameEngine.h"

using namespace std;

int main() {

    srand(time(0));

    hideCursor();

    GameEngine engine;
    engine.run();

}