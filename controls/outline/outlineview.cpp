#include "outlineview.h"
#include "ui_outlineview.h"

OutlineView::OutlineView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OutlineView)
{
    ui->setupUi(this);
    setMouseTracking(true);
    m_helper=new WidgetHelper(this);
    m_helper->setControl(this);
    m_helper->setItemsTop(16);
    m_edit=new OutLineViewItemEdit(this);
    m_edit->setHidden(true);
    connect(m_edit,&OutLineViewItemEdit::keyPressBackSpace,this,&OutlineView::onkeyPressBackSpace);
}

OutlineView::~OutlineView()
{
    delete ui;
}

void OutlineView::addItem(OutLineViewItem *item, OutLineViewItem *pItem)
{
    if (pItem==nullptr)
    {

        m_rootItems<<item;

    }else
    {
        pItem->addChild(item);
    }
    m_items<<item;
    item->setParent(pItem);
    update();

}

void OutlineView::addItem(QString name, OutLineViewItem *pItem)
{
    OutLineViewItem *item=new OutLineViewItem(this);
    item->setItemType(ItemInfo);
    item->setName(name);
    item->setPid(pItem->id());
    addItem(item,pItem);

}

void OutlineView::insertAfterItem(OutLineViewItem *item, OutLineViewItem *curItem, OutLineViewItem *pItem)
{
    if (pItem==nullptr)
    {
        int i=m_rootItems.indexOf(curItem);
        m_rootItems.insert(i+1,item);

    }else
    {
        pItem->insertChild(item,curItem);
    }
    m_items<<item;
    item->setParent(pItem);
    update();
}

OutLineViewItem *OutlineView::findItemById(int id)
{
    for(OutLineViewItem  *item:m_items)
    {
        if (item->id()==id)
        {
            return item;
        }
    }
    return nullptr;

}

void OutlineView::drawItems(QPainter &painter, int &t, int l, QList<OutLineViewItem *> &parentItems)
{
    for (int i=0;i<parentItems.count();i++)
    {
        OutLineViewItem *item=parentItems.at(i);
        QFont font=painter.font();
        font.setPointSize(12);
        font.setFamily("新宋体");
        font.setBold(item->itemType()==ItemCate);
        painter.setFont(font);
        QRect textRc(l,t,width()-l-16,24);
        item->setRect(textRc);
        QRect iconRc(l-24,t+4,16,16);
        item->setIconRect(iconRc);
        if (item->name().startsWith("http"))
        {
            painter.drawPixmap(iconRc,m_urlIcon,m_urlIcon.rect());
        }
        if (item->selected())
        {
            QRect fillRc(l-4,t,width()-l-12,24);
            painter.fillRect(fillRc,QColor(QColor(204,232,255)));
        }
        painter.drawText(textRc,item->name(),Qt::AlignLeft|Qt::AlignVCenter);

        t+=32;
        drawItems(painter,t,l+32,item->childrenIems());
    }

}

OutLineViewItem *OutlineView::selectedItem()
{
    for (OutLineViewItem *item:m_items)
    {
        if (item->selected())
        {
            return item;
        }
    }
    return nullptr;

}

void OutlineView::showEditor()
{
    OutLineViewItem *selItem=selectedItem();

    if (selItem==nullptr)
    {

        if ((m_edit->isVisible()) && (m_edit->item()!=nullptr))
        {
            m_edit->item()->setName(m_edit->text());
            emit saveItemData(m_edit->item());
        }
        m_edit->setHidden(true);
        return;
    }
    if (selItem->itemType()==ItemCate)
    {
        m_edit->setHidden(true);
        return;
    }
    m_edit->setHidden(false);
    m_edit->setGeometry(selItem->rect());
    if (m_edit->item()!=nullptr)
    {
        m_edit->item()->setName(m_edit->text());
        emit saveItemData(m_edit->item());
    }
    m_edit->setText(selItem->name());
    m_edit->setItem(selItem);

    m_edit->setFocus();



}

void OutlineView::clearItems()
{
    if (!m_edit->isHidden())
    {
        m_edit->setHidden(true);
        m_edit->setItem(nullptr);

    }
    qDeleteAll(m_items);
    m_items.clear();
    m_rootItems.clear();
    m_helper->setItemsTop(16);

}

QList<OutLineViewItem *> &OutlineView::items()
{
    return m_items;

}

void OutlineView::quitEdit(bool saveEdit)
{
    if (!m_edit->isHidden())
    {
        OutLineViewItem* item=m_edit->item();
        item->setName(m_edit->text());
        if (saveEdit)
        {
            m_edit->setHidden(true);
        }


    }

}

void OutlineView::paintEvent(QPaintEvent *event)
{
    QPainter painter;
    painter.begin(this);

    QRect clientRc=m_helper->clientRect();
    painter.fillRect(clientRc,QBrush(Qt::white));

    int t=m_helper->itemsTop();
    drawItems(painter,t,80,m_rootItems);

    painter.end();

}

void OutlineView::mousePressEvent(QMouseEvent *event)
{
    setFocus();
    QPoint curPt=m_helper->cursorPos();
   for (OutLineViewItem *item:m_items)
   {
       item->setSelected(item->rect().contains(curPt));
       if (item->iconRect().contains(curPt))
       {
           emit clickItemIcon(item);
       }
   }
   update();

    if (event->button()==Qt::RightButton)
    {
        QStringList menuNames;
        menuNames<<"复制"<<"复制子结点"<<"替换"<<"-"<<"导出为MarkDown"<<"-"<<"百度选中内容";
        QMenu *menu=new QMenu(this);
        for(int i=0;i<menuNames.count();i++)
        {
            QAction *act=new QAction(menu);
            if (menuNames[i]=="-")
            {
                act->setSeparator(true);

            }else
            {
                act->setText(menuNames[i]);
                connect(act,&QAction::triggered,this,&OutlineView::onMenuActionTriggered);

            }
            menu->addAction(act);
        }
        update();
        menu->exec(QCursor::pos());

        delete menu;

    }else
    {

       showEditor();
    }


}

void OutlineView::keyPressEvent(QKeyEvent *event)
{

    if (event->key()==Qt::Key_Return)
    {
        OutLineViewItem *selItem=selectedItem();
        if (selItem==nullptr)
        {
            if (m_edit->item()!=nullptr)
            {
                emit saveItemData(m_edit->item());
                m_edit->setItem(nullptr);
            }
            return;
        }
        OutLineViewItem *item=new OutLineViewItem(this);
        item->setItemType(ItemInfo);

        if (selItem->itemType()==ItemCate)
        {
           if (selItem->childrenIems().count()!=0)
           {
               return;
           }
            item->setPid(selItem->id());
            addItem(item,selItem);

        }else
        {

            item->setPid(selItem->pid());
            if (selItem==selItem->parent()->childrenIems().last())
            {
               addItem(item,selItem->parent());
            }else
            {
               insertAfterItem(item,selItem,selItem->parent());
            }

        }
        selItem->setSelected(false);
        item->setSelected(true);
        if (selItem!=item)
        {
            emit saveItemData(m_edit->item());
        }
        update();
        QApplication::processEvents();
        showEditor();

    }else if (event->key()==Qt::Key_Backspace)
    {
        if (m_edit->isVisible())
        {
            qDebug()<<m_edit->text();
        }
    }


}

void OutlineView::wheelEvent(QWheelEvent *event)
{
    m_helper->moveTop(event->angleDelta().y());
    QApplication::processEvents();
    showEditor();


}

void OutlineView::onkeyPressBackSpace(OutLineViewItemEdit *edit)
{
    if (edit->isVisible())
    {
        OutLineViewItem *item=edit->item();
        if (item==nullptr)
        {
            return;
        }
        int i=item->parent()->childrenIems().indexOf(item);
        OutLineViewItem *pItem=item->parent();
        pItem->childrenIems().removeOne(item);

        m_items.removeOne(item);
        delete item;
        edit->setHidden(true);
        edit->setItem(nullptr);
        if (pItem->childrenIems().count()==0)
        {

        }
        else if (i<(pItem->childrenIems().count()-1))
        {
            item=pItem->childrenIems().at(i);
            item->setSelected(true);
        }else
        {
            item=pItem->childrenIems().at(pItem->childrenIems().count()-1);
            item->setSelected(true);
        }

        update();
        QApplication::processEvents();
          showEditor();
    }

}

void OutlineView::onMenuActionTriggered(bool checked)
{
    QAction *act=static_cast<QAction*>(sender());
    if (act->text()=="复制子结点")
    {
        OutLineViewItem *selItem=selectedItem();
        if (selItem==nullptr)
        {
            return;
        }
        QString s=selItem->childrenItemsText().join("\n");
        qApp->clipboard()->setText(s);
    }else if (act->text()=="百度选中内容")
    {
        OutLineViewItem *selItem=selectedItem();
        if (selItem==nullptr)
        {
            return;
        }
        QDesktopServices::openUrl(QUrl("https://www.baidu.com/s?wd="+selItem->name()));
    }

}

const QPixmap &OutlineView::urlIcon() const
{
    return m_urlIcon;
}

void OutlineView::setUrlIcon(const QPixmap &newUrlIcon)
{
    m_urlIcon = newUrlIcon;
}
