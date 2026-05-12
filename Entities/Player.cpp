#include "Player.h"

Player::Player(int xPos, int yPos)
: Actor(xPos, yPos, 1), icon{'@'} {
    setHP(10);
}

char Player::getIcon() { return icon; }