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
    ,facingRight(true)
    ,attackTime(0)
    ,animState(ANIM_IDLE)
    ,animTimer(0)
    ,animFrame(0)
{
    resId = RES_PLAYER_IDLE;
    auto& cfg=ConfigManager::instance()->player;
    hp=cfg.hp;
    maxHp=cfg.maxHp;
    velX=0;
    velY=0;
    QSize sz=resourcemanager::instance()->GetSize(resId,0);
    width = sz.width();
    heigth = sz.height();
}
void Player::Update(float deltaTime)
{
    auto& phy=ConfigManager::instance()->physics;
    auto& pCfg=ConfigManager::instance()->player;
    //水平移动
    velX = 0;
    if (keyLeft){
        velX = -phy.moveSpeed;
        facingRight=false;
    }
    if (keyRight){
        velX = phy.moveSpeed;
        facingRight=true;
    }
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
    attackTime+=deltaTime;
    isAttacking=false;
    if(keyAttack&&attackTime>=pCfg.attackCd){
        isAttacking=keyAttack;
        attackTime=0;
    }
    //重力
    velY += phy.gravity * deltaTime;
    //位置更新
    pos.rx() += velX * deltaTime;
    pos.ry() += velY * deltaTime;
    //状态机优先级判定
    if(isAttacking) animState=ANIM_ATTACK;
    else if(!isGrounded) animState=ANIM_JUMP;
    else if(velX!=0) animState=ANIM_WALK;
    else animState=ANIM_IDLE;
    //帧动画播放
    animTimer+=deltaTime*pCfg.animSpeed;
    int maxFrame=0;
    switch (animState) {
    case ANIM_IDLE:
        maxFrame=pCfg.idleFrameCnt;
        break;
    case ANIM_WALK:
        maxFrame=pCfg.walkFrameCnt;
        break;
    case ANIM_JUMP:
        maxFrame=pCfg.jumpFrameCnt;
        break;
    case ANIM_ATTACK:
        maxFrame=pCfg.attackFrameCnt;
        break;
    }
    if(animTimer>=1.0f){
        animTimer=0;
        animFrame=(animFrame+1)%maxFrame;
    }

}