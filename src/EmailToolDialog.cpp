#include "EmailToolDialog.h"
#include "ui_EmailToolDialog.h"

EmailToolDialog::EmailToolDialog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EmailToolDialog)
{
    ui->setupUi(this);
    setStyleSheet("background:transparent;");
    setAttribute(Qt::WA_TranslucentBackground);
    setWindowFlags(Qt::FramelessWindowHint);
    QPixmap bg(CWD"/resources/email_dialog_background.png");
    ui->background->setPixmap(bg.scaled(ui->background->width(), ui->background->height(), Qt::KeepAspectRatio));
    ui->background->setStyleSheet("QLabel { background-color: transparent }");
    QObject::connect(ui->send_emails_button, &QPushButton::clicked, [&]{emit sendEmailsClicked();});

}

EmailToolDialog::~EmailToolDialog()
{
    delete ui;
}
