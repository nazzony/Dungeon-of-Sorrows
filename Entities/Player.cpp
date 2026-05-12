#include "Player.h"

Player::Player(int xPos, int yPos) : Entity(xPos, yPos, 1), icon{'@'} {}

char Player::getIcon() { return icon; }