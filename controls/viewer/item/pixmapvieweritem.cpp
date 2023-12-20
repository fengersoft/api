#include "pixmapvieweritem.h"
#include "ui_pixmapvieweritem.h"

PixmapViewerItem::PixmapViewerItem(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::PixmapViewerItem)
{
    ui->setupUi(this);
}

PixmapViewerItem::~PixmapViewerItem()
{
    delete ui;
}

void PixmapViewerItem::paintEvent(QPaintEvent* event)
{
    QPainter painter;
    painter.begin(this);
    painter.fillRect(rect(), QColor(23, 23, 23));
    QPixmap tmp = m_pixmap.scaledToWidth(width(), Qt::SmoothTransformation);
    QRect rc(0, (height() - tmp.height()) / 2, width(), tmp.height());
    painter.drawPixmap(rc, tmp, tmp.rect());
    painter.end();
}

int PixmapViewerItem::id() const
{
    return m_id;
}

void PixmapViewerItem::setId(int id)
{
    m_id = id;
}

QPixmap PixmapViewerItem::pixmap() const
{
    return m_pixmap;
}

void PixmapViewerItem::setPixmap(const QPixmap& pixmap)
{
    m_pixmap = pixmap;
    update();
}
