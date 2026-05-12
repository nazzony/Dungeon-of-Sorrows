#ifndef DUNGEON_OF_SORROWS_ENEMY_H
#define DUNGEON_OF_SORROWS_ENEMY_H

#include "Actor.h"

class Enemy : public Actor {
private:
    char icon;

public:
    Enemy(int x, int y);

    char getIcon();

    void setIcon(char n);

};


#endif //DUNGEON_OF_SORROWS_ENEMY_H