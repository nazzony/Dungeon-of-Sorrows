#include "./Item.h"

#include <cstdlib>

Item::Item(int xPos, int yPos) : Entity(xPos, yPos, 13), icon{'*'} {
    lootType = rand() % 2;
}

char Item::getIcon() { return icon; }

int Item::getLootType() { return lootType; }
