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
    #ifdef LINUX
    QPixmap bg("resources/dropdown.png");
    #endif

    #ifdef WINDOWS
    QPixmap bg("resources\\dropdown.png");
    #endif
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
    QStringList files = QFileDialog::getOpenFileNames(this, tr("Open CSV file of students"), "", tr("CSV Files (*.csv)"));
    QString files_selected = "";
    if (files.size() > 0)
    {
        m_files.clear();
        for (const auto& file: files)
        {
            for (int i = 0; i < file.length(); i++)
            {
                if (file[file.length() - i - 1] == '/')
                {
                    files_selected+=  "\"" + QString::fromStdString(file.toStdString().substr(file.length() - i, i)) + "\" ";
                    break;
                }
            }
            
            m_files.push_back(file.toStdString());
        }
        qInfo() << "Files selected: " << files_selected;
        

        ui->csv_lineedit->setText(files_selected);

        emit filesSelected(m_files);
    }   
}