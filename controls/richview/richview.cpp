#include "richview.h"
#include "ui_richview.h"

RichView::RichView(QWidget* parent) :
    QListWidget(parent),
    ui(new Ui::RichView)
{
    ui->setupUi(this);
    setStyleSheet(
        "QListWidget::Item:hover{background:transparent; }"
        "QListWidget::item:selected{background:transparent;}"

    );

    setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    setContextMenuPolicy(Qt::ActionsContextMenu);
    QStringList menuNames;
    menuNames << "在上方插入文本";
    menuNames << "在下方插入文本";
    menuNames << "-";
    menuNames << "在尾部追加文本";
    menuNames << "在尾部追加图像";
    menuNames << "-";
    menuNames << "删除";


    for (int i = 0; i < menuNames.count(); i++)
    {
        QAction* act = new QAction(this);
        if (menuNames[i] == "-")
        {
            act->setSeparator(true);
        }
        else
        {
            act->setText(menuNames[i]);
            connect(act, &QAction::triggered, this, &RichView::onTriggered);
        }
        addAction(act);
    }
}

RichView::~RichView()
{
    delete ui;
}

RichViewItemContainer* RichView::addTextArea(int textHeight)
{
    RichViewTextItem* edt = new RichViewTextItem(this);
    edt->setStyleSheet(R"(
     border:none;
     border-bottom:1px solid rgb(223,223,223);
     font:16px "微软雅黑";
     color:#121212;


    )");
    edt->document()->setDocumentMargin(32);

    connect(edt->document(), &QTextDocument::contentsChanged, this, &RichView::onTextContentsChanged);
    QListWidgetItem* item = new QListWidgetItem(this);
    item->setSizeHint(QSize(0, textHeight));
    addItem(item);
    RichViewItemContainer* c = new RichViewItemContainer(this);
    c->addClietWidget(edt);
    setItemWidget(item, c);
    c->setItem(item);
    return c;

}

RichViewItemContainer* RichView::addImageArea(int imageHeight)
{
    RichViewImageItem* imgWidget = new RichViewImageItem(this);


    QListWidgetItem* item = new QListWidgetItem(this);
    item->setSizeHint(QSize(0, imageHeight));
    addItem(item);
    RichViewItemContainer* c = new RichViewItemContainer(this);
    c->addClietWidget(imgWidget);
    c->setItem(item);
    setItemWidget(item, c);
    return c;

}

void RichView::recalItemHeight(QTextEdit* selEdit)
{
    for (int i = 0; i < count(); i++)
    {
        QListWidgetItem* item = this->item(i);
        RichViewItemContainer* c = dynamic_cast<RichViewItemContainer*>(this->itemWidget(item));
        if (c != nullptr)
        {
            QTextEdit* edt = dynamic_cast<QTextEdit*>(c->clientWidget());
            if (edt != nullptr)
            {
                if (selEdit == edt)
                {
                    item->setSizeHint(QSize(0, edt->height()));
                    return;
                }
            }
        }

    }

}

void RichView::recalAllItemHeight()
{
    for (int i = 0; i < count(); i++)
    {
        QListWidgetItem* item = this->item(i);

        RichViewItemContainer* c = dynamic_cast<RichViewItemContainer*>(this->itemWidget(item));
        if (c != nullptr)
        {
            QTextEdit* edt = dynamic_cast<QTextEdit*>(c->clientWidget());

            if (edt != nullptr)
            {

                QTextDocument* document = edt->document();
                int Area = document->size().width() * document->size().height();
                //新的高度
                int NewHeight = Area / (this->width() - 32);
                NewHeight = NewHeight < document->size().height() ? document->size().height() + 16 : NewHeight + 16;
                edt->setFixedHeight(NewHeight);
                item->setSizeHint(QSize(0, edt->height()));

            }

        }




    }

}

void RichView::onTextContentsChanged()
{
    QTextDocument* document = qobject_cast<QTextDocument*>(sender()); //拿到信号发送的对象
    if (document)
    {
        QTextEdit* edit = qobject_cast<QTextEdit*>(document->parent()->parent());
        if (edit)
        {
            //计算总面积
            int Area = document->size().width() * document->size().height();
            //新的高度
            int NewHeight = Area / (this->width() - 32);
            NewHeight = NewHeight < document->size().height() ? document->size().height() + 16 : NewHeight + 16;
            edit->setFixedHeight(NewHeight);
            recalItemHeight(edit);

        }
    }





}

void RichView::onTriggered()
{
    QAction* act = static_cast<QAction*>(sender());
    if (act->text() == "在尾部追加文本")
    {
        RichViewItemContainer* c = addTextArea(128);
        QTextEdit* edt = static_cast<QTextEdit*>(c->clientWidget());
        setCurrentItem(c->item());
        edt->setFocus();
    }
    else if (act->text() == "在尾部追加图像")
    {
        RichViewItemContainer* c = addImageArea(768);

        setCurrentItem(c->item());

    }
    else if (act->text() == "删除")
    {
        QListWidgetItem* curItem = currentItem();
        if (curItem == nullptr)
        {
            return;
        }
        RichViewItemContainer* c = static_cast<RichViewItemContainer*>(itemWidget(curItem));

        this->removeItemWidget(curItem);
        delete curItem;
        delete c;

    }


}

void RichView::resizeEvent(QResizeEvent* event)
{
    qDebug() << "reisze";
    recalAllItemHeight();
    QListWidget::resizeEvent(event);


}
