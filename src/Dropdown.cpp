#include "Dropdown.h"
#include "ui_Dropdown.h"

Dropdown::Dropdown(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Dropdown)
{
    ui->setupUi(this);
    setStyleSheet("background:transparent;");
    setAttribute(Qt::WA_TranslucentBackground);
    setWindowFlags(Qt::FramelessWindowHint);
    QPixmap bg(CWD"/resources/dropdown.png");
    ui->background->setPixmap(bg.scaled(ui->background->width(), ui->background->height(), Qt::KeepAspectRatio));
    ui->background->setStyleSheet("QLabel { background-color: transparent }");



}

Dropdown::~Dropdown()
{
    delete ui;
}
