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

QString SetIpDialog::getBaseUrl(QString defaultUrl)
{
    QString path = QApplication::applicationDirPath() + "/configs/config.ini";
    qDebug() << path;
    QSettings ini(path, QSettings::IniFormat);
    ini.beginGroup("base");
    QString url = ini.value("url").toString();
    ini.endGroup();

    return url;

}

void SetIpDialog::setBaseUrl(QString url)
{
    QString path = QApplication::applicationDirPath() + "/configs/config.ini";
    QSettings ini(path, QSettings::IniFormat);
    ini.beginGroup("base");
    ini.setValue("url", url);
    ini.endGroup();
    GlobalData::baseUrl = url;



}

void SetIpDialog::on_btnCancel_clicked()
{
    reject();
}


void SetIpDialog::on_btnOk_clicked()
{
    accept();
}

