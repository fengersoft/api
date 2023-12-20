#ifndef IMAGEPROCVIEWERLIST_H
#define IMAGEPROCVIEWERLIST_H

#include <QWidget>
#include <QWheelEvent>
#include "../base/widgethelper.h"
#include "./history/imageprochistoryobject.h"
#include "../base/verticalscrollbar.h"
#include <QWheelEvent>

namespace Ui
{
class ImageProcViewerList;
}
class ImageProcHistoryObject;
class ImageProcViewerList : public QWidget
{
    Q_OBJECT

public:
    explicit ImageProcViewerList(QWidget* parent = nullptr);
    ~ImageProcViewerList();
    QList<ImageProcHistoryObject*> procHistoryList;
    ImageProcHistoryObject* selObj;
protected:
    void paintEvent(QPaintEvent* event);
    void mousePressEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);
    void mouseDoubleClickEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    void wheelEvent(QWheelEvent* event);
private:
    Ui::ImageProcViewerList* ui;
    WidgetHelper* m_helper;
    VerticalScrollBar* m_scrollBar;


};

#endif // IMAGEPROCVIEWERLIST_H
