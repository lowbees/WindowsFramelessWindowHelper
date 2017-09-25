#include "mainwindow.h"
#include <QApplication>
#include <QtQml>
#include "FramelessHelper/framelesswindowhelper.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    qmlRegisterType<FramelessWindowHelper>("FramelessWindowHelper", 1, 0, "FramelessWindowHelper");

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;
    return a.exec();
}
