#include "Enemy.h"

Enemy::Enemy(int x, int y) : Entity(x, y), icon{'E'} {
    hp = 3;
}

char Enemy::getIcon() { return icon; }

void Enemy::setIcon(char n) { icon = n; }
