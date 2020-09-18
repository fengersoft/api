#ifndef SELECTCARD_H
#define SELECTCARD_H

#include <QWidget>
#include <QPainter>
#include <QDebug>

namespace Ui
{
class SelectCard;
}
struct SelectCardItem
{
    QString caption;
    int id;
    QRect rect;
    QRect closeRect;
    bool selected = false;
};

class SelectCard : public QWidget
{
    Q_OBJECT

public:
    explicit SelectCard(QWidget* parent = nullptr);
    ~SelectCard();
    void addItem(QString name, int id);
    void setSelected(int id);
    bool hasItemId(int id);
    void mousePressEvent(QMouseEvent* event);
signals:
    void onSelected(SelectCardItem* item);
protected:
    void paintEvent(QPaintEvent* event);
private:
    Ui::SelectCard* ui;
    QList<SelectCardItem*> items;
};

#endif // SELECTCARD_H
