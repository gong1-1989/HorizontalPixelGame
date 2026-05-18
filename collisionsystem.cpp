#include "collisionsystem.h"
#include "configmanager.h"
#include "gamemain.h"

bool CollisionSystem::CheckCollision(const QRectF &a, const QRectF &b)
{
    return a.intersects(b);
}
void CollisionSystem::ResolveCollision(Player *player, const QList<Tile *> tiles)
{
    QRectF playerRect(player->pos.x(), player->pos.y(), player->width, player->height);
    player->isGrounded = false;
    for (Tile *tile : tiles) {
        if (!tile->isSolid) continue;
        QRectF tileRect(tile->pos.x(), tile->pos.y(), tile->width, tile->height);
        if (CheckCollision(playerRect, tileRect)) {            
            //垂直碰撞（落地、头顶碰撞）
            float overlapTop = playerRect.bottom() - tileRect.top();
            float overlapBottom = tileRect.bottom() - playerRect.top();
            if (overlapTop < overlapBottom&& player->velY>=0) {
                player->pos.setY(tileRect.top() - player->height);
                player->velY = 0;
                player->isGrounded = true;
            } else if(overlapBottom<overlapBottom&&player->velY<0){
                player->pos.setY(tileRect.bottom());
                player->velY = 0;
            }
            //水平碰撞（左右卡墙）
            float overlapLeft = playerRect.right() - tileRect.left();
            float overlapRight = tileRect.right() - playerRect.left();
            if (overlapLeft < overlapRight&&player->velX>=0){
                player->pos.setX(tileRect.left() - player->width);
            }else if(overlapRight<overlapLeft&&player->velX<0){
                player->pos.setX(tileRect.right());
                player->velX=0;
            }
        }       
    }
}

void CollisionSystem::ResolveCollision(Monster *monster, const QList<Tile *> tiles){
    QRectF rect(monster->pos.x(),monster->pos.y(),monster->width,monster->height);
    for(Tile*t:tiles){
        if(!t->isSolid)continue;
        QRectF tRect(t->pos.x(),t->pos.y(),t->width,t->height);
        if(CheckCollision(rect,tRect)){
            monster->pos.setY(tRect.top()-monster->height);
            monster->velY=0;
        }
    }
}
void CollisionSystem::CheckPlayerAttack(Player *p, QList<Monster *> &mons){
    if(!p->isAttacking) return;
    auto& cfg=ConfigManager::instance()->player;
    auto& itemCfg=ConfigManager::instance()->item;
    QRectF attackRect(p->pos.x()+32,p->pos.y(),32,32);
    for(auto it=mons.begin();it!=mons.end();){
        QRectF mRect((*it)->pos.x(),(*it)->pos.y(),32,32);
        if(CheckCollision(attackRect,mRect)){
            (*it)->hp-=cfg.attackDamage;
            if((*it)->hp<=0){
                //按照配置概率掉落
                if(QRandomGenerator::global()->generateDouble()<itemCfg.dropRate){
                    Item* drop=new Item();
                    if(QRandomGenerator::global()->bounded(0,2)==0){
                        drop->type=ITEM_COIN;
                        drop->resId=RES_ITEM_COIN;
                    }else{
                        drop->type=ITEM_HP;
                        drop->resId=RES_ITEM_HP;
                    }
                    drop->pos=(*it)->pos;
                    gamemain::instance()->AddItem(drop);
                }
                delete *it;
                it=mons.erase(it);
                continue;
            }
        }
        ++it;
    }
}

void CollisionSystem::CheckMonsterAttack(Player *p, QList<Monster *> &mons){
    auto& cfg=ConfigManager::instance()->monster;
    for (Monster* m:mons){
        if(m->attackTimer<cfg.attackCd) continue;
        QRectF pRect(p->pos.x(),p->pos.y(),32,32);
        QRectF mRect(m->pos.x(),m->pos.y(),32,32);
        if(CheckCollision(pRect,mRect)){
            p->hp-=cfg.damage;
            m->attackTimer=0;
        }
    }
}

void CollisionSystem::CheckItemPick(Player *p, QList<Item *> &items, int &coin){
    auto& cfg=ConfigManager::instance()->item;
    QRectF pRect(p->pos.x(),p->pos.y(),p->width,p->height);
    for(auto it=items.begin();it!=items.end();){
        QRectF iRect((*it)->pos.x(),(*it)->pos.y(),(*it)->width,(*it)->height);
        if(CheckCollision(pRect,iRect)){
            if((*it)->type==ITEM_COIN) coin+=cfg.coinValue;
            else if((*it)->type==ITEM_HP) p->hp=qMin(p->hp+cfg.healValue,p->maxHp);
            delete *it;
            it=items.erase(it);
            continue;
        }
        ++it;
    }
}

bool CollisionSystem::CheckPortalEnter(Player *p, Portal *portal){
    if(!p->isGrounded) return false;
    QRectF pRect(p->pos.x(),p->pos.y(),p->width,p->height);
    QRectF poRect(portal->pos.x(),portal->pos.y(),portal->width,portal->height);
    return CheckCollision(pRect,poRect);
}