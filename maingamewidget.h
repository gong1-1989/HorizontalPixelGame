#ifndef MAINGAMEWIDGET_H
#define MAINGAMEWIDGET_H
//主渲染窗口
#include <QWidget>
#include <QObject>
#include <QPainter>
#include <QPaintEvent>
#include <QKeyEvent>
#include <QTimer>
#include "gamemain.h"

class maingamewidget : public QWidget
{
    Q_OBJECT
public:
    explicit maingamewidget(QWidget *parent=nullptr);
protected:
    void paintEvent(QPaintEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;
private:
    QTimer m_gameTimer;
    float m_deltaTime;
};

#endif // MAINGAMEWIDGET_H
