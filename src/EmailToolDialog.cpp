#include "EmailToolDialog.h"
#include "ui_EmailToolDialog.h"

EmailToolDialog::EmailToolDialog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EmailToolDialog)
{
    ui->setupUi(this);
    setStyleSheet("background:transparent;");
    setAttribute(Qt::WA_TranslucentBackground);
    // setWindowFlags(Qt::FramelessWindowHint);
    #ifdef LINUX
    QPixmap bg("resources/email_dialog_background.png");
    #endif

    #ifdef WINDOWS
    QPixmap bg("resources\\email_dialog_background.png");
    #endif
    ui->background->setPixmap(bg.scaled(ui->background->width(), ui->background->height(), Qt::KeepAspectRatio));
    ui->background->setStyleSheet("QLabel { background-color: transparent }");
    QObject::connect(ui->send_emails_button, &QPushButton::clicked, [&]{emit sendEmailsClicked(m_data);});
    
}

EmailToolDialog::~EmailToolDialog()
{
    delete ui;
}

void EmailToolDialog::updateGroups(const std::vector<std::string>& files)
{
    
    if (files.size() > 0)
    {
        ui->groups_combo->clear();

        for (const auto& file: files)
        {
            for (int i = 0; i < file.length(); i++)
            {
                if (file[file.length() - i - 1] == '/')
                {
                    ui->groups_combo->addItem(QString::fromStdString(file.substr(file.length() - i, i)));
                    break;
                }
            }
        }
        ui->groups_combo->setCurrentIndex(0);
    }
    

}