#ifndef OUTLINEVIEWITEMEDIT_H
#define OUTLINEVIEWITEMEDIT_H

#include <QObject>
#include <QWidget>
#include <QLineEdit>
#include "outlineviewitem.h"
#include <QKeyEvent>

class OutLineViewItemEdit : public QLineEdit
{
    Q_OBJECT
public:
    explicit OutLineViewItemEdit(QWidget *parent = nullptr);

    OutLineViewItem *item() const;
    void setItem(OutLineViewItem *newItem);
signals:
    void keyPressBackSpace(OutLineViewItemEdit *edit);
protected:
    void keyPressEvent(QKeyEvent *event);

signals:
private:
    OutLineViewItem *m_item;

};

#endif // OUTLINEVIEWITEMEDIT_H
