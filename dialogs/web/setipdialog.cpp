#include "setipdialog.h"
#include "ui_setipdialog.h"

SetIpDialog::SetIpDialog(QWidget* parent) :
    QDialog(parent),
    ui(new Ui::SetIpDialog)
{
    ui->setupUi(this);
    ui->edtUrl->setText(GlobalData::baseUrl);
}

SetIpDialog::~SetIpDialog()
{
    delete ui;
}

QString SetIpDialog::baseUrl() const
{
    GlobalData::baseUrl = ui->edtUrl->text();
    return ui->edtUrl->text();
}

void SetIpDialog::on_btnCancel_clicked()
{
    reject();
}


void SetIpDialog::on_btnOk_clicked()
{
    accept();
}

