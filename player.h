#ifndef PLAYER_H
#define PLAYER_H
//玩家实体子类
#include <QKeyEvent>
#include "entity.h"

class Player : public entity
{
public:
    Player();
    //按键状态
    bool keyLeft;
    bool keyRight;
    bool keyJump;
    bool jumpPressed;
    bool canDoubleJump;
    bool isAttacking;
    bool keyAttack;
    int hp;
    int maxHp;
    void Update(float deltaTime) override;
};

#endif // PLAYER_H
