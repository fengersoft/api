#include "labeledit.h"

LabelEdit::LabelEdit(QWidget* parent) : QLineEdit(parent)
{
    setStyleSheet(R"(border:none;)");
    setAlignment(Qt::AlignCenter);



}

void LabelEdit::hideEdit()
{
    emit changeEditInfo(this->text());
    hide();

}

void LabelEdit::showEdit(QRect rc, QString info)
{
    setHidden(false);
    setGeometry(rc);
    setText(info);
    setFocus();
}

void LabelEdit::judgeShowOrHide(QRect rc, QPoint pt, QString info)
{
    if (rc.contains(pt))
    {

        showEdit(rc, info);
    }
    else
    {
        hideEdit();
    }

}


