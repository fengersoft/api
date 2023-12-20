#ifndef SELECTTABLEVIEWDIALOG_H
#define SELECTTABLEVIEWDIALOG_H

#include <QDialog>
#include <QStandardItemModel>

namespace Ui
{
class SelectTableViewDialog;
}

class SelectTableViewDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SelectTableViewDialog(QWidget* parent = nullptr);
    ~SelectTableViewDialog();

    QStandardItemModel* model() const;
    void setModel(QStandardItemModel* newModel);
    QStandardItem* selectItem(int column = 0);

private slots:
    void on_btnCancel_clicked();

    void on_btnOk_clicked();

    void on_lvData_doubleClicked(const QModelIndex& index);

private:
    Ui::SelectTableViewDialog* ui;
    QStandardItemModel* m_model;
};

SelectTableViewDialog* createSelectTableViewDialog(QString title, QStringList& labels);
#endif // SELECTTABLEVIEWDIALOG_H
