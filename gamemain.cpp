#include "gamemain.h"
#include "configmanager.h"
#include <QRandomGenerator>

gamemain *gamemain::m_instance = nullptr;
gamemain *gamemain::instance()
{
    if (!m_instance)
        m_instance = new gamemain();
    return m_instance;
}

gamemain::gamemain() {}

void gamemain::Init()
{
    //加载所有美术资源
    resourcemanager::instance()->LoadAllResources();
    NextLevel();
    //初始化玩家
    m_player.pos = QPointF(100, 300);
    //摄像机跟随玩家
    m_camera.SetFollowTarget(&m_player);
    m_currentLevel=1;
    m_coin=0;
}
void gamemain::NextLevel(){
    //清空旧场景
    for(auto t:m_TileList) delete t;
    for(auto m:m_monsterList)delete m;
    for(auto i:m_itemList)delete i;
    m_TileList.clear();
    m_monsterList.clear();
    m_itemList.clear();
    //生产新关卡
    auto& cfg=ConfigManager::instance()->level;
    int len=cfg.baseLength+m_currentLevel*cfg.lengthAdd;
    m_TileList=LevelGenerator::GenerateLevel(len);
    //生成怪物
    int monsterCount=cfg.baseMonsterNum+m_currentLevel*cfg.monsterAdd;
    for(int i=0;i<monsterCount;i++){
        Monster* m=new Monster();
        int x=QRandomGenerator::global()->bounded(400,len-200);
        m->pos=QPointF(x,300);
        m->patrolStartX=x-100;
        m->patrolEndX=x+100;
        m_monsterList.append(m);
    }
    //生成传送门
    m_portal.pos=QPointF(len-100,386);
    m_portal.resId=RES_PROTAL;
}

void gamemain::ResetGame()
{
    m_currentLevel=1;
    m_coin=0;
    m_player.hp=m_player.maxHp;
    NextLevel();
    m_player.pos=QPoint(100,300);
}
void gamemain::Update(float deltaTime)
{
    m_camera.Update(deltaTime);
    m_player.Update(deltaTime);
    //执行碰撞检测和位置修正
    CollisionSystem::ResolveCollision(&m_player, m_TileList);
    //更新怪物AI
    for(Monster* m:m_monsterList) {
        m->Update(deltaTime,&m_player);
        CollisionSystem::ResolveCollision(m,m_TileList);
    }
    CollisionSystem::CheckPlayerAttack(&m_player,m_monsterList);
    CollisionSystem::CheckMonsterAttack(&m_player,m_monsterList);
    CollisionSystem::CheckItemPick(&m_player,m_itemList,m_coin);
    //进入传送门
    static float portalTime=0;
    portalTime+=deltaTime;
    if(portalTime>1.0f&&CollisionSystem::CheckPortalEnter(&m_player,&m_portal)){
        m_currentLevel++;
        NextLevel();
        m_player.pos=QPointF(100,300);
        portalTime=0;
    }
    //玩家死亡
    if(m_player.hp<=0) ResetGame();
    //更新移动平台和陷阱
    for(Tile*t:m_TileList) t->Update(deltaTime);
}

void gamemain::Draw(QPainter *painter)
{
    //应用摄像机偏移
    painter->translate(-m_camera.GetOffset().x(), -m_camera.GetOffset().y());
    //渲染场景瓦片
    for (Tile *t : m_TileList) t->Draw(painter);
    //渲染终点传送门
    m_portal.Draw(painter);
    //渲染怪物
    for(Monster*m : m_monsterList) m->Draw(painter);
    //渲染玩家
    m_player.Draw(painter);
    //渲染道具
    for(Item* i:m_itemList) i->Draw(painter);
    //绘制UI（固定在屏幕左上角）
    painter->resetTransform();
    painter->setPen(Qt::white);
    painter->setFont(QFont("Arial",12));
    painter->drawText(10,20,QString("关卡：%1").arg(m_currentLevel));
    painter->drawText(10,40,QString("金币：%1").arg(m_coin));
    painter->drawText(10,60,QString("生命：%1/%2").arg(m_player.hp).arg(m_player.maxHp));
}
Player *gamemain::GetPlayer()
{
    return &m_player;
}
void gamemain::AddItem(Item *item){
    m_itemList.append(item);
}