#ifndef DUNGEON_OF_SORROWS_ENTITY_H
#define DUNGEON_OF_SORROWS_ENTITY_H


class Entity {
protected:
    int x;
    int y;
    char prev;
    int color;
public:
    Entity(int x, int y, int color);

    int getX();
    int getY();
    char getPrev();
    int getColor();

    void setX(int n);
    void setY(int n);
    void setPrev(char n);
    void setColor(int colorCode);

    void moveUp();
    void moveDown();
    void moveLeft();
    void moveRight();

};


#endif //DUNGEON_OF_SORROWS_ENTITY_H