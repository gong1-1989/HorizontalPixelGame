#ifndef LEVELGENERATOR_H
#define LEVELGENERATOR_H
//横板场景生成器
#include <QList>
#include "tile.h"

class LevelGenerator
{
public:
    static QList<Tile*> GenerateLevel(int levelLength);
private:
    //生成单段场景，保证基础通道连通
    static QList<Tile*> GenerateSegment(int startX);
    //校验场景重点可到达
    static bool CheckLevelPassable(const QList<Tile*>& tiles);
};

#endif // LEVELGENERATOR_H
