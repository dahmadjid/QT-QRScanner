#include "Dropdown.h"
#include "ui_Dropdown.h"
#include <QFileDialog>
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

    QObject::connect(ui->email_tool_button, &QPushButton::clicked, [=]{emit emailToolButtonClicked();});

    ui->session_lineedit->setMaxLength(10);
    ui->session_lineedit->setText("Session");
    QObject::connect(ui->session_lineedit, &QLineEdit::textChanged, [=](const QString& text){emit textChanged(text);});

     

    QObject::connect(ui->csv_button, &QPushButton::clicked, this, &Dropdown::onFilesSelected);

}

Dropdown::~Dropdown()
{
    delete ui;
}



void Dropdown::onFilesSelected()
{
    QStringList files = QFileDialog::getOpenFileNames(this, tr("Open CSV file of students"), CWD, tr("CSV Files (*.csv)"));
    QString files_selected = "";
    if (files.size() > 0)
    {
        for (int i = 0; i < files.size(); i++)
        {
            files_selected+=  "\"" + files[i] + "\" ";
            m_files.push_back(files[i].toStdString());
        }
        qInfo() << "Files selected: " << files_selected;
        ui->csv_lineedit->setText(files_selected);

        emit filesSelected(m_files);
    }   
}