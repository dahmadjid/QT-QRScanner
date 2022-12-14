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
    Capture(std::shared_ptr<cv::Mat> image): m_image(image) {}
    
public slots:

    void run();
    void getFrame();
    void setSync();
signals:
    void updated();
    void finished();

 
private:
    bool sync = true;   // this and setSync replaces mutex, syncing like this with signals and slots is way faster, tried qmutex and it was terribly slow
    std::shared_ptr<cv::Mat> m_image;
    std::unique_ptr<cv::VideoCapture> m_cap;


};



