#include "Actor.h"

Actor::Actor(int xPos, int yPos, int colorCode)
: Entity(xPos, yPos, colorCode), hp{0} {

}

int Actor::getHP() { return hp; }

void Actor::setHP(int n) { hp = n; }

void Actor::takeDamage(int n) { hp -= n; }
