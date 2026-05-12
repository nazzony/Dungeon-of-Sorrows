#ifndef DUNGEON_OF_SORROWS_ITEM_H
#define DUNGEON_OF_SORROWS_ITEM_H

#include "Entity.h"

class Item : public Entity {
    char icon;
    int lootType;
public:
    Item(int xPos, int yPos);

    char getIcon();

    int getLootType();
};


#endif //DUNGEON_OF_SORROWS_ITEM_H