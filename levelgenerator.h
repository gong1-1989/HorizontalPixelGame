#ifndef LEVELGENERATOR_H
#define LEVELGENERATOR_H
//横板场景生成器
#include <QList>
#include "tile.h"
#include "configmanager.h"

class LevelGenerator
{
public:
    static QList<Tile *> GenerateLevel();
};

#endif // LEVELGENERATOR_H
