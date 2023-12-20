#include "selecticondialog.h"
#include "iconitemwidget.h"
#include "qapplication.h"
#include "qdialog.h"
#include "qdir.h"
#include "qfileinfo.h"
#include "qglobal.h"
#include "qlistwidget.h"
#include "qsize.h"
#include "ui_selecticondialog.h"

SelectIconDialog::SelectIconDialog(QWidget* parent) :
    QDialog(parent),
    ui(new Ui::SelectIconDialog)
{
    ui->setupUi(this);
    ui->lvData->setSpacing(6);
    m_suffixes << "jpg" << "jpeg" << "ico" << "png" << "webp";
}

SelectIconDialog::~SelectIconDialog()
{
    delete ui;
}

void SelectIconDialog::addFolder(QString path)
{
    QDir dir(path);
    QFileInfoList fileInfos = dir.entryInfoList();
    for (const QFileInfo& info : qAsConst(fileInfos))
    {
        if ((info.fileName() == ".") || (info.fileName() == ".."))
        {
            continue;
        }
        if (info.isDir())
        {
            addFolder(info.absoluteFilePath());
        }
        else
        {
            if (!m_suffixes.contains(info.suffix()))
            {
                continue;
            }
            m_fileNames << info.absoluteFilePath();


        }


    }


}

void SelectIconDialog::showAll()
{
    ui->lvData->clear();
    for (QString fileName : qAsConst(m_fileNames))
    {
        addItem(fileName);

    }

}

int SelectIconDialog::exec()
{
    showAll();
    ui->edtSearch->setFocus();
    return QDialog::exec();

}

void SelectIconDialog::addItem(QString fileName)
{
    QListWidgetItem* item = new QListWidgetItem();
    item->setSizeHint(QSize(52, 52));
    ui->lvData->addItem(item);
    IconItemWidget* w = new IconItemWidget(ui->lvData);
    connect(w, &IconItemWidget::clickItemWidget, this, &SelectIconDialog::onClickItemWidget);
    w->setPath(fileName);
    ui->lvData->setItemWidget(item, w);
    QApplication::processEvents();

}

QString SelectIconDialog::getSelectPath()
{
    QString ret;
    for (int i = 0; i < ui->lvData->count(); i++)
    {
        QListWidgetItem* item = ui->lvData->item(i);
        IconItemWidget* w = static_cast<IconItemWidget*>(ui->lvData->itemWidget(item));
        if (w->selected())
        {
            ret = w->path();
            break;
        }
    }

    return ret;

}

void SelectIconDialog::on_edtSearch_returnPressed()
{
    ui->lvData->clear();
    for (QString fileName : m_fileNames)
    {
        if (fileName.indexOf(ui->edtSearch->text()) >= 0)
        {
            addItem(fileName);

        }
    }
}

void SelectIconDialog::onClickItemWidget(IconItemWidget* selWidget)
{
    for (int i = 0; i < ui->lvData->count(); i++)
    {
        QListWidgetItem* item = ui->lvData->item(i);
        IconItemWidget* w = static_cast<IconItemWidget*>(ui->lvData->itemWidget(item));
        w->setSelected(w == selWidget);
    }

}


void SelectIconDialog::on_btnCancel_clicked()
{
    reject();
}


void SelectIconDialog::on_btnOk_clicked()
{
    accept();
}

