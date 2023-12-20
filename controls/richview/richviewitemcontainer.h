#ifndef RICHVIEWITEMCONTAINER_H
#define RICHVIEWITEMCONTAINER_H

#include <QWidget>
#include <QListWidget>
#include "../base/fnwidgetapi.h"

namespace Ui
{
class RichViewItemContainer;
}

class RichViewItemContainer : public QWidget
{
    Q_OBJECT

public:
    explicit RichViewItemContainer(QWidget* parent = nullptr);
    ~RichViewItemContainer();
    void addClietWidget(QWidget* w);
    QWidget* clientWidget();



    QListWidgetItem *item() const;
    void setItem(QListWidgetItem *newItem);

private:
    Ui::RichViewItemContainer* ui;
    QWidget* m_clientWidget;
    QListWidgetItem* m_item;
};

#endif // RICHVIEWITEMCONTAINER_H
