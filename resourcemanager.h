#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H
//美术资源管理器（预留加载图片）
#include <QMap>
#include <QPixmap>
#include <QString>
//统一素材ID，后期绑定PNG图片
enum ResID {
    //玩家
    RES_PLAYER_IDLE,
    RES_PLAYER_RUN,
    //场景
    RES_GROUND,
    RES_PLATFORM,
    RES_PROTAL,
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
    //获取素材
    QPixmap GetPixmap(ResID id);

private:
    resourcemanager();
    static resourcemanager *m_instance;
    QMap<ResID, QPixmap> m_pixmapCache;
};

#endif // RESOURCEMANAGER_H
