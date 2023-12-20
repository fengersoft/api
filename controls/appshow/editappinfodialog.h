#ifndef EDITAPPINFODIALOG_H
#define EDITAPPINFODIALOG_H

#include <QDialog>
#include <QFileDialog>

namespace Ui {
class EditAppInfoDialog;
}

class EditAppInfoDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EditAppInfoDialog(QWidget *parent = nullptr);
    ~EditAppInfoDialog();

    const QString &caption() const;
    void setCaption(const QString &newCaption);

    const QString &path() const;
    void setPath(const QString &newPath);

private slots:
    void on_btnCancel_clicked();

    void on_btnOk_clicked();

    void on_btnOpen_clicked();

private:
    Ui::EditAppInfoDialog *ui;
    mutable QString m_caption;
    mutable QString m_path;
};

#endif // EDITAPPINFODIALOG_H
