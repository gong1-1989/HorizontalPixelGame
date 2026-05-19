#include "entity.h"

entity::entity()
    : pos(0, 0)
    , width(0)
    , heigth(0)
    , resId(RES_GROUND)
    , frame(0)
    , velX(0)
    , velY(0)
    , isGrounded(false)
{}

void entity::Update(float deltaTime)
{
    //基类空实现，子类重写
}
void entity::Draw(QPainter *painter)
{
    //统一渲染美术图片
    painter->drawPixmap(pos.x(), pos.y(), resourcemanager::instance()->GetPixmap(resId,frame));
}
