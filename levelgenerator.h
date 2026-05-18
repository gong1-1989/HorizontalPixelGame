#ifndef LEVELGENERATOR_H
#define LEVELGENERATOR_H
//横板场景生成器
#include <QList>
#include <QPoint>
#include <QHash>
#include "tile.h"
#include "configmanager.h"

class LevelGenerator
{
public:
    static QList<Tile *> GenerateLevel(int levelLength);

private:
    //根据权重随机选取一个地块
    static LevelChunk RandomSelectChunk();
    //生成单段场景，保证基础通道连通
    static QList<Tile *> GenerateSegment(int startX,const LevelChunk& chunk);
    //校验场景重点可到达：BFS寻路
    static bool CheckLevelPassable(const QList<Tile *> &tiles,QPoint startPos);
    //获取瓦片的网络坐标
    static QPoint TileToGrid(Tile* tile);
};

#endif // LEVELGENERATOR_H
