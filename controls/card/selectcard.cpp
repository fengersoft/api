#include "selectcard.h"
#include "ui_selectcard.h"

SelectCard::SelectCard(QWidget* parent) :
    QWidget(parent),
    ui(new Ui::SelectCard)
{
    ui->setupUi(this);
}

SelectCard::~SelectCard()
{
    delete ui;
}

void SelectCard::addItem(QString caption, int id)
{
    SelectCardItem* item = new SelectCardItem();
    item->id = id;
    item->caption = caption;
    items << item;
    update();

}

void SelectCard::setSelected(int id)
{
    SelectCardItem* selItem = nullptr;
    for (int i = 0; i < items.count(); i++)
    {
        SelectCardItem* item = items.at(i);
        item->selected = item->id == id;
        if (item->selected)
        {
            selItem = item;

        }
    }
    update();
    if (selItem != nullptr)
    {
        emit onSelected(selItem);
    }
}

bool SelectCard::hasItemId(int id)
{

    for (int i = 0; i < items.count(); i++)
    {
        SelectCardItem* item = items.at(i);
        if (item->id == id)
        {
            return true;
        }

    }
    return false;
}

void SelectCard::mousePressEvent(QMouseEvent* event)
{
    QPoint pt = mapFromGlobal(cursor().pos());
    for (int i = 0; i < items.count(); i++)
    {
        SelectCardItem* item = items.at(i);
        if (item->rect.contains(pt))
        {
            setSelected(item->id);
            return;
        }

    }

}

void SelectCard::updateItemText(int id, QString& s)
{
    for (int i = 0; i < items.count(); i++)
    {
        SelectCardItem* item = items.at(i);
        if (item->id == id)
        {
            item->caption = s;

        }

    }
    update();
}

void SelectCard::deleteItemById(int id)
{
    for (int i = 0; i < items.count(); i++)
    {
        SelectCardItem* item = items.at(i);
        if (item->id == id)
        {
            items.removeAt(i);
            delete  item;
            break;

        }

    }
    update();
}

void SelectCard::paintEvent(QPaintEvent* event)
{
    QPainter painter;
    painter.begin(this);
    int l = 16;

    for (int i = 0; i < items.count(); i++)
    {
        if (i == 0)
        {
            painter.setPen(QColor(197, 197, 197));
            painter.drawLine(0, height(), l, height());
        }
        SelectCardItem* item = items.at(i);
        QFontMetrics fm = painter.fontMetrics();
        int w = fm.width(item->caption);
        item->rect = QRect(l, 0, w + 32, height());
        item->closeRect = QRect();
        if (item->selected)
        {

            painter.fillRect(item->rect, QBrush(QColor(255, 255, 255)));
        }
        else
        {
            painter.fillRect(item->rect, QBrush(QColor(237, 237, 237)));
        }
        //绘制线条
        painter.setPen(QColor(197, 197, 197));
        painter.drawLine(l, 0, l, height());
        painter.setPen(QColor(197, 197, 197));
        painter.drawLine(l, 0, l + w + 32, 0);



        QRect rc;
        rc = QRect(l + 6, 0, w, height());

        painter.setPen(QColor(0, 0, 0));
        painter.drawText(rc, Qt::AlignCenter, item->caption);
        if (item->selected == false)
        {
            painter.setPen(QColor(197, 197, 197));
            painter.drawLine(l, height(), l + w + 32, height());
        }
        l = l + w + 32;
    }
    if (items.count() > 0)
    {
        painter.setPen(QColor(197, 197, 197));
        painter.drawLine(l, 0, l, height());
        painter.drawLine(l, height(), width(), height());
    }


    painter.end();

}
