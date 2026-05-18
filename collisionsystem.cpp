#include "collisionsystem.h"

bool CollisionSystem::CheckCollision(const QRectF& a,const QRectF& b){
    return a.intersects(b);
}
void CollisionSystem::ResolveCollision(Player* player,const QList<Tile*> tiles){
    QRectF playerRect(player->pos.x(),player->pos.y(),player->width,player->height);
    player->isGrounded=false;
    for(Tile*tile:tiles){
        if(!tile->isSolid) continue;
        QRectF tileRect(tile->pos.x(),tile->pos.y(),tile->width,tile->height);
        if(CheckCollision(playerRect,tileRect)){
            //垂直碰撞（落地、头顶碰撞）
            float overlapTop=playerRect.bottom()-tileRect.top();
            float overlapBottom=tileRect.bottom()-playerRect.top();
            if(overlapTop<overlapBottom){
                player->pos.setY(tileRect.top()-player->height);
                player->velY=0;
                player->isGrounded=true;
            }else{
                player->pos.setY(tileRect.bottom());
                player->velY=0;
            }
            //水平碰撞（左右卡墙）
            float overlapLeft=playerRect.right()-tileRect.left();
            float overlapRight=tileRect.right()-playerRect.left();
            if(overlapLeft<overlapRight) player->pos.setX(tileRect.left()-player->width);
            else player->pos.setX(tileRect.right());

        }
    }
}