#include "levelgenerator.h"
#include <QRandomGenerator>
#include <QQueue>
#include <QSet>
#include "resourcemanager.h"

LevelChunk LevelGenerator::RandomSelectChunk(){
    auto& list=ConfigManager::instance()->chunkList;
    int totalWeight=0;
    for(auto& c:list) totalWeight+=c.weight;
    int rnd=QRandomGenerator::global()->bounded(totalWeight);
    int cur=0;
    for(auto& c:list){
        cur+=c.weight;
        if(rnd<cur) return c;
    }
    return list.first();
}

QList<Tile *> LevelGenerator::GenerateLevel(int levelLength)
{
    QList<Tile *> tiles;
    int currentX = 0;
    int chunkW=ConfigManager::instance()->level.chunkWidth;
    //分段生成场景
    while (currentX < levelLength) {
        auto chunk=RandomSelectChunk();
        auto seg = GenerateSegment(currentX,chunk);
        tiles.append(seg);
        currentX += chunkW; //每段固定长度
    }
    //场景不可通行则重新生成
    QPoint startGrid(3,14);//出生位置网格
    if (!CheckLevelPassable(tiles,startGrid)) {
        for(auto t:tiles) delete t; //清理旧瓦片，避免内存泄露
        return GenerateLevel(levelLength);
    }
    return tiles;
}

QList<Tile *> LevelGenerator::GenerateSegment(int startX, const LevelChunk &chunk)
{
    QList<Tile *> seg;
    //底部固定地面（保底连接通道）
    for (int i = 0; i < 12; i++) {
        Tile *t = new Tile();
        t->pos = QPointF(startX + i * 32, chunk.fixedBaseY);
        t->width=32;
        t->heigth=32;
        t->isSolid=true;
        t->behavior=BEHAVIOR_NORMAL;
        t->resId = RES_GROUND;
        seg.append(t);
    }

    //生成改地块模板中定义的所有瓦片
    for(auto& td:chunk.tiles){
        Tile* t=new Tile();
        int localX=QRandomGenerator::global()->bounded(2,10)*td.width;
        t->pos=QPointF(startX+localX,QRandomGenerator::global()->bounded(200,400));
        t->width=td.width;
        t->heigth=td.heigth;
        t->isSolid=td.isSolid;
        t->behavior=td.behavior;
        t->resId=td.resId;
        t->moveSpeed=td.moveSpeed;
        t->moveRange=td.moveRange;
        t->trapDamage=td.trapDamage;
        seg.append(t);
    }
    return seg;
}

QPoint LevelGenerator::TileToGrid(Tile *tile){    
    //转成32像素一格的网格坐标
    int gx=tile->pos.x()/32;
    int gy=tile->pos.y()/32;
    return QPoint(gx,gy);
}

bool LevelGenerator::CheckLevelPassable(const QList<Tile *> &tiles, QPoint startPos)
{
    //建立网格-瓦片映射
    QHash<QPoint,bool> gridMap;
    int maxX=0;
    for (auto t : tiles) {
        QPoint g=TileToGrid(t);
        gridMap[g]=t;
        if(g.x()>maxX)maxX=g.x();
    }
    //BFS队列与已访问集合
    QQueue<QPoint> queue;
    QSet<QPoint> visited;
    queue.enqueue(startPos);
    visited.insert(startPos);
    //横板4向遍历：左右、上下（模拟跳跃）
    QList<QPoint> dirs={{-1,0},{1,0},{0,-1},{0,1}};
    while(!queue.isEmpty()){
        QPoint cur=queue.dequeue();
        //抵达场景最右侧，通关校验成功
        if(cur.x()>=maxX-2)return true;
        for(auto d:dirs){
            QPoint next;
            next.setX(cur.x()+d.x());
            next.setY(cur.y()+d.y());
            if(visited.contains(next))continue;
            //网格存在实体=可站立
            if(gridMap.contains(next)){
                visited.insert(next);
                queue.enqueue(next);
            }
        }
    }
    //BFS走完仍没有到达终点，关卡不可通行
    return false;
}
