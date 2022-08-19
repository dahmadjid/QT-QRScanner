
#include "mainwindow.h"
#include <QApplication>
#include "Logger.h"
#include <QThread>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Logger logger;
    QThread::currentThread()->setObjectName("Main Thread");
    
    MainWindow w;

    qDebug() << "Debug";
    qInfo() << "Info";
    qWarning() << "Warning";
    qCritical() << "Critical";
    qFatal("Fatal");

    w.show();
    
    return a.exec();
}
