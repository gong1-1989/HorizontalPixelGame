#ifndef COLLISIONSYSTEM_H
#define COLLISIONSYSTEM_H
//全局碰撞系统
#include <QList>
#include <QRectF>
#include <QRandomGenerator>
#include "Player.h"
#include "tile.h"
#include "monster.h"
#include "item.h"
#include "portal.h"

class CollisionSystem
{
public:
    static bool CheckCollision(const QRectF &a, const QRectF &b);
    static void ResolveCollision(Player *player, const QList<Tile *> tiles);
    static void ResolveCollision(Monster *monster,const QList<Tile*> tiles);
    //玩家攻击怪物判定
    static void CheckPlayerAttack(Player* p,QList<Monster*>& mons);
    //怪物攻击玩家判定
    static void CheckMonsterAttack(Player* p,QList<Monster*>& mons);
    //道具拾取
    static void CheckItemPick(Player* p,QList<Item*>& items,int & coin);
    //传送门通关检测
    static bool CheckPortalEnter(Player* p,Portal* portal);
};

#endif // COLLISIONSYSTEM_H
