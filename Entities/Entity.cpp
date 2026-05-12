#include "Entity.h"

Entity::Entity(int xPos, int yPos, int color) : x{0}, y{0}, prev{char(249)}, hp{100} {
    setX(xPos);
    setY(yPos);
    setColor(color);
}

int Entity::getX() { return x; }
int Entity::getY() { return y; }
char Entity::getPrev() { return prev; }
int Entity::getHP() { return hp; }
int Entity::getColor() { return color; }



void Entity::setX(int n) { if (n >= 0) x = n; }
void Entity::setY(int n) { if (n >= 0) y = n; }
void Entity::setPrev(char n) { prev = n; }
void Entity::setHP(int n) { hp = n; }
void Entity::setColor(int colorCode) { color = colorCode; }




void Entity::moveUp() { --y; }
void Entity::moveDown() { ++y; }
void Entity::moveLeft() { --x; }
void Entity::moveRight() { ++x; }

void Entity::takeDamage(int n) { hp -= n; }
