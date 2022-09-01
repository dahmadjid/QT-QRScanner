#pragma once

#include <QWidget>
namespace Ui {
class EmailToolDialog;
}

struct EmailToolData
{
    std::string subject = "";
    std::string body = "";
    int group_selected_index = 0;
    int attach_qr_state = 0;
    int all_groups_state = 0;
    std::vector<std::string> attached_files;
};
class EmailToolDialog : public QWidget
{
    Q_OBJECT

public:
    explicit EmailToolDialog(QWidget *parent = nullptr);
    ~EmailToolDialog();
    

signals:
    void sendEmailsClicked(const EmailToolData& data);

public slots:
    void updateGroups(const std::vector<std::string>& files);
private:
    Ui::EmailToolDialog *ui;
    EmailToolData m_data;
};

