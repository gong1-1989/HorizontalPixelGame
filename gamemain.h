#ifndef GAMEMAIN_H
#define GAMEMAIN_H
//游戏主逻辑控制器
#include <QList>
#include "camera.h"
#include "collisionsystem.h"
#include "levelgenerator.h"
#include "player.h"
#include "monster.h"
#include "tile.h"
#include "item.h"
#include "portal.h"

class gamemain
{
public:
    static gamemain *instance();
    void Init();
    void Update(float deltaTime);
    void Draw(QPainter *painter);
    //对外设置玩家按键
    Player *GetPlayer();
    void AddItem(Item* item);

private:
    gamemain();
    static gamemain *m_instance;
    void NextLevel();
    void ResetGame();
    camera m_camera;
    Player m_player;
    QList<Monster*> m_monsterList;
    QList<Tile *> m_TileList; //所有场景实体
    QList<Item*> m_itemList;
    Portal m_portal;
    int m_currentLevel;
    int m_coin;
};

#endif // GAMEMAIN_H
