#include "outlineviewitemedit.h"

OutLineViewItemEdit::OutLineViewItemEdit(QWidget *parent)
    : QLineEdit{parent}
{
    m_item=nullptr;
    setStyleSheet(R"(
    border:none;
    background-color:rgb(204,232,255);
)");

}

OutLineViewItem *OutLineViewItemEdit::item() const
{
    return m_item;
}

void OutLineViewItemEdit::setItem(OutLineViewItem *newItem)
{
    m_item = newItem;
}

void OutLineViewItemEdit::keyPressEvent(QKeyEvent *event)
{
    if (event->key()==Qt::Key_Backspace)
    {
        QString s=this->text();
        if (s=="")
        {
            emit keyPressBackSpace(this);
        }else
        {
            QLineEdit::keyPressEvent(event);
        }
    }else
    {
          QLineEdit::keyPressEvent(event);
    }


}
