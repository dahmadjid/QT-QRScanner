#include "Capture.h"
#include <QDebug>
#include <QThread>
#include <memory>
#define SRC CWD"/src/"




void Capture::run()     
{
    sync = true;
    cap = std::make_shared<cv::VideoCapture>(0);
    qInfo() << "init capture " << QThread::currentThread(); 
    if (!cap->isOpened()) 
    {
        qCritical() << "cannot open camera";
    }
}

void Capture::getFrame()
{
    if(sync)
    {
        if (!cap->isOpened()) 
        {
            qCritical() << "cannot open camera";
            return;
        }
        if (image != nullptr)
        {
            *cap >> *image;
            if (!image->empty())
            {
                cv::cvtColor(*image, *image, cv::COLOR_BGR2RGB);
                sync = false;
                emit updated();
            }
            
        }
        else
        {
            qCritical() << "image is nullptr";
        }
    }
    else
    {
        // qDebug() << "not sync";
    }
} 

void Capture::setSync()
{
    sync = true;
}