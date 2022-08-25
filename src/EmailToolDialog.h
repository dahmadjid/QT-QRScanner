#ifndef EMAILTOOLDIALOG_H
#define EMAILTOOLDIALOG_H

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

private:
    Ui::EmailToolDialog *ui;
};

#endif // EMAILTOOLDIALOG_H
