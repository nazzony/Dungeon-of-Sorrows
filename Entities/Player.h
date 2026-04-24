#ifndef DUNGEON_OF_SORROWS_PLAYER_H
#define DUNGEON_OF_SORROWS_PLAYER_H

#include "Entity.h"

class Player : public Entity {
private:
    char icon;
public:
    Player(int xPos, int yPos);

    char getIcon();
};


#endif //DUNGEON_OF_SORROWS_PLAYER_H