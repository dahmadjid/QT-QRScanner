#include "mainwindow.h"
#include <QDebug>
#include "./ui_mainwindow.h"
#include <QMovie>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , burger_animation_movie(QMovie(this))
    
{
    ui->setupUi(this);
// burgir button animation -----------------------------------------------------------------------------------------------------------
    burger_animation_movie.setFileName(CWD"/resources/burger.gif");
    burger_animation_movie.start();
    burger_animation_movie.setPaused(true);

    // jumps to the initial state, apparently i need to go frame by frame.
    // jumptoframe(14) directly doesnt work. investigate later
    for (int i = 0; i<=14; i++)
    {
        burger_animation_movie.jumpToFrame(i);
    }

    ui->menu_button->setIcon(burger_animation_movie.currentPixmap());
    ui->menu_button->setIconSize({120,120});
    ui->menu_button->setFlat(true);
    ui->menu_button->setStyleSheet("QPushButton { background-color: transparent }");
    ui->menu_button->setStyleSheet("QPushButton:pressed { background-color: rgba(0, 0, 0, 0);border-style: inset;border-width: 0px;}");
    QObject::connect(&burger_animation_movie, &QMovie::frameChanged, [=]{
        ui->menu_button->setIcon(burger_animation_movie.currentPixmap());
        ui->menu_button->setIconSize({120,120});
        if (burger_animation_movie.currentFrameNumber() == 25)
        {
            burger_animation_movie.setPaused(true);
        }
        else if (burger_animation_movie.currentFrameNumber() == 13)
        {
            burger_animation_movie.setPaused(true);
        }
    });

    QObject::connect(ui->menu_button, &QPushButton::clicked, [=]{

        burger_animation_movie.setPaused(false);
    });

// Logos -------------------------------------------------------------------------------------------------------------------------------
    QPixmap bg(CWD"/resources/background.png");
    ui->background->setPixmap(bg.scaled(ui->background->width(), ui->background->height(), Qt::KeepAspectRatio));
    
    QPixmap wameedh_logo(CWD"/resources/wameedh_logo.png");
    ui->logo_center->setPixmap(wameedh_logo.scaled(ui->logo_center->width(), ui->logo_center->height(), Qt::KeepAspectRatio));
    ui->logo_center->setStyleSheet("QLabel { background-color: transparent }");

    QPixmap event_logo(CWD"/resources/schlumberger.png");
    ui->logo_right->setPixmap(event_logo.scaled(ui->logo_right->width(), ui->logo_right->height(), Qt::KeepAspectRatio));
    ui->logo_right->setStyleSheet("QLabel { background-color: transparent }");

    QPixmap sponsor_logo(CWD"/resources/deadline.png");
    ui->logo_left->setPixmap(sponsor_logo.scaled(ui->logo_left->width(), ui->logo_left->height(), Qt::KeepAspectRatio));
    ui->logo_left->setStyleSheet("QLabel { background-color: transparent }");

    QPixmap scan_img(CWD"/resources/scan_text.png");
    ui->scan_text->setPixmap(scan_img.scaled(ui->scan_text->width(), ui->scan_text->height(), Qt::KeepAspectRatio));
    ui->scan_text->setStyleSheet("QLabel { background-color: transparent }");



    ui->camera->setStyleSheet("QLabel { background-color: transparent }");


    
}

MainWindow::~MainWindow()
{
    delete ui;

}

void MainWindow::updateFrame()
{   
    
    

    if (image != nullptr)
    {
        
        cv::QRCodeDetector qrDet;
        if (!detected_qr)
        {   
            QImage img((uchar*)image->data, image->cols, image->rows,  QImage::Format_RGB888);
            QPixmap pixmap = QPixmap::fromImage(img);
            ui->camera->setPixmap(pixmap.scaled(ui->camera->width(), ui->camera->height(), Qt::KeepAspectRatioByExpanding));
   
            std::string qr = qrDet.detectAndDecode(*image);
            
            if (qr.length() > 0)
            {
                qInfo() << "Detected QR: " << qr.c_str(); 
                detected_qr = true;
                QTimer::singleShot(2500, this, [=]{
                    detected_qr = false; // debouncing
                    if (m_dialog != nullptr)
                    {
                        m_dialog->hide();
                    }
                }); 
                emit detectedQR(qr, 1, "C10"); 
            }
        }
        emit updated(); // this calls Capture::setSync (essentially a semaphore behavior but way faster than qmutex)
    }
    else
    {
        qCritical() << "image is nullptr";
    }
}
