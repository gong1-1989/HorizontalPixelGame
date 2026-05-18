#ifndef TILE_H
#define TILE_H
//场景瓦片实体子类：地面、平台
#include "entity.h"
class Tile : public entity
{
public:
    Tile();
    bool isSolid; //是否为实心碰撞体
};

#endif // TILE_H
