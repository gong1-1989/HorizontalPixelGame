#include "levelgenerator.h"
#include <QRandomGenerator>
#include "resourcemanager.h"

QList<Tile*> LevelGenerator::GenerateLevel(int levelLength) {
    QList<Tile*> tiles;
    int currentX=0;
    //分段生成场景
    while(currentX<levelLength){
        auto seg=GenerateSegment(currentX);
        tiles.append(seg);
        currentX+=32*12;    //每段固定长度
    }
    //场景不可通行则重新生成
    if(!CheckLevelPassable(tiles)){
        return GenerateLevel(levelLength);
    }
    return tiles;
}

QList<Tile*> LevelGenerator::GenerateSegment(int startX){
    QList<Tile*> seg;
    //底部固定地面（保底连接通道）
    for (int i=0;i<12;i++){
        Tile* t=new Tile();
        t->pos=QPointF(startX+i*32,450);
        t->resId=RES_GROUND;
        seg.append(t);
    }
    //随机生成浮空平台
    int platformCount=QRandomGenerator::global()->bounded(2,5);
    for(int i=0;i<platformCount;i++){
        Tile* t=new Tile();
        int px=startX+QRandomGenerator::global()->bounded(2,10)*32;
        int py=QRandomGenerator::global()->bounded(200,400);
        t->pos=QPointF(px,py);
        t->resId=RES_PLATFORM;
        seg.append(t);
    }
    return seg;
}

bool LevelGenerator::CheckLevelPassable(const QList<Tile *> &tiles){
    //简化校验：存在底层地面即判定可通行
    for(auto t:tiles){
        if(t->pos.y()==450) return true;
    }
    return false;
}
