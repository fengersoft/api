#include "appshowwidget.h"
#include "ui_appshowwidget.h"

AppShowWidget::AppShowWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AppShowWidget)
{
    ui->setupUi(this);
    m_backgroundImage=QPixmap();
    setMouseTracking(true);
    m_helper=new WidgetHelper(this);
    m_helper->setControl(this);
    QStringList menuNames;
    menuNames<<"添加"<<"修改"<<"删除";
    for (int i=0;i<menuNames.count();i++)
    {
        QAction *act=new QAction(this);
        act->setText(menuNames[i]);
        connect(act,&QAction::triggered,this,&AppShowWidget::onActionTriggered);
        addAction(act);

    }

}

AppShowWidget::~AppShowWidget()
{
    delete ui;
}

void AppShowWidget::loadAppInfos()
{
    if (!QFile::exists(m_configPath))
    {
        return;
    }
    qDeleteAll(m_items);
    m_items.clear();

    QFile file(m_configPath);
    file.open(QFile::ReadOnly);
    QByteArray data=file.readAll();
    file.close();
    QJsonDocument jdoc=QJsonDocument::fromJson(data);


    QJsonArray jarr=jdoc.array();
    for (int i=0;i<jarr.count();i++)
    {
        QJsonObject jobj=jarr.at(i).toObject();
        AppShowWidgetItem *item=new AppShowWidgetItem(this);
        item->setCaption(jobj["caption"].toString());
        item->setPath(jobj["path"].toString());
        m_items<<item;
    }

    update();


}

void AppShowWidget::saveAppInfos()
{
    QJsonArray jarr;
    for (int i=0;i<m_items.count();i++)
    {
        AppShowWidgetItem *item=m_items.at(i);
        QJsonObject jobj;
        jobj["caption"]=item->caption();
        jobj["path"]=item->path();
        jarr.append(jobj);
    }
    QJsonDocument jdoc;
    jdoc.setArray(jarr);
    QByteArray data=jdoc.toJson();
    QFile file(m_configPath);
    file.open(QFile::WriteOnly);
    file.write(data);
    file.close();


}

const QString &AppShowWidget::configPath() const
{
    return m_configPath;
}

void AppShowWidget::setConfigPath(const QString &newConfigPath)
{
    m_configPath = newConfigPath;
}

const QList<AppShowWidgetItem *> &AppShowWidget::items() const
{
    return m_items;
}

void AppShowWidget::setItems(const QList<AppShowWidgetItem *> &newItems)
{
    m_items = newItems;
}

void AppShowWidget::paintEvent(QPaintEvent *event)
{
    QPoint curPt=m_helper->cursorPos();
    QPainter painter;
    painter.begin(this);
    QRect clientRc=m_helper->clientRect();
    if (!m_backgroundImage.isNull())
    {
        painter.drawPixmap(clientRc,m_backgroundImage,m_backgroundImage.rect());
    }

    int l=32;
    int t=32;
    for (int i=0;i<m_items.count();i++)
    {
        if (l>width())
        {
            l=32;
            t+=128;
        }

        AppShowWidgetItem *item=m_items.at(i);
        QRect itemRc(l,t,64,96);
        item->setRect(itemRc);
        if (item->icon().isNull())
        {
            QFileInfo info(item->path());
            QFileIconProvider provider;
            QIcon icon=provider.icon(info);
            item->setIcon(icon.pixmap(48,48));

        }
        if (itemRc.contains(curPt))
        {
            painter.setPen(QColor(255,255,255,60));
            painter.setBrush(QColor(255,255,255,60));
            painter.drawRoundedRect(itemRc,4,4);

        }
        QRect iconRc(l+8,t+8,48,48);
        painter.drawPixmap(iconRc,item->icon(),item->icon().rect());
        QRect textRc(l,t+64,64,32);
        QTextOption op;
        op.setWrapMode(QTextOption::WrapAnywhere);
        op.setAlignment(Qt::AlignCenter);
        QFontMetrics fm=painter.fontMetrics();
        QString caption=fm.elidedText(item->caption(),Qt::ElideRight,96);




        painter.setPen(Qt::white);
        painter.drawText(textRc,caption,op);


        l+=96;




    }

    painter.end();

}

void AppShowWidget::mousePressEvent(QMouseEvent *event)
{
    QPoint curPt=m_helper->cursorPos();
    m_selectItem=nullptr;
    for(int i=0;i<m_items.count();i++)
    {
        AppShowWidgetItem* item=m_items.at(i);
        if (item->rect().contains(curPt))
        {
            m_selectItem=item;
            break;
        }


    }
    if (m_selectItem==nullptr)
    {
        return;
    }
    if (event->button()==Qt::LeftButton)
    {
       QDesktopServices::openUrl(QUrl::fromLocalFile("file:"+m_selectItem->path()));

    }else if (event->button()==Qt::RightButton)
    {

    }



}

void AppShowWidget::mouseMoveEvent(QMouseEvent *event)
{
    update();

}

void AppShowWidget::onActionTriggered()
{
    QAction *act=static_cast<QAction*>(sender());
    if (act->text()=="添加")
    {
        EditAppInfoDialog *dlg=new EditAppInfoDialog();
        dlg->setWindowTitle("添加");
        int ret=dlg->exec();
        if (ret==QDialog::Accepted)
        {
            AppShowWidgetItem *item=new AppShowWidgetItem(this);
            item->setCaption(dlg->caption());
            item->setPath(dlg->path());
            m_items<<item;
            update();
            saveAppInfos();
        }
        delete dlg;
    }
    else if (act->text()=="修改")
    {
        if (m_selectItem==nullptr)
        {
            return;
        }
        EditAppInfoDialog *dlg=new EditAppInfoDialog();
        dlg->setWindowTitle("修改");
        dlg->setCaption(m_selectItem->caption());
        dlg->setPath(m_selectItem->path());
        int ret=dlg->exec();
        if (ret==QDialog::Accepted)
        {

            m_selectItem->setCaption(dlg->caption());
            m_selectItem->setPath(dlg->path());
            m_selectItem->setIcon(QPixmap());
            update();
            saveAppInfos();
        }
        delete dlg;

    }else
        if (act->text()=="删除")
    {
        if (m_selectItem==nullptr)
        {
            return;
        }
        m_items.removeOne(m_selectItem);
        delete m_selectItem;
        m_selectItem=nullptr;
        saveAppInfos();
        update();

    }
}

const QPixmap &AppShowWidget::backgroundImage() const
{
    return m_backgroundImage;
}

void AppShowWidget::setBackgroundImage(const QPixmap &newBackgroundImage)
{
    m_backgroundImage = newBackgroundImage;
    update();
}
