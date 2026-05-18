#ifndef MONSTER_H
#define MONSTER_H
//怪物实体子类
#include "entity.h"
#include "player.h"

class Monster:public entity
{
public:
    Monster();
    int hp;
    int maxHp;
    float patrolStartX;
    float patrolEndX;
    bool isChasing;
    float attackTimer;
    void Update(float deltaTime,Player*player);
};

#endif // MONSTER_H
