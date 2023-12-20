#ifndef MULTILINEEDITDIALOG_H
#define MULTILINEEDITDIALOG_H

#include <QDialog>

namespace Ui {
class MultilineEditDialog;
}

class MultilineEditDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MultilineEditDialog(QWidget *parent = nullptr);
    ~MultilineEditDialog();

private:
    Ui::MultilineEditDialog *ui;
};

#endif // MULTILINEEDITDIALOG_H
