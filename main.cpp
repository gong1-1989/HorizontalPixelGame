#include "mainwindow.h"
#include "configmanager.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ConfigManager::instance()->LoadConfig();
    MainWindow w;
    w.show();
    return QApplication::exec();
}
