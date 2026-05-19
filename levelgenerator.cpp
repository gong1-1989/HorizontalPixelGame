#include "levelgenerator.h"
#include "resourcemanager.h"

QList<Tile *> LevelGenerator::GenerateLevel()
{
    QList<Tile *> tiles;
    auto& levelCfg=ConfigManager::instance()->level;
    for(auto& td:levelCfg.tiles){
        //自适应尺寸逻辑
        QSize texSize=resourcemanager::instance()->GetSize(td.resId,0);
        int w=td.width>0 ? td.width : texSize.width();
        int h=td.heigth>0 ? td.heigth : texSize.height();
        for(auto& pos:td.pos){
            Tile* t=new Tile();
            t->pos=QPointF(pos.x,pos.y);
            t->originX=pos.x;
            t->originY=pos.y;
            t->width=w;
            t->heigth=h;
            t->isSolid=td.isSolid;
            t->behavior=td.behavior;
            t->moveSpeed=td.moveSpeed;
            t->moveRange=td.moveRange;
            t->trapDamage=td.trapDamage;
            t->resId=td.resId;
            tiles.append(t);
        }
    }
    return tiles;
}