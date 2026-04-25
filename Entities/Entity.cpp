#include "Entity.h"

Entity::Entity(int xPos, int yPos) : x{0}, y{0}, prev{'.'}, hp{100} {
    setX(xPos);
    setY(yPos);
}

int Entity::getX() { return x; }
int Entity::getY() { return y; }
char Entity::getPrev() { return prev; }
int Entity::getHP() { return hp; }


void Entity::setX(int n) { if (n >= 0) x = n; }
void Entity::setY(int n) { if (n >= 0) y = n; }
void Entity::setPrev(char n) { prev = n; }
void Entity::setHP(int n) { hp = n; }



void Entity::moveUp() { --y; }
void Entity::moveDown() { ++y; }
void Entity::moveLeft() { --x; }
void Entity::moveRight() { ++x; }

void Entity::takeDamage(int n) { hp -= n; }
