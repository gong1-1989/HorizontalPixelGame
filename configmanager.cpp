#include "configmanager.h"

ConfigManager* ConfigManager::m_instance=nullptr;

ConfigManager* ConfigManager::instance(){
    if(!m_instance) m_instance=new ConfigManager();
    return m_instance;
}

ConfigManager::ConfigManager() {
    SetDefault();
}

TileBehavior ConfigManager::StrToBehavior(const QString &s){
    if(s=="trap")return BEHAVIOR_TRAP;
    if(s=="move_h")return BEHAVIOR_MOVE_HORIZ;
    if(s=="move_v")return BEHAVIOR_MOVE_VERT;
    return BEHAVIOR_NORMAL;
}

ResID ConfigManager::strToResid(const QString&s){
    if(s=="groud") return RES_GROUND;
    if(s=="platform") return RES_PLATFORM;
    if(s=="trap") return RES_TRAP;
    return RES_WALL;
}

void ConfigManager::SetDefault(){
    physics.gravity=980.0f;
    physics.moveSpeed=280.0f;
    physics.jumpForce=420.0f;
    physics.doubleJumpForce=360.0f;
    player.hp=100;
    player.maxHp=100;
    player.attackDamage=10;
    player.attackCd=0.5f;
    player.animSpeed=8.0f;
    //待机0~1
    player.idleStartFrame=0;
    player.idleFrameCnt=2;
    //行走2~10
    player.walkStartFrame=2;
    player.walkFrameCnt=9;
    //跳跃11-14
    player.walkStartFrame=11;
    player.jumpFrameCnt=4;
    //攻击15~21
    player.attackStartFrame=15;
    player.attackFrameCnt=8;
    monster.hp=30;
    monster.maxHp=30;
    monster.speed=120.0f;
    monster.chaseRange=250.0f;
    monster.patrolRange=300.0f;
    monster.attackCd=1.0f;
    monster.damage=5;
    item.coinValue=10;
    item.healValue=20;
    item.dropRate=0.5f;
    level.worldWidth=2000;
    level.tiles.clear();
}

void ConfigManager::LoadConfig(const QString &path){
    QFile file(path);
    if(!file.open(QIODevice::ReadOnly)){
        SetDefault();
        return;
    }
    QByteArray data=file.readAll();
    QJsonDocument doc=QJsonDocument::fromJson(data);
    QJsonObject obj=doc.object();
    //物理属性
    auto phy=obj["physics"].toObject();
    physics.gravity=phy["gtavity"].toDouble(physics.gravity);
    physics.moveSpeed=phy["moveSpeed"].toDouble(physics.moveSpeed);
    physics.jumpForce=phy["jumpForce"].toDouble(physics.jumpForce);
    physics.doubleJumpForce=phy["doubleJumpForce"].toDouble(physics.doubleJumpForce);
    //玩家属性
    auto pl=obj["player"].toObject();
    player.hp=pl["hp"].toInt(player.hp);
    player.maxHp=pl["maxHp"].toInt(player.maxHp);
    player.attackDamage=pl["attackDamage"].toInt(player.attackDamage);
    player.attackCd=pl["attackCd"].toDouble(player.attackCd);
    player.animSpeed=pl["animSpeed"].toDouble(player.animSpeed);
    player.idleStartFrame=pl["idleStartFrame"].toInt(player.idleStartFrame);
    player.idleFrameCnt=pl["idleFrameCnt"].toInt(player.idleFrameCnt);
    player.walkStartFrame=pl["walkStartFrame"].toInt(player.walkStartFrame);
    player.walkFrameCnt=pl["walkFrameCnt"].toInt(player.walkFrameCnt);
    player.jumpStartFrame=pl["jumpStartFrame"].toInt(player.jumpStartFrame);
    player.jumpFrameCnt=pl["jumpFrameCnt"].toInt(player.jumpFrameCnt);
    player.attackStartFrame=pl["attackStartFrame"].toInt(player.attackStartFrame);
    player.attackFrameCnt=pl["attackFrameCnt"].toInt(player.attackFrameCnt);
    //怪物
    auto mo=obj["monster"].toObject();
    monster.hp=mo["hp"].toInt(monster.hp);
    monster.maxHp=mo["maxHp"].toInt(monster.maxHp);
    monster.speed=mo["speed"].toDouble( monster.speed);
    monster.chaseRange=mo["chaseRange"].toDouble( monster.chaseRange);
    monster.patrolRange=mo["patrolRange"].toDouble( monster.patrolRange);
    monster.attackCd=mo["attackCd"].toDouble( monster.attackCd);
    monster.damage=mo["damage"].toInt(monster.damage);
    //道具
    auto it=obj["item"].toObject();
    item.coinValue=it["coinValue"].toInt(item.coinValue);
    item.healValue=it["healValue"].toInt(item.healValue);
    item.dropRate=it["dropRate"].toDouble(item.dropRate);
    //关卡
    auto le=obj["level"].toObject();
    level.levelName=le["levelName"].toString(level.levelName);
    level.worldWidth=le["worldWidth"].toInt(level.worldWidth);
    //加载地块模板
    level.tiles.clear();
    auto tiles=le["tiles"].toArray();
    for(auto c:tiles){
        QJsonObject co=c.toObject();
        TileConfig lc;
        lc.type=co["type"].toString();
        lc.width=co["width"].toInt(0);
        lc.heigth=co["heigth"].toInt(0);
        lc.isSolid=co["isSolid"].toBool(true);
        lc.behavior=StrToBehavior(co["behavior"].toString("normal"));
        lc.moveSpeed=co["moveSpeed"].toDouble(80);
        lc.moveRange=co["moveRange"].toInt(100);
        lc.trapDamage=co["trapDamage"].toInt(10);
        auto posArr=co["pos"].toArray();
        for(auto p:posArr){
            QJsonObject po=p.toObject();
            TilePos tp;
            tp.x=po["x"].toInt();
            tp.y=po["y"].toInt();
            lc.pos.append(tp);
        }
        lc.resId=strToResid(lc.type);
        level.tiles.append(lc);
    }
}