#include <QApplication>

#include "mainwindow.h"
#include "Logger.h"
#include <QThread>
#include "Capture.h"
#include <memory>
#include <QTimer>
#include <QMutex>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Logger logger;

    std::shared_ptr<cv::Mat> mat = std::make_shared<cv::Mat>();
    std::shared_ptr<QMutex> image_mutex = std::make_shared<QMutex>();

    QThread::currentThread()->setObjectName("Main Thread");
    QThread* thread = new QThread();
    thread->setObjectName("Capture Thread");
    Capture* capture = new Capture();

    MainWindow w;

    w.image = mat;
    capture->image = mat;

    w.image_mutex = image_mutex;
    capture->image_mutex = image_mutex;


    capture->moveToThread(thread);
    QObject::connect(thread, &QThread::started, capture, &Capture::run, Qt::QueuedConnection);
    QObject::connect(capture, &Capture::finished, thread, &QThread::quit, Qt::QueuedConnection);
    QObject::connect(capture, &Capture::finished, capture, &Capture::deleteLater, Qt::QueuedConnection);
    QObject::connect(thread, &QThread::finished, thread, &QThread::deleteLater, Qt::QueuedConnection);
    QObject::connect(capture, &Capture::updated, &w, &MainWindow::updateFrame, Qt::QueuedConnection);
    QTimer timer = QTimer();
    QObject::connect(&timer, &QTimer::timeout, capture, &Capture::getFrame, Qt::QueuedConnection);
    QObject::connect(&w, &MainWindow::updated, capture, &Capture::setSync, Qt::QueuedConnection);

    thread->start();
    timer.start(16);

    w.show();
    
    return a.exec();
}
