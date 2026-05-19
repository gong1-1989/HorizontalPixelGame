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
    float attackCd;
    //动画配置：同一张精灵图的帧范围
    float animSpeed;
    int idleStartFrame;
    int idleFrameCnt;
    int walkStartFrame;
    int walkFrameCnt;
    int jumpStartFrame;
    int jumpFrameCnt;
    int attackStartFrame;
    int attackFrameCnt;
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

struct TilePos{
    int x;
    int y;
};

struct TileConfig{
    QString type;
    QList<TilePos> pos;
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

struct LevelConfig{
    QString levelName;
    int worldWidth;
    QList<TileConfig> tiles;
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
private:
    ConfigManager();
    static ConfigManager* m_instance;
    void SetDefault();
    TileBehavior StrToBehavior(const QString&s);
    ResID strToResid(const QString&s);
};

#endif // CONFIGMANAGER_H
