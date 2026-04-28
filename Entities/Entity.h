#ifndef DUNGEON_OF_SORROWS_ENTITY_H
#define DUNGEON_OF_SORROWS_ENTITY_H


class Entity {
protected:
    int x;
    int y;
    char prev;
    int hp;
public:
    Entity(int x, int y);

    int getX();
    int getY();
    char getPrev();
    int getHP();

    void setX(int n);
    void setY(int n);
    void setPrev(char n);
    void setHP(int n);

    void moveUp();
    void moveDown();
    void moveLeft();
    void moveRight();

    void takeDamage(int n);



};


#endif //DUNGEON_OF_SORROWS_ENTITY_H