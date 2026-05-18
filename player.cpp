#include "player.h"

Player::Player()
    :keyLeft(false)
    ,keyRight(false)
    ,keyJump(false)
    ,jumpPressed(false)
    ,canDoubleJump(true){
    width=32;
    height-32;
    resId=RES_PLAYER_IDLE;
}
void Player::Update(float deltaTime){
    //水平移动
    if(keyLeft)velX=-MOVE_SPEED;
    else if(keyRight)velX=MOVE_SPEED;
    else velX=0;
    //二段跳逻辑
    if(keyJump&&!jumpPressed){
        if(isGrounded){
            velY=-JUMP_FORCE;
            isGrounded=false;
            canDoubleJump=true;
        }else if(canDoubleJump){
            velY=-DOUBLE_JUMP_FORCE;
            canDoubleJump=false;
        }
        jumpPressed=true;
    }
    if(!keyJump) jumpPressed=false;
    //重力
    velY+=GRAVITY*deltaTime;
    //位置更新
    pos.rx()+=velX*deltaTime;
    pos.ry()+=velY*deltaTime;
}