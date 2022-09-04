#include "DetectedQRDialog.h"
#include "ui_DetectedQRDialog.h"
#include <QPalette>

#define SD(x) static_cast<int>(x*0.7111111)

DetectedQRDialog::DetectedQRDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DetectedQRDialog)
{
    ui->setupUi(this);
    setStyleSheet("background:transparent;");
    setAttribute(Qt::WA_TranslucentBackground);
    setWindowFlags(Qt::FramelessWindowHint);

    #ifdef LINUX
    QPixmap bg("resources/dialog_background.png");
    #endif 

    #ifdef WINDOWS
    QPixmap bg("resources\\dialog_background.png");
    #endif 

    #ifdef SCALED_DOWN
    setGeometry({0,0,1366,768});
    ui->dialog_background->setGeometry({0,0,1366,768});
    ui->attendance_label->setGeometry({SD(640), SD(540), SD(640), SD(100)});
    ui->name_label->setGeometry({SD(640), SD(440), SD(640), SD(100)});

    #endif
    ui->dialog_background->setPixmap(bg.scaled(ui->dialog_background->width(), ui->dialog_background->height(), Qt::KeepAspectRatio));
    ui->dialog_background->setStyleSheet("QLabel { background-color: transparent }");

}

DetectedQRDialog::~DetectedQRDialog()
{
    delete ui;
}


void DetectedQRDialog::display(const std::string& qr, const int& state)
{
    ui->name_label->setText(std::move(QString::fromStdString(qr)));
    if (state == 0)
    {
        ui->attendance_label->setText(std::move(QString::fromStdString(m_attendance_confirmed)));
        ui->attendance_label->setStyleSheet("QLabel { color: rgb(0,255,0); }");
    }
    // else if (state == 1)
    // {
    //     ui->attendance_label->setText(std::move(QString::fromStdString(m_wrong_room + correct_room)));    // This will really never happen as csvs are separated and i dont want to load entire csvs.
    //     ui->attendance_label->setStyleSheet("QLabel { color: red }"); // students can orient theemselves correctly by reading schedule like humans;
    // }
    else if (state == 1)
    {
        ui->attendance_label->setText(std::move(QString::fromStdString(m_not_found)));
        ui->attendance_label->setStyleSheet("QLabel { color: red; }");
    }
    else
    {
        ui->attendance_label->setText(std::move(QString::fromStdString(m_parser_not_ready)));
        ui->attendance_label->setStyleSheet("QLabel { color: red; }");
    }
    


    this->show();

    
}
