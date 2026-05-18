#ifndef GAMEMAIN_H
#define GAMEMAIN_H
//游戏主逻辑控制器
#include <QList>
#include "player.h"
#include "camera.h"
#include "tile.h"
#include "levelgenerator.h"
#include "collisionsystem.h"

class gamemain
{
public:
    static gamemain*instance();
    void Init();
    void Update(float deltaTime);
    void Draw(QPainter* painter);
    //对外设置玩家按键
    Player*GetPlayer();
private:
    gamemain();
    static gamemain* m_instance;
    camera m_camera;
    Player m_player;
    QList<Tile*> m_TileList;    //所有场景实体
};

#endif // GAMEMAIN_H
