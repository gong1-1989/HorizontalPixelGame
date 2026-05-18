#ifndef COLLISIONSYSTEM_H
#define COLLISIONSYSTEM_H
//全局碰撞系统
#include "tile.h"
#include "Player.h"
#include <QRectF>
#include <QList>

class CollisionSystem
{
public:
    static bool CheckCollision(const QRectF& a,const QRectF& b);
    static void ResolveCollision(Player* player,const QList<Tile*> tiles);
};

#endif // COLLISIONSYSTEM_H
