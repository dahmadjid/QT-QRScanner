#include <QApplication>

#include "mainwindow.h"
#include "Logger.h"
#include <QThread>
#include "Capture.h"
#include <memory>
#include <QTimer>
#include "DetectedQRDialog.h"
#include "Dropdown.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Logger logger;
    auto w = std::make_unique<MainWindow>();
    auto attendance_dialog = std::make_unique<DetectedQRDialog>();
    auto drop = new Dropdown(w.get());
    auto thread = new QThread();  // They delete themselves later
    auto capture = new Capture(); 


    auto mat = std::make_shared<cv::Mat>();


    QTimer timer_refresh_rate;


    QThread::currentThread()->setObjectName("Main Thread");
    thread->setObjectName("Capture Thread");


    w->m_dialog = attendance_dialog.get();

    w->image = mat;
    capture->image = mat;
    
    capture->moveToThread(thread);
    QObject::connect(thread, &QThread::started, capture, &Capture::run, Qt::QueuedConnection);
    QObject::connect(capture, &Capture::finished, thread, &QThread::quit, Qt::QueuedConnection);
    QObject::connect(capture, &Capture::updated, w.get(), &MainWindow::updateFrame, Qt::QueuedConnection);
    QObject::connect(capture, &Capture::finished, capture, &Capture::deleteLater, Qt::DirectConnection);
    QObject::connect(thread, &QThread::finished, thread, &QThread::deleteLater, Qt::DirectConnection);

    QObject::connect(&timer_refresh_rate, &QTimer::timeout, capture, &Capture::getFrame, Qt::QueuedConnection);
    QObject::connect(w.get(), &MainWindow::updated, capture, &Capture::setSync, Qt::QueuedConnection);
    QObject::connect(w.get(), &MainWindow::detectedQR, attendance_dialog.get(), &DetectedQRDialog::display, Qt::DirectConnection);
    bool shown = false;
    QObject::connect(w.get(), &MainWindow::menu_clicked, [&]{if(shown){ drop->hide(); shown = false;} else{drop->show(); shown = true;}});

    thread->start();
    timer_refresh_rate.start(16);
    drop->move(std::move(QPoint(1563, 200)));
    w->show();
    drop->hide();

    return a.exec();
}
