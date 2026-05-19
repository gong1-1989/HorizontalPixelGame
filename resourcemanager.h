#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H
//美术资源管理器（预留加载图片）
#include <QMap>
#include <QPixmap>
#include <QString>
#include <QSize>

//统一素材ID，后期绑定PNG图片
enum ResID {
    //玩家
    RES_PLAYER_IDLE,
    //场景
    RES_GROUND,     //地面
    RES_PLATFORM,   //平台
    RES_WALL,       //墙体
    RES_TRAP,       //陷阱
    RES_PROTAL,     //传送门
    //怪物
    RES_MONSTER_NORMAL,
    //道具
    RES_ITEM_COIN,
    RES_ITEM_HP,
    //UI
    RES_UI_HPBAR
};

class resourcemanager
{
public:
    static resourcemanager *instance();
    //预加载所有图片（后期填入真实路径）
    void LoadAllResources();
    void LoadSpriteSheet(ResID id,const QString&path,int frameCount);
    //获取素材
    QPixmap GetPixmap(ResID id,int frame=0);
    QSize GetSize(ResID id,int frame=0);

private:
    resourcemanager();
    static resourcemanager *m_instance;
    QMap<ResID, QPixmap> m_pixmapCache;
    QMap<ResID,QList<QPixmap>> m_spriteFrames;
};

#endif // RESOURCEMANAGER_H
