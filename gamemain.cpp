#include "gamemain.h"

gamemain* gamemain::m_instance=nullptr;
gamemain* gamemain::instance() {
    if(!m_instance) m_instance=new gamemain();
    return m_instance;
}

gamemain::gamemain(){}

void gamemain::Init(){
    //加载所有美术资源
    resourcemanager::instance()->LoadAllResources();
    //生成长度2000像素的横板关卡
    m_TileList=LevelGenerator::GenerateLevel(2000);
    //初始化玩家
    m_player.pos=QPointF(100,200);
    //摄像机跟随玩家
    m_camera.SetFollowTarget(&m_player);
}

void gamemain::Update(float deltaTime){
    m_camera.Update(deltaTime);
    m_player.Update(deltaTime);
    //执行碰撞检测和位置修正
    CollisionSystem::ResolveCollision(&m_player,m_TileList);
}

void gamemain::Draw(QPainter *painter){
    //应用摄像机偏移
    painter->translate(-m_camera.GetOffset().x(),-m_camera.GetOffset().y());
    //渲染场景瓦片
    for(Tile*t:m_TileList) t->Draw(painter);
    //渲染玩家
    m_player.Draw(painter);
}
Player* gamemain::GetPlayer(){
    return &m_player;
}