#pragma once

#include <QWidget>
namespace Ui {
class EmailToolDialog;
}

class EmailToolDialog : public QWidget
{
    Q_OBJECT

public:
    explicit EmailToolDialog(QWidget *parent = nullptr);
    ~EmailToolDialog();
signals:
    void sendEmailsClicked();

private:
    Ui::EmailToolDialog *ui;
};

