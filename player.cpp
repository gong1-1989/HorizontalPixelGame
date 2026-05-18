#include "player.h"
#include "configManager.h"

Player::Player()
    : keyLeft(false)
    , keyRight(false)
    , keyJump(false)
    , jumpPressed(false)
    , canDoubleJump(true)
    ,isAttacking(false)
    ,keyAttack(false)
{
    width = 32;
    heigth = 32;
    resId = RES_PLAYER_IDLE;
    auto& cfg=ConfigManager::instance()->player;
    hp=cfg.hp;
    maxHp=cfg.maxHp;
    velX=0;
    velY=0;
}
void Player::Update(float deltaTime)
{
    auto& phy=ConfigManager::instance()->physics;
    //水平移动
    velX = 0;
    if (keyLeft)
        velX = -phy.moveSpeed;
    if (keyRight)
        velX = phy.moveSpeed;
    //二段跳逻辑
    if (keyJump && !jumpPressed) {
        if (isGrounded) {
            velY = -phy.jumpForce;
            isGrounded = false;
            canDoubleJump = true;
        } else if (canDoubleJump) {
            velY = -phy.doubleJumpForce;
            canDoubleJump = false;
        }
        jumpPressed = true;
    }
    if (!keyJump)
        jumpPressed = false;
    //攻击判定
    isAttacking=keyAttack;
    //重力
    velY += phy.gravity * deltaTime;
    //位置更新
    pos.rx() += velX * deltaTime;
    pos.ry() += velY * deltaTime;
}