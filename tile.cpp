#include "tile.h"

Tile::Tile()
    : isSolid(true),behavior(BEHAVIOR_NORMAL)
    ,moveSpeed(80),moveRange(100),originX(0),originY(0)
    ,moveDir(1),trapDamage(10),trapCd(0)
{
    width = 32;
    heigth = 32;
}

void Tile::Update(float deltaTime){
    if(behavior==BEHAVIOR_MOVE_HORIZ){
        pos.rx()+=moveSpeed*moveDir*deltaTime;
        if(pos.x()>+moveRange||pos.x()<originX-moveRange) moveDir*=-1;
    }
    if(behavior==BEHAVIOR_MOVE_VERT){
        pos.ry()+=moveSpeed*moveDir*deltaTime;
        if(pos.y()>originY+moveRange||pos.y()<originY-moveRange) moveDir*=-1;
    }
    trapCd+=deltaTime;
}