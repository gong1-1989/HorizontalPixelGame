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

void ConfigManager::SetDefault(){
    physics.gravity=980.0f;
    physics.moveSpeed=280.0f;
    physics.jumpForce=420.0f;
    physics.doubleJumpForce=360.0f;
    player.hp=100;
    player.maxHp=100;
    player.attackDamage=10;
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
    level.baseLength=2000;
    level.lengthAdd=200;
    level.baseMonsterNum=5;
    level.monsterAdd=1;
    level.chunkWidth=384;
    level.maxJumpHeight=160;
    //默认地块
    chunkList.clear();
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
    level.baseLength=le["baseLength"].toInt(level.baseLength);
    level.lengthAdd=le["lengthAdd"].toInt(level.lengthAdd);
    level.baseMonsterNum=le["baseMonsterNum"].toInt(level.baseMonsterNum);
    level.monsterAdd=le["monsterAdd"].toInt(level.monsterAdd);
    level.chunkWidth=le["chunkWidth"].toInt(level.chunkWidth);
    level.maxJumpHeight=le["maxJumpHeight"].toInt(level.maxJumpHeight);
    //加载地块模板
    chunkList.clear();
    auto chunks=obj["chunks"].toArray();
    for(auto c:chunks){
        QJsonObject co=c.toObject();
        LevelChunk lc;
        lc.chunkName=co["chunkName"].toString();
        lc.weight=co["weight"].toInt(1);
        lc.fixedBaseY=co["fixedBaseY"].toInt(450);
        lc.maxPlatformHeight=co["maxPlatformHeight"].toInt(level.maxJumpHeight);
        lc.isBossChunk=co["isBossChunk"].toBool(false);
        auto tiles=co["tiles"].toArray();
        for(auto t:tiles){
            QJsonObject to=t.toObject();
            TileConfig tc;
            tc.type=to["type"].toString();
            tc.width=to["width"].toInt();
            tc.heigth=to["heigth"].toInt();
            tc.isSolid=to["isSolid"].toBool();
            tc.resId=(ResID)to["resId"].toInt(0);
            tc.behavior=StrToBehavior(to["behaviot"].toString("normal"));
            tc.moveSpeed=to["moveSpeed"].toDouble(80);
            tc.moveRange=to["moveRange"].toInt(100);
            tc.trapDamage=to["trapDamage"].toInt(10);
            lc.tiles.append(tc);
        }
        chunkList.append(lc);

    }
}