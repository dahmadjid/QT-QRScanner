#pragma once

#include <QWidget>

namespace Ui {
class Dropdown;
}

class Dropdown : public QWidget
{
    Q_OBJECT

public:
    explicit Dropdown(QWidget *parent = nullptr);
    ~Dropdown();
signals:
    void emailToolButtonClicked();
private:
    Ui::Dropdown *ui;
    std::vector<std::string> m_files;
signals:
    void textChanged(const QString& text);
    void filesSelected(const std::vector<std::string>& files);
private slots:
    void onFilesSelected();

};

