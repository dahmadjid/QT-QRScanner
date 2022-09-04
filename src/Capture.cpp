#include "Capture.h"
#include <QDebug>
#include <QThread>
#include <memory>




void Capture::run()     
{
    sync = true;
    m_cap = std::make_unique<cv::VideoCapture>(0);
    qInfo() << "init capture " << QThread::currentThread(); 
    if (!m_cap->isOpened()) 
    {
        qCritical() << "cannot open camera";
    }
}

void Capture::getFrame()
{
    if(sync)
    {
        if (!m_cap->isOpened()) 
        {
            qCritical() << "cannot open camera";
            return;
        }
        if (m_image != nullptr)
        {
            *m_cap >> *m_image;
            if (!m_image->empty())
            {
                cv::cvtColor(*m_image, *m_image, cv::COLOR_BGR2RGB);
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