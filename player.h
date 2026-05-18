#ifndef PLAYER_H
#define PLAYER_H
//玩家实体子类
#include "entity.h"
#include <QKeyEvent>

//物理参数（后期可直接挪到JSon配置）
#define GRAVITY 980.0f
#define MOVE_SPEED 280.0f
#define JUMP_FORCE 420.0f
#define DOUBLE_JUMP_FORCE 360.0f

class Player:public entity
{
public:
    Player();
    //按键状态
    bool keyLeft;
    bool keyRight;
    bool keyJump;
    bool jumpPressed;
    bool canDoubleJump;
    void Update(float deltaTime) override;
};

#endif // PLAYER_H
