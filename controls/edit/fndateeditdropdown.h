#ifndef FNDATEEDITDROPDOWN_H
#define FNDATEEDITDROPDOWN_H

#include <QWidget>
#include <QDebug>
#include <QDate>

namespace Ui {
class FnDateEditDropDown;
}

class FnDateEditDropDown : public QWidget
{
    Q_OBJECT

public:
    explicit FnDateEditDropDown(QWidget *parent = nullptr);
    ~FnDateEditDropDown();
signals:
    void getData(QDate date);
private slots:


    void on_edtCal_clicked(const QDate &date);

private:
    Ui::FnDateEditDropDown *ui;
};

#endif // FNDATEEDITDROPDOWN_H
