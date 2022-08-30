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
    void display(const std::string& qr, const int& state);

private:
    Ui::DetectedQRDialog *ui;
    const char* m_attendance_confirmed = "Attendance Confirmed";
    const char* m_not_found = "Name not found in the list";
    const char* m_parser_not_ready = "Make sure to choose a .csv file.";
};  
