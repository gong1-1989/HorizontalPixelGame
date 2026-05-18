#ifndef TILE_H
#define TILE_H
//场景瓦片实体子类：地面、平台
#include "entity.h"
#include "configmanager.h"
class Tile : public entity
{
public:
    Tile();
    bool isSolid; //是否为实心碰撞体
    TileBehavior behavior;
    //移动平台专用
    float moveSpeed;
    int moveRange;
    float originX,originY;
    int moveDir;
    //陷阱专用
    int trapDamage;
    float trapCd;
    void Update(float deltaTime)override;
};

#endif // TILE_H
