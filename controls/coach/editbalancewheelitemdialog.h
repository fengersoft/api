#ifndef EDITBALANCEWHEELITEMDIALOG_H
#define EDITBALANCEWHEELITEMDIALOG_H

#include <QDialog>
#include "../color/colortoolbar.h"
#include "../base/fnwidgetapi.h"

namespace Ui {
class EditBalanceWheelItemDialog;
}

class EditBalanceWheelItemDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EditBalanceWheelItemDialog(QWidget *parent = nullptr);
    ~EditBalanceWheelItemDialog();

    int score() const;
    void setScore(int newScore);

    const QString &caption() const;
    void setCaption(const QString &newCaption);

    const QColor &color() const;
    void setColor(const QColor &newColor);

private slots:
    void on_btnCancel_clicked();

    void on_btnOk_clicked();

private:
    Ui::EditBalanceWheelItemDialog *ui;
    mutable int m_score;
    mutable QString m_caption;
    mutable QColor m_color;
    ColorToolbar *m_toolbar;
};

#endif // EDITBALANCEWHEELITEMDIALOG_H
