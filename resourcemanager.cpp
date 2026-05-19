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
    LoadSpriteSheet(RES_PLAYER_IDLE,":/Image/Resource/Image/RES_PLAYER_IDLE.png",30);
    LoadSpriteSheet(RES_GROUND,":/Image/Resource/Image/RES_GROUND.png",1);
    LoadSpriteSheet(RES_PLATFORM,":/Image/Resource/Image/RES_PLATFORM.png",1);
    LoadSpriteSheet(RES_WALL,":/Image/Resource/Image/RES_WALL.png",1);
    LoadSpriteSheet(RES_TRAP,":/Image/Resource/Image/RES_TRAP.png",1);
    LoadSpriteSheet(RES_PROTAL,":/Image/Resource/Image/RES_PROTAL.gif",1);
    LoadSpriteSheet(RES_MONSTER_NORMAL,":/Image/Resource/Image/RES_MONSTER_NORMAL.png",1);
    LoadSpriteSheet(RES_ITEM_COIN,"",1);
    LoadSpriteSheet(RES_ITEM_HP,":/Image/Resource/Image/RES_ITEM_HP.png",1);
    LoadSpriteSheet(RES_UI_HPBAR,"",1);
}

void resourcemanager::LoadSpriteSheet(ResID id,const QString&path, int frameCount){
    QImage img(path);
    if(img.isNull()) return;
    int frameW=img.width()/frameCount;
    int frameH=img.height();
    QList<QPixmap> frames;
    for(int i=0;i<frameCount;i++){
        QRect rect(i*frameW,0,frameW,frameH);
        frames.append(QPixmap::fromImage(img.copy(rect)));
    }
    m_spriteFrames[id]=frames;
}
QPixmap resourcemanager::GetPixmap(ResID id,int frame){
    if(!m_spriteFrames.contains(id)) return QPixmap();
    auto& list=m_spriteFrames[id];
    int idx=frame%list.size();
    return list[idx];
}

QSize resourcemanager::GetSize(ResID id, int frame){
    if(!m_spriteFrames.contains(id)) return QSize(32,32);
    auto&list=m_spriteFrames[id];
    int idx=frame%list.size();
    return list[idx].size();
}