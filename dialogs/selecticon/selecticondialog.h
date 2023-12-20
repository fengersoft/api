#ifndef SELECTICONDIALOG_H
#define SELECTICONDIALOG_H

#include <QDialog>
#include <QDir>
#include "iconitemwidget.h"
#include "qlist.h"
#include "qset.h"

namespace Ui
{
class SelectIconDialog;
}

class SelectIconDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SelectIconDialog(QWidget* parent = nullptr);
    ~SelectIconDialog();
    void addFolder(QString path);
    void showAll();
    int exec();
    void addItem(QString fileName);
    QString getSelectPath();
private slots:
    void on_edtSearch_returnPressed();
    void onClickItemWidget(IconItemWidget* selWidget);
    void on_btnCancel_clicked();

    void on_btnOk_clicked();

private:
    Ui::SelectIconDialog* ui;
    QSet<QString> m_suffixes;
    QStringList m_fileNames;
};

#endif // SELECTICONDIALOG_H
