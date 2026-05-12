#ifndef DUNGEON_OF_SORROWS_ACTOR_H
#define DUNGEON_OF_SORROWS_ACTOR_H

#include "Entity.h"

class Actor : public Entity {
protected:
    int hp;
public:
    Actor(int xPos, int yPos, int colorCode);

    int getHP();

    void setHP(int n);

    void takeDamage(int n);

};


#endif //DUNGEON_OF_SORROWS_ACTOR_H