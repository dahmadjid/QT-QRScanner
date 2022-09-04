#include "Dropdown.h"
#include "ui_Dropdown.h"
#include <QFileDialog>

#define SD(x) static_cast<int>(x*0.7111111)

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

    #ifdef SCALED_DOWN
    setGeometry({0,0,SD(214),SD(390)});
    ui->background->setGeometry({0, 0 ,SD(214) ,SD(390)});
    ui->csv_button->setGeometry({SD(7), SD(192) ,SD(80) ,SD(30)});
    ui->csv_lineedit->setGeometry({SD(87), SD(192) ,SD(120) ,SD(30)});
    ui->email_tool_button->setGeometry({SD(7), SD(99) ,SD(200) ,SD(30)});
    ui->session_label->setGeometry({SD(7), SD(291) ,SD(80) ,SD(30)});
    ui->session_lineedit->setGeometry({SD(87), SD(291) ,SD(120) ,SD(30)});

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