#ifndef RICHVIEWTEXTITEM_H
#define RICHVIEWTEXTITEM_H

#include <QWidget>
#include <QTextEdit>


namespace Ui
{
class RichViewTextItem;
}

class RichViewTextItem : public QTextEdit
{
    Q_OBJECT

public:
    explicit RichViewTextItem(QWidget* parent = nullptr);
    ~RichViewTextItem();

private:
    Ui::RichViewTextItem* ui;
};

#endif // RICHVIEWTEXTITEM_H
