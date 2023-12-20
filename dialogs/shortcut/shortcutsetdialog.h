#ifndef SHORTCUTSETDIALOG_H
#define SHORTCUTSETDIALOG_H

#include <QDialog>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QFile>
#include "shortcutitemwidget.h"

namespace Ui
{
class ShortCutSetDialog;
}

class ShortCutSetDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ShortCutSetDialog(QWidget* parent = nullptr);
    ~ShortCutSetDialog();
    void loadConfig(QString path);
    void saveConfig(QString path);

private slots:
    void on_btnOk_clicked();

    void on_btnCancel_clicked();

private:
    Ui::ShortCutSetDialog* ui;
};
bool showShortCutSetDialog(QString path);

#endif // SHORTCUTSETDIALOG_H
