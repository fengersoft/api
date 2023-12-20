#include "shelltreeview.h"
#include "qaction.h"
#include "qapplication.h"
#include "qdir.h"
#include "qfileiconprovider.h"
#include "qfileinfo.h"
#include "qicon.h"
#include "qnamespace.h"
#include "qsize.h"
#include "qstandarditemmodel.h"
#include "ui_shelltreeview.h"

ShellTreeView::ShellTreeView(QWidget* parent) :
    QWidget(parent),
    ui(new Ui::ShellTreeView)
{
    ui->setupUi(this);
    m_model = new QStandardItemModel(this);
    ui->tvData->setModel(m_model);
    refreshTreeView();
    QStringList menuNames;
    menuNames<<"在资源管理器显示根目录"<<"刷新";
    for(int i=0;i<menuNames.count();i++)
    {
        QAction *act=new QAction(this);
        act->setText(menuNames[i]);
        connect(act,&QAction::triggered,this,&ShellTreeView::onTriggered);
        addAction(act);
    }

}

ShellTreeView::~ShellTreeView()
{
    delete ui;
}

const QString& ShellTreeView::rootPath() const
{
    return m_rootPath;
}

void ShellTreeView::setRootPath(const QString& newRootPath)
{
    m_rootPath = newRootPath;
    refreshTreeView();
}

void ShellTreeView::refreshTreeView()
{
    m_expandDirs.clear();
    m_model->clear();
    ui->tvData->setUpdatesEnabled(false);
    ui->tvData->setModel(nullptr);
    addChildFile(m_rootPath, nullptr);
    ui->tvData->setModel(m_model);
    ui->tvData->setUpdatesEnabled(true);

}

void ShellTreeView::addChildFile(QString parentPath, QStandardItem* parentNode)
{

    QDir dir(parentPath);
    QFileInfoList fileInfos = dir.entryInfoList();
    for (QFileInfo info : fileInfos)
    {
        if ((info.fileName() == ".") || (info.fileName() == ".."))
        {
            continue;
        }
        QStandardItem* item = new QStandardItem();

        QFileIconProvider provider;
        QIcon ico = provider.icon(info);
        item->setIcon(ico);
        item->setSizeHint(QSize(width(), 48));

        item->setText(info.fileName());
        item->setData(info.absoluteFilePath(), Qt::UserRole + 1);
        item->setData(info.isDir() == true ? 1 : 0, Qt::UserRole + 2);
        if (parentNode == nullptr)
        {
            m_model->appendRow(item);
        }
        else
        {
            parentNode->appendRow(item);
        }
        if (info.isDir())
        {
            QStandardItem* itemNull = new QStandardItem();
            item->appendRow(itemNull);
        }


    }




}

void ShellTreeView::keyPressEvent(QKeyEvent* event)
{
    if (event->key() == Qt::Key_F5)
    {
        refreshTreeView();
    }


}

void ShellTreeView::on_tvData_clicked(const QModelIndex& index)
{
    if (!index.isValid())
    {
        return;
    }
    QStandardItem* item = m_model->itemFromIndex(index);
    QFileInfo info(item->data().toString());
    emit clickNode(info);
}


void ShellTreeView::on_tvData_expanded(const QModelIndex& index)
{
    if (!index.isValid())
    {
        return;
    }
    QStandardItem* item = m_model->itemFromIndex(index);
    QString dirPath = item->data().toString();
    if (!m_expandDirs.contains(dirPath))
    {
        item->removeRows(0, item->rowCount());
        addChildFile(dirPath, item);

        m_expandDirs << dirPath;
    }

}

void ShellTreeView::onTriggered(bool checked)
{
    QAction *act=static_cast<QAction*>(sender());
    if (act->text()=="在资源管理器显示根目录")
    {
        QDesktopServices::openUrl(QUrl::fromLocalFile(m_rootPath));

    }
}

