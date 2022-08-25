#ifndef DROPDOWN_H
#define DROPDOWN_H

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

};

#endif // DROPDOWN_H
