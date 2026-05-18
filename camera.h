#ifndef CAMERA_H
#define CAMERA_H
//平滑摄像机（横版卷轴）
#include <QPointF>
#include "entity.h"

class camera
{
public:
    camera();
    //设置跟随目标
    void SetFollowTarget(entity* target);
    //平滑更新摄像机位置
    void Update(float deltaTime);
    //获取摄像机偏移
    QPointF GetOffset();
private:
    QPointF m_offset;
    entity* m_followTarget;
    float m_smoothFactor;   //平滑系数
};

#endif // CAMERA_H
