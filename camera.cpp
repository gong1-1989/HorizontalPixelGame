#include "camera.h"

camera::camera()
    : m_followTarget(nullptr)
    , m_smoothFactor(0.08f)
{
    m_offset = QPointF(0, 0);
}

void camera::SetFollowTarget(entity *target)
{
    m_followTarget = target;
}

void camera::Update(float deltaTime)
{
    if (!m_followTarget)
        return;
    //平滑插值跟随，消除抖动,屏幕居中
    float targetX = m_followTarget->pos.x() - 400;
    float targetY = m_followTarget->pos.y() - 300;
    m_offset.rx() += (targetX - m_offset.x()) * m_smoothFactor;
    m_offset.ry() += (targetY - m_offset.y()) * m_smoothFactor;
}

QPointF camera::GetOffset()
{
    return m_offset;
}