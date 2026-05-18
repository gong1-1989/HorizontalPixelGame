#ifndef CONFIGMANAGER_H
#define CONFIGMANAGER_H
//配置读取类
#include <QJsonObject>
#include <QJsonDocument>
#include <QFile>
#include <QString>
#include <QList>
#include <QJsonArray>
#include "resourcemanager.h"

struct PhysicsConfig{
    float gravity;
    float moveSpeed;
    float jumpForce;
    float doubleJumpForce;
};

struct PlayerConfig{
    int hp;
    int maxHp;
    int attackDamage;
};

struct MonsterConfig{
    int hp;
    int maxHp;
    float speed;
    float chaseRange;
    float patrolRange;
    float attackCd;
    int damage;
};

struct ItemConfig{
    int coinValue;
    int healValue;
    float dropRate; //怪物死亡掉落概率0-1
};

struct LevelConfig{
    int baseLength;     //基础关卡长度
    int lengthAdd;      //每关增加长度
    int baseMonsterNum; //基础怪物数量
    int monsterAdd;     //每关增加怪物数量
    int chunkWidth;     //单个地块总宽度
};
struct TileConfig{
    QString type;
    int width;
    int heigth;
    bool isSolid;
    ResID resId;
};

struct LevelChunk{
    QString chunkName;
    int weight;                 //随机抽取权重
    int fixedBaseY;             //保底地面高度
    QList<TileConfig> tiles;    //该地块包含的所有瓦片
};

class ConfigManager
{
public:
    static ConfigManager* instance();
    void LoadConfig(const QString&path=":/Config/Resource/Config/game_config.json");
    PhysicsConfig physics;
    PlayerConfig player;
    MonsterConfig monster;
    ItemConfig item;
    LevelConfig level;
    QList<LevelChunk> chunkList;
private:
    ConfigManager();
    static ConfigManager* m_instance;
    void SetDefault();
};

#endif // CONFIGMANAGER_H
