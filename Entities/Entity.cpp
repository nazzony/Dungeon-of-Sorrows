#include "Entity.h"

Entity::Entity(int xPos, int yPos, int color) : x{0}, y{0}, prev{char(249)} {
    setX(xPos);
    setY(yPos);
    setColor(color);
}

int Entity::getX() { return x; }
int Entity::getY() { return y; }
char Entity::getPrev() { return prev; }
int Entity::getColor() { return color; }



void Entity::setX(int n) { if (n >= 0) x = n; }
void Entity::setY(int n) { if (n >= 0) y = n; }
void Entity::setPrev(char n) { prev = n; }
void Entity::setColor(int colorCode) { color = colorCode; }




void Entity::moveUp() { --y; }
void Entity::moveDown() { ++y; }
void Entity::moveLeft() { --x; }
void Entity::moveRight() { ++x; }
