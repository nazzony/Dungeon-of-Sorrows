#include "Player.h"

Player::Player(int xPos, int yPos) : Entity(xPos, yPos), icon{'@'} {}

char Player::getIcon() { return icon; }