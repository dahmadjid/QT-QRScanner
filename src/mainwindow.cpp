#include "mainwindow.h"
#include <QDebug>
#include "./ui_mainwindow.h"
#include <QMovie>

MainWindow::MainWindow(QWidget *parent, std::shared_ptr<cv::Mat> image, Dropdown* drop, DetectedQRDialog* dialog)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , burger_animation_movie(QMovie(this))
    ,m_image(image)
    ,m_drop(drop)
    ,m_dialog(dialog)
{
    ui->setupUi(this);
// burgir button animation -----------------------------------------------------------------------------------------------------------
    // burger_animation_movie.setFileName(CWD"/resources/burger.gif");
    // burger_animation_movie.start();
    // burger_animation_movie.setPaused(true);

    // // jumps to the initial state, apparently i need to go frame by frame.
    // // jumptoframe(14) directly doesnt work. investigate later
    // for (int i = 0; i<=14; i++)
    // {
    //     burger_animation_movie.jumpToFrame(i);
    // }

    // ui->menu_button->setIcon(burger_animation_movie.currentPixmap());
    // ui->menu_button->setIconSize({74,74});
    // ui->menu_button->setFlat(true);
    // ui->menu_button->setStyleSheet("QPushButton { background-color: transparent }");
    // ui->menu_button->setStyleSheet("QPushButton:pressed { background-color: rgba(0, 0, 0, 0);border-style: inset;border-width: 0px;}");
    // QObject::connect(&burger_animation_movie, &QMovie::frameChanged, [=]{
    //     ui->menu_button->setIcon(burger_animation_movie.currentPixmap());
    //     ui->menu_button->setIconSize({74,74});
    //     if (burger_animation_movie.currentFrameNumber() == 25)
    //     {
    //         burger_animation_movie.setPaused(true);
    //     }
    //     else if (burger_animation_movie.currentFrameNumber() == 13)
    //     {
    //         burger_animation_movie.setPaused(true);
    //     }
    // });

    QObject::connect(ui->menu_button, &QPushButton::clicked, [=]{

        // burger_animation_movie.setPaused(false);  // animation disabled until animation of drop down menu added
        emit menuButtonClicked();
    });

// Logos -------------------------------------------------------------------------------------------------------------------------------
#ifdef LINUX
    QPixmap bg("resources/background.png");
    QPixmap wameedh_logo("resources/wameedh_logo.png");
    QPixmap event_logo("resources/schlumberger.png");
    QPixmap sponsor_logo("resources/deadline.png");
    QPixmap scan_img("resources/scan_text.png");
    QPixmap burger_img("resources/burger.png");
    
#endif
#ifdef WINDOWS
    QPixmap bg("resources\\background.png");
    QPixmap wameedh_logo("resources\\wameedh_logo.png");
    QPixmap event_logo("resources\\schlumberger.png");
    QPixmap sponsor_logo("resources\\deadline.png");
    QPixmap scan_img("resources\\scan_text.png");
    QPixmap burger_img("resources\\burger.png");
    
#endif
    ui->background->setPixmap(bg.scaled(ui->background->width(), ui->background->height(), Qt::KeepAspectRatio));
    
    ui->logo_center->setPixmap(wameedh_logo.scaled(ui->logo_center->width(), ui->logo_center->height(), Qt::KeepAspectRatio));
    ui->logo_center->setStyleSheet("QLabel { background-color: transparent }");

    ui->logo_right->setPixmap(event_logo.scaled(ui->logo_right->width(), ui->logo_right->height(), Qt::KeepAspectRatio));
    ui->logo_right->setStyleSheet("QLabel { background-color: transparent }");

    ui->logo_left->setPixmap(sponsor_logo.scaled(ui->logo_left->width(), ui->logo_left->height(), Qt::KeepAspectRatio));
    ui->logo_left->setStyleSheet("QLabel { background-color: transparent }");

    ui->scan_text->setPixmap(scan_img.scaled(ui->scan_text->width(), ui->scan_text->height(), Qt::KeepAspectRatio));
    ui->scan_text->setStyleSheet("QLabel { background-color: transparent }");

    ui->menu_button->setIcon(burger_img.scaled(ui->menu_button->width(), ui->menu_button->height(), Qt::KeepAspectRatio));
    ui->menu_button->setStyleSheet("QPushButton { background-color: transparent }");
    ui->menu_button->setStyleSheet("QPushButton:pressed { background-color: rgba(0, 0, 0, 0);border-style: inset;border-width: 0px;}");

    ui->camera->setStyleSheet("QLabel { background-color: transparent }");

    QObject::connect(m_drop, &Dropdown::textChanged, [&](const QString& text){m_session = text.toStdString(); qInfo() << m_session.c_str();});
    QObject::connect(m_drop, &Dropdown::filesSelected, [&](const std::vector<std::string>& files){m_parser.parseMultiple(files);emit csvLoaded(files);});
}

MainWindow::~MainWindow()
{
    delete ui;

}

void MainWindow::updateFrame()
{   
    
    

    if (m_image != nullptr)
    {
        
        cv::QRCodeDetector qrDet;
        if (!detected_qr)
        {   
            QImage img((uchar*)m_image->data, m_image->cols, m_image->rows,  QImage::Format_RGB888);
            QPixmap pixmap = QPixmap::fromImage(img);
            ui->camera->setPixmap(pixmap.scaled(ui->camera->width(), ui->camera->height(), Qt::KeepAspectRatioByExpanding));
            std::string qr;
            try
            {
                qr = qrDet.detectAndDecode(*m_image);
            }
            catch(...)
            {
                qInfo() << "Exception from qr decoder";
            }
            
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
                if (m_parser.ready)
                {
                    bool found = m_parser.updateAttendance(qr, m_session);
                    if (found)
                    {

                        qr = m_parser.getNameOnly(qr);
                        emit detectedQR(qr, 0); 

                    }
                    else
                    {
                        emit detectedQR(qr, 1); 
                    }
                }
                else
                {
                    emit detectedQR(qr, 2);  // implement 2 so that it displays that you have to select a csv file
                }
            }
        }
        emit updated(); // this calls Capture::setSync (essentially a semaphore behavior but way faster than qmutex)
    }
    else
    {
        qCritical() << "image is nullptr";
    }
}

// void MainWindow::sendEmails(const EmailToolData& data)
// {
//     m_parser.generateQRs(0);
//     if (data.attach_qr_state == Qt::Checked)
//     {
        
//     }
// }
