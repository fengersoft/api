#ifndef SETIPDIALOG_H
#define SETIPDIALOG_H

#include <QDialog>
#include "../api/global/globaldata.h"

namespace Ui
{
class SetIpDialog;
}

class SetIpDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SetIpDialog(QWidget* parent = nullptr);
    ~SetIpDialog();
    QString baseUrl() const;

private slots:
    void on_btnOk_clicked();

    void on_btnCancel_clicked();

private:
    Ui::SetIpDialog* ui;
};

#endif // SETIPDIALOG_H
