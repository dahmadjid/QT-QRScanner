#pragma once

#include <QObject>
#include <QThread>
#include <QMutex>

#include <opencv2/opencv.hpp>
#include <opencv2/objdetect.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc/imgproc.hpp>
// https://mayaposch.wordpress.com/2011/11/01/how-to-really-truly-use-qthreads-the-full-explanation/

class Capture : public QObject{
    Q_OBJECT
 
public:
    std::shared_ptr<cv::Mat> image;
    std::shared_ptr<cv::VideoCapture> cap;
    std::shared_ptr<QMutex> image_mutex;
public slots:

    void run();
    void getFrame();
    void setSync();
signals:
    void updated();
    void finished();

 
private:
    bool sync = true;
    // add your variables here
};



