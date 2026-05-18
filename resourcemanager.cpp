#include "resourcemanager.h"

resourcemanager* resourcemanager::m_instance=nullptr;

resourcemanager*resourcemanager::instance(){
    if(!m_instance)m_instance=new resourcemanager();
    return m_instance;
}
resourcemanager::resourcemanager() {}
void resourcemanager::LoadAllResources(){
    //================================
    //【美术预留】后期直接修改路径即可加载PNG
    //================================
    m_pixmapCache[RES_PLAYER_IDLE]=QPixmap("Resources/Image/player_idle.png");
    m_pixmapCache[RES_PLAYER_RUN]=QPixmap("Resources/Image/player_run.png");
    m_pixmapCache[RES_GROUND]=QPixmap("Resources/Image/ground.png");
    m_pixmapCache[RES_PLATFORM]=QPixmap("Resources/Image/platform.png");
    m_pixmapCache[RES_MONSTER_NORMAL]=QPixmap("Resources/Image/monster.png");
    m_pixmapCache[RES_ITEM_COIN]=QPixmap("Resources/Image/coin.png");
    m_pixmapCache[RES_ITEM_HP]=QPixmap("Resources/Image/hp.png");
    m_pixmapCache[RES_UI_HPBAR]=QPixmap("Resources/Image/hpbar.png");
}
QPixmap resourcemanager::GetPixmap(ResID id){
    return m_pixmapCache.value(id);
}