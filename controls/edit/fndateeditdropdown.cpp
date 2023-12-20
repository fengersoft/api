#include "fndateeditdropdown.h"
#include "ui_fndateeditdropdown.h"

FnDateEditDropDown::FnDateEditDropDown(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FnDateEditDropDown)
{
    ui->setupUi(this);
    setWindowFlag(Qt::Popup);
    setAttribute(Qt::WA_DeleteOnClose);
    ui->edtCal->setSelectedDate(QDate::currentDate());

}

FnDateEditDropDown::~FnDateEditDropDown()
{
    qDebug()<<"~FnDateEditDropDown()";
    delete ui;
}




void FnDateEditDropDown::on_edtCal_clicked(const QDate &date)
{
    emit getData(date);
    close();
}

