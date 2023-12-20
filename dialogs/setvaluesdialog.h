#ifndef SETVALUESDIALOG_H
#define SETVALUESDIALOG_H

#include <QDialog>

namespace Ui
{
class SetValuesDialog;
}

class SetValuesDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SetValuesDialog(QWidget* parent = nullptr);
    ~SetValuesDialog();

    QString caption() const;
    void setCaption(const QString& newCaption);

    QStringList values() const;
    void setValues(const QStringList& newValues);

private slots:
    void on_btnOk_clicked();

    void on_btnCancel_clicked();

private:
    Ui::SetValuesDialog* ui;
    mutable QString m_caption;
    mutable QStringList m_values;
};

bool setValues(QString title, QString caption, QStringList& values);

#endif // SETVALUESDIALOG_H
