#include "monster.h"
#include <cmath>
#include "resourcemanager.h"
#include "configmanager.h"

Monster::Monster()
    :isChasing(false),attackTimer(0){
    width=32;
    heigth=30;
    resId=RES_MONSTER_NORMAL;
    auto& cfg=ConfigManager::instance()->monster;
    hp=cfg.hp;
    maxHp=cfg.maxHp;
}

void Monster::Update(float deltaTime, Player *player){
    attackTimer+=deltaTime;
    float dist=pos.x()-player->pos.x();
    auto& cfg=ConfigManager::instance()->monster;
    //追击逻辑
    if(fabs(dist)<cfg.chaseRange){
        isChasing=true;
        if(dist>10) velX=-cfg.speed;
        else if(dist<-10) velX=cfg.speed;
        else velX=0;
    }
    //巡逻逻辑
    else{
        isChasing=false;
        if(pos.x()<=patrolStartX) velX=cfg.speed;
        else if(pos.x()>=patrolEndX) velX=-cfg.speed;
    }
    //重力
    auto& phy=ConfigManager::instance()->physics;
    velY+=phy.gravity*deltaTime;
    pos.rx()+=velX*deltaTime;
    pos.ry()+=velY*deltaTime;
}