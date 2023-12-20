#include "iconitemwidget.h"
#include "qbrush.h"
#include "qcolor.h"
#include "qnamespace.h"
#include "qpixmap.h"
#include "qpoint.h"
#include "qwindowdefs.h"
#include "ui_iconitemwidget.h"

IconItemWidget::IconItemWidget(QWidget* parent) :
    QWidget(parent),
    ui(new Ui::IconItemWidget)
{
    ui->setupUi(this);
    setMouseTracking(true);
    m_selected = false;
}

IconItemWidget::~IconItemWidget()
{
    delete ui;
}

const QString& IconItemWidget::path() const
{
    return m_path;
}

void IconItemWidget::setPath(const QString& newPath)
{
    m_path = newPath;
    m_pix = QPixmap(m_path);
}

void IconItemWidget::paintEvent(QPaintEvent* event)
{
    QPoint curPt = cursor().pos();
    curPt = mapFromGlobal(curPt);
    QPainter painter;
    painter.begin(this);
    QRect rc(0, 0, width(), height());
    if ((m_pix.width() < width()) && (m_pix.height() < rc.height()))
    {
        QRect rc2((width() - m_pix.width()) / 2, (height() - m_pix.height()) / 2,
                  m_pix.width(), m_pix.height());
        painter.drawPixmap(rc2, m_pix, m_pix.rect());
    }
    else
    {
        QRect drawRc(2, 2, width() - 4, height() - 4);
        painter.drawPixmap(drawRc, m_pix, m_pix.rect());
    }

    if ((rc.contains(curPt)) || (m_selected))
    {
        painter.setBrush(QBrush(QColor(0, 0, 255, 80)));
        painter.setPen(Qt::NoPen);
        painter.drawRect(rc);

    }
    painter.end();


}

void IconItemWidget::mousePressEvent(QMouseEvent* event)
{
    emit clickItemWidget(this);

}

bool IconItemWidget::selected() const
{
    return m_selected;
}

void IconItemWidget::setSelected(bool newSelected)
{
    m_selected = newSelected;
    update();
}
