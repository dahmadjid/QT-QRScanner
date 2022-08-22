#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>

#include <iostream>

#include <QMovie>
#include <QMutex>
#include <QTimer>
#include <opencv2/opencv.hpp>
#include <opencv2/objdetect.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc/imgproc.hpp>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    std::shared_ptr<cv::Mat> image;
public slots:
    void updateFrame();
signals:
    void detectedQR(std::string qr);

    void updated();
private:
    Ui::MainWindow *ui;
    QMovie burger_animation_movie;
    bool detected_qr = false;

    int movie_frames;

};

#endif // MAINWINDOW_H