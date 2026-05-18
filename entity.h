#ifndef ENTITY_H
#define ENTITY_H
//实体基类（玩家、怪物、道具父类）
#include <QPainter>
#include <QPointF>
#include "resourcemanager.h"

class entity
{
public:
    entity();
    virtual ~entity() = default;
    //位置、大小
    QPointF pos;
    int width;
    int height;
    ResID resId; //绑定美术素材ID
    //物理属性
    float velX;
    float velY;
    bool isGrounded;
    //逻辑更新
    virtual void Update(float deltaTime);
    //渲染
    virtual void Draw(QPainter *painter);
};

#endif // ENTITY_H
