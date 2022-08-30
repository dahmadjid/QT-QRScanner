#pragma once
#include <QMainWindow>

#include <iostream>
#include <QtWidgets>
#include <QMovie>
#include <QMutex>
#include <QTimer>
#include <opencv2/opencv.hpp>
#include <opencv2/objdetect.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "DetectedQRDialog.h"
#include "CSVParser.h"
#include "Dropdown.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent, std::shared_ptr<cv::Mat> image, Dropdown* drop, DetectedQRDialog* dialog);
    ~MainWindow();
    

public slots:
    void updateFrame();
signals:
    void detectedQR(const std::string& qr, const int& state);
    
    void updated();
    void menuButtonClicked();
private:
    Ui::MainWindow *ui;
    QMovie burger_animation_movie;
    bool detected_qr = false;
    int movie_frames;
    CSV::CSVParser m_parser;
    std::string m_session = "Session";
    std::shared_ptr<cv::Mat> m_image;
    Dropdown* m_drop;
    DetectedQRDialog* m_dialog; 

};

