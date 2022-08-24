#pragma once
#include <QDialog>

namespace Ui {
class DetectedQRDialog;
}

class DetectedQRDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DetectedQRDialog(QWidget *parent = nullptr);
    ~DetectedQRDialog();
public slots:
    void display(const std::string& qr, const int& state, const std::string& correct_room);

private:
    Ui::DetectedQRDialog *ui;
    const std::string m_attendance_confirmed = "Attendance Confirmed";
    const std::string m_wrong_room = "Wrong room. Please proceed to room ";
    const std::string m_not_found = "Name not found in the list";
};  
