#ifndef CHECKLISTDIALOG_H
#define CHECKLISTDIALOG_H

#include <QDialog>
#include <QStandardItemModel>
#include <QClipboard>
#include <QDateTime>
#include <QPainter>
#include <QBuffer>

namespace Ui {
class CheckListDialog;
}

class CheckListDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CheckListDialog(QWidget *parent = nullptr);
    ~CheckListDialog();
    void copyAsText();
    void copyAsImage();

private slots:
    void on_btnCancel_clicked();

    void on_btnOk_clicked();

private:
    Ui::CheckListDialog *ui;
    QStandardItemModel* m_model;
};
void showCheckListDialog();

#endif // CHECKLISTDIALOG_H
