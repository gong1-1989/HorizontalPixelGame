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

enum TileBehavior{
    BEHAVIOR_NORMAL,
    BEHAVIOR_TRAP,          //陷阱扣血
    BEHAVIOR_MOVE_HORIZ,    //水平移动平台
    BEHAVIOR_MOVE_VERT      //垂直移动平台
};

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
    int maxJumpHeight;  //全局最大可跳跃高度
};
struct TileConfig{
    QString type;
    int width;
    int heigth;
    bool isSolid;
    ResID resId;
    TileBehavior behavior;
    //移动平台参数
    float moveSpeed;
    int moveRange;
    //陷阱伤害参数
    int trapDamage;
};

struct LevelChunk{
    QString chunkName;
    int weight;                 //随机抽取权重
    int fixedBaseY;             //保底地面高度
    int maxPlatformHeight;      //平台最大高度，限制跳跃可达
    bool isBossChunk;           //是否BOSS专属平台
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
    TileBehavior StrToBehavior(const QString&s);
};

#endif // CONFIGMANAGER_H
