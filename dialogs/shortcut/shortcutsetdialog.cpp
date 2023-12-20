#include "shortcutsetdialog.h"
#include "qjsonarray.h"
#include "qjsondocument.h"
#include "qjsonobject.h"
#include "qlayoutitem.h"
#include "qlistwidget.h"
#include "qsize.h"
#include "shortcutitemwidget.h"
#include "ui_shortcutsetdialog.h"

ShortCutSetDialog::ShortCutSetDialog(QWidget* parent) :
    QDialog(parent),
    ui(new Ui::ShortCutSetDialog)
{
    ui->setupUi(this);
}

ShortCutSetDialog::~ShortCutSetDialog()
{
    delete ui;
}

void ShortCutSetDialog::loadConfig(QString path)
{
    QFile file(path);
    file.open(QIODevice::ReadOnly);
    QByteArray data = file.readAll();
    QJsonDocument jdoc = QJsonDocument::fromJson(data);
    QJsonArray jarr = jdoc.array();
    for (int i = 0; i < jarr.count(); i++)
    {
        QJsonObject jobj = jarr.at(i).toObject();
        QListWidgetItem* item = new QListWidgetItem();
        ui->lvData->addItem(item);
        ShortCutItemWidget* w = new ShortCutItemWidget(this);
        w->setCaption(jobj["caption"].toString());
        w->setShortCut(jobj["shortcut"].toString());
        item->setSizeHint(QSize(ui->lvData->width(), 42));
        ui->lvData->setItemWidget(item, w);
    }
    file.close();

}

void ShortCutSetDialog::saveConfig(QString path)
{
    QJsonArray jarr;
    for (int i = 0; i < ui->lvData->count(); i++)
    {
        QListWidgetItem* item = ui->lvData->item(i);
        ShortCutItemWidget* w = static_cast<ShortCutItemWidget*>(ui->lvData->itemWidget(item));
        QJsonObject jobj;
        jobj["caption"] = w->caption();
        jobj["shortcut"] = w->shortCut();
        jarr.append(jobj);

    }
    QJsonDocument jdoc;
    jdoc.setArray(jarr);
    QByteArray data = jdoc.toJson();
    QFile file(path);
    file.open(QIODevice::WriteOnly);
    file.write(data);
    file.close();

}

void ShortCutSetDialog::on_btnOk_clicked()
{
    accept();
}


void ShortCutSetDialog::on_btnCancel_clicked()
{
    reject();
}


bool showShortCutSetDialog(QString path)
{
    bool b = false;
    ShortCutSetDialog* dlg = new ShortCutSetDialog();
    dlg->loadConfig(path);
    int ret = dlg->exec();
    if (ret == QDialog::Accepted)
    {
        dlg->saveConfig(path);
        b = true;
    }
    delete dlg;
    return b;

}
