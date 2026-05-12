#include "Enemy.h"

Enemy::Enemy(int x, int y) : Actor(x, y, 4), icon{'E'} {
    setHP(3);
}

char Enemy::getIcon() { return icon; }

void Enemy::setIcon(char n) { icon = n; }
