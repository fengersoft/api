#ifndef OUTLINEVIEW_H
#define OUTLINEVIEW_H

#include <QWidget>
#include <QPainter>
#include <QKeyEvent>
#include <QWheelEvent>
#include <QMenu>
#include <QAction>
#include <QClipboard>
#include <QDesktopServices>

#include "../base/widgethelper.h"

#include "outlineviewitem.h"
#include "outlineviewitemedit.h"

namespace Ui {
class OutlineView;
}

class OutlineView : public QWidget
{
    Q_OBJECT

public:
    explicit OutlineView(QWidget *parent = nullptr);
    ~OutlineView();
    void addItem(OutLineViewItem* item,OutLineViewItem *pItem=nullptr);
    void addItem(QString name,OutLineViewItem *pItem=nullptr);
    void insertAfterItem(OutLineViewItem* item,OutLineViewItem* curItem,OutLineViewItem *pItem=nullptr);
    OutLineViewItem* findItemById(int id);
    void drawItems(QPainter &painter,int &t,int l,QList<OutLineViewItem*> &parentItems);
    OutLineViewItem* selectedItem();
    void showEditor();
    void clearItems();
    QList<OutLineViewItem*>& items();
    void quitEdit(bool saveEdit=false);

    const QPixmap &urlIcon() const;
    void setUrlIcon(const QPixmap &newUrlIcon);

signals:
    void saveItemData(OutLineViewItem* item);
    void clickItemIcon(OutLineViewItem* item);

protected:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void wheelEvent(QWheelEvent *event);
private slots:
    void onkeyPressBackSpace(OutLineViewItemEdit* edit);
    void onMenuActionTriggered(bool checked = false);
private:
    Ui::OutlineView *ui;
    QList<OutLineViewItem*> m_items;
    QList<OutLineViewItem*> m_rootItems;
    WidgetHelper* m_helper;
    OutLineViewItemEdit *m_edit;
    QPixmap m_urlIcon;


};

#endif // OUTLINEVIEW_H
