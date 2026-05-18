#include "maingamewidget.h"

maingamewidget::maingamewidget(QWidget *parent)
    : QWidget(parent)
    , m_deltaTime(0.016f)
{
    setFixedSize(800, 600);
    setFocusPolicy(Qt::StrongFocus);
    //60帧游戏循环
    connect(&m_gameTimer, &QTimer::timeout, this, [=] {
        gamemain::instance()->Update(m_deltaTime);
        update();
    });
    m_gameTimer.start(16);
    //初始化游戏
    gamemain::instance()->Init();
}

void maingamewidget::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);
    QPainter painter(this);
    painter.fillRect(rect(), Qt::darkGray);
    gamemain::instance()->Draw(&painter);
}

void maingamewidget::keyPressEvent(QKeyEvent *event)
{
    //后续绑定玩家移动按键
    Player *p = gamemain::instance()->GetPlayer();

    switch (event->key()) {
    case Qt::Key_A:
    case Qt::Key_Left:
        p->keyLeft = true;
        break;
    case Qt::Key_D:
    case Qt::Key_Right:
        p->keyRight = true;
    case Qt::Key_W:
    case Qt::Key_Space:
        p->keyJump = true;
        break;
    case Qt::Key_J:
        p->keyAttack=true;
        break;
    }
}
void maingamewidget::keyReleaseEvent(QKeyEvent *event)
{
    Player *p = gamemain::instance()->GetPlayer();
    switch (event->key()) {
    case Qt::Key_A:
    case Qt::Key_Left:
        p->keyLeft = false;
        break;
    case Qt::Key_D:
    case Qt::Key_Right:
        p->keyRight = false;
    case Qt::Key_W:
    case Qt::Key_Space:
        p->keyJump = false;
        break;
    case Qt::Key_J:
        p->keyAttack=false;
        break;
    }
}