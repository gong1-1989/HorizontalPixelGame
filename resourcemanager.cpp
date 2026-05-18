#include "resourcemanager.h"

resourcemanager *resourcemanager::m_instance = nullptr;

resourcemanager *resourcemanager::instance()
{
    if (!m_instance)
        m_instance = new resourcemanager();
    return m_instance;
}
resourcemanager::resourcemanager() {}
void resourcemanager::LoadAllResources()
{
    //================================
    //【美术预留】后期直接修改路径即可加载PNG
    //================================
    m_pixmapCache[RES_PLAYER_IDLE] = QPixmap(":/Image/Resource/Image/RES_PLAYER_IDLE.png");
    m_pixmapCache[RES_PLAYER_RUN] = QPixmap("Resources/Image/player_run.png");
    m_pixmapCache[RES_GROUND] = QPixmap(":/Image/Resource/Image/RES_GROUND.png");
    m_pixmapCache[RES_PLATFORM] = QPixmap(":/Image/Resource/Image/RES_PLATFORM.png");
    m_pixmapCache[RES_PROTAL]=QPixmap("");
    m_pixmapCache[RES_MONSTER_NORMAL] = QPixmap(":/Image/Resource/Image/RES_MONSTER_NORMAL.png");
    m_pixmapCache[RES_ITEM_COIN] = QPixmap("Resources/Image/coin.png");
    m_pixmapCache[RES_ITEM_HP] = QPixmap("Resources/Image/hp.png");
    m_pixmapCache[RES_UI_HPBAR] = QPixmap("Resources/Image/hpbar.png");
}
QPixmap resourcemanager::GetPixmap(ResID id)
{
    return m_pixmapCache.value(id);
}