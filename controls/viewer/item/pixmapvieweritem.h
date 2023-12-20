#ifndef PIXMAPVIEWITEM_H
#define PIXMAPVIEWITEM_H

#include <QPainter>
#include <QPixmap>
#include <QWidget>

namespace Ui {
class PixmapViewerItem;
}

class PixmapViewerItem : public QWidget {
    Q_OBJECT

public:
    explicit PixmapViewerItem(QWidget* parent = nullptr);
    ~PixmapViewerItem();
    void paintEvent(QPaintEvent* event);

    int id() const;
    void setId(int id);

    QPixmap pixmap() const;
    void setPixmap(const QPixmap& pixmap);

private:
    Ui::PixmapViewerItem* ui;
    int m_id;
    QPixmap m_pixmap;
};

#endif // PIXMAPVIEWITEM_H
