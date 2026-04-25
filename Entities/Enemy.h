#ifndef DUNGEON_OF_SORROWS_ENEMY_H
#define DUNGEON_OF_SORROWS_ENEMY_H

#include "Entity.h"

class Enemy : public Entity {
private:
    char icon;

public:
    Enemy(int x, int y);

    char getIcon();

    void setIcon(char n);

};


#endif //DUNGEON_OF_SORROWS_ENEMY_H