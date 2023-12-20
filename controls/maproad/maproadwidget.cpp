#include "maproadwidget.h"
#include "ui_maproadwidget.h"

MapRoadWidget::MapRoadWidget(QWidget* parent) :
    QWidget(parent),
    ui(new Ui::MapRoadWidget)
{
    ui->setupUi(this);
    m_helper = new WidgetHelper(this);
    m_helper->setControl(this);
    setMouseTracking(true);
}

MapRoadWidget::~MapRoadWidget()
{
    delete ui;
}

void MapRoadWidget::getStartPoint()
{
    QPoint curPt = m_helper->cursorPos();
    m_startPoint = nullptr;
    for (int i = 0; i < m_points.count(); i++)
    {
        MapRoadPoint* point = m_points.at(i);
        if (point->rect().contains(curPt))
        {
            m_startPoint = point;
            m_movePoint = QPoint(m_startPoint->x(), m_startPoint->y());
            break;
        }
    }

}

void MapRoadWidget::getEndPoint()
{
    QPoint curPt = m_helper->cursorPos();
    m_endPoint = nullptr;
    for (int i = 0; i < m_points.count(); i++)
    {
        MapRoadPoint* point = m_points.at(i);
        if (point->rect().contains(curPt))
        {
            m_endPoint = point;
            break;
        }
    }
}

void MapRoadWidget::paintEvent(QPaintEvent* event)
{
    QPainter painter;
    painter.begin(this);

    painter.setRenderHints(QPainter::Antialiasing);
    if (!m_backgroundImage.isNull())
    {
        painter.drawPixmap(0, 0, m_backgroundImage);
    }

    qDebug() << m_lines.count() << m_points.count();

    for (int i = 0; i < m_lines.count(); i++)
    {
        MapRoadLine* line = m_lines.at(i);
        QPainterPath path;
        path.moveTo(QPoint(line->startPoint()->x(), line->startPoint()->y()));
        QPoint pt1((line->startPoint()->x() + line->endPoint()->x()) / 2, line->startPoint()->y());
        QPoint pt2((line->startPoint()->x() + line->endPoint()->x()) / 2, line->endPoint()->y());
        path.cubicTo(pt1, pt2, QPoint(line->endPoint()->x(), line->endPoint()->y()));

        painter.drawPath(path);


    }

    if (m_startPoint != nullptr)
    {
        QPainterPath path;
        path.moveTo(QPoint(m_startPoint->x(), m_startPoint->y()));
        QPoint pt1((m_startPoint->x() + m_movePoint.x()) / 2, m_startPoint->y());
        QPoint pt2((m_startPoint->x() + m_movePoint.x()) / 2, m_movePoint.y());
        path.cubicTo(pt1, pt2, QPoint(m_movePoint.x(), m_movePoint.y()));

        painter.drawPath(path);

    }
    painter.setBrush(QBrush(Qt::black));
    for (int i = 0; i < m_points.count(); i++)
    {
        MapRoadPoint* point = m_points.at(i);
        painter.drawEllipse(QPoint(point->x(), point->y()), 6, 6);
        qDebug() << point->x() << point->y();
        point->setRect(QRect(point->x() - 3, point->y() - 3, 6, 6));

    }
    painter.end();

}

void MapRoadWidget::mousePressEvent(QMouseEvent* event)
{
    QPoint curPt = m_helper->cursorPos();
    if (qApp->keyboardModifiers() == Qt::ControlModifier)
    {
        MapRoadPoint* point = new MapRoadPoint(this);
        point->addPoint(curPt.x(), curPt.y());
        m_points << point;
    }
    else if (qApp->keyboardModifiers() == Qt::ShiftModifier)
    {
        getStartPoint();
        qDebug() << m_startPoint;

    }

    update();


}

void MapRoadWidget::mouseReleaseEvent(QMouseEvent* event)
{
    if (qApp->keyboardModifiers() == Qt::ShiftModifier)
    {

        if (m_startPoint == nullptr)
        {
            qDebug() << m_startPoint;
            return;
        }
        getEndPoint();
        if (m_endPoint == nullptr)
        {
            m_startPoint = nullptr;
            update();
            return;
        }
        MapRoadLine* line = new MapRoadLine(this);
        line->setStartPoint(m_startPoint);
        line->setEndPoint(m_endPoint);
        m_lines << line;
        m_startPoint = nullptr;
        m_endPoint = nullptr;


    }
    update();

}

void MapRoadWidget::mouseMoveEvent(QMouseEvent* event)
{
    if (qApp->keyboardModifiers() == Qt::ShiftModifier)
    {
        m_movePoint = m_helper->cursorPos();

    }
    update();

}

const QPixmap& MapRoadWidget::backgroundImage() const
{
    return m_backgroundImage;
}

void MapRoadWidget::setBackgroundImage(const QPixmap& newBackgroundImage)
{
    m_backgroundImage = newBackgroundImage;
}
