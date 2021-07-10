#include "fnchart.h"
#include "ui_fnchart.h"

FnChart::FnChart(QWidget* parent) :
    QWidget(parent),
    ui(new Ui::FnChart)
{
    ui->setupUi(this);
    m_helper = new WidgetHelper(this);
    m_helper->setControl(this);
    resetOrigin();

}

FnChart::~FnChart()
{
    delete ui;
}

int FnChart::originX() const
{
    return m_originX;
}

void FnChart::setOriginX(int originX)
{
    m_originX = originX;
}

int FnChart::originY() const
{
    return m_originY;
}

void FnChart::setOriginY(int originY)
{
    m_originY = originY;
}

int FnChart::zoomX() const
{
    return m_zoomX;
}

void FnChart::setZoomX(int zoomX)
{
    m_zoomX = zoomX;
}

int FnChart::zoomY() const
{
    return m_zoomY;
}

void FnChart::resetOrigin()
{
    m_originX = 64;
    m_originY = height() - 32;
    m_xLabelWidth = 120;
    m_startX = m_originX;
    m_startY = m_originY;
    update();
}

void FnChart::addXLabel(QString caption)
{
    FnChartXLabel* xlabel = new FnChartXLabel(this);
    xlabel->setCaption(caption);
    m_xlabels << xlabel;
    update();
}

void FnChart::paintEvent(QPaintEvent* event)
{
    QPainter painter;
    painter.begin(this);
    //绘制线条
    painter.drawLine(0, m_originY, width(), m_originY);
    painter.drawLine(m_originX, height() - 32, m_originX, 0);



    //绘制x轴标签
    QMap<QString, int> labelMap;
    int m = m_startX + m_xLabelWidth;
    for (int i = 0; i < m_xlabels.count(); i++)
    {
        FnChartXLabel* xlabel = m_xlabels.at(i);
        xlabel->setX(m);
        QRect textRc = QRect(m - m_xLabelWidth / 2, m_originY + 6, m_xLabelWidth, 24);
        painter.drawText(textRc, Qt::AlignCenter, xlabel->caption());
        labelMap.insert(xlabel->caption(), m);
        m += m_xLabelWidth;
    }
    //绘制y轴

    for (int i = 0; i < m_series.count(); i++)
    {
        FnChartValues* dataValues = m_series.at(i);
        if (!dataValues->isShow())
            continue;
        QPoint prePt;
        painter.save();
        QPen pen = painter.pen();
        pen.setColor(dataValues->color());
        pen.setWidth(2);
        painter.setPen(pen);
        for (int j = 0; j < dataValues->values.count(); j++)
        {
            FnChartYValue* value = dataValues->values.at(j);
            int y = m_startY - value->value() * 10;
            value->setY(y);
            int x = labelMap[value->caption()];
            value->setX(x);
            if (j == 0)
            {
                prePt = QPoint(x, y);
            }
            else
            {
                QPoint pt = QPoint(x, y);
                QPointF tempPt1 = QPointF((pt.x() + prePt.x()) / 2, prePt.y());
                QPointF tempPt2 = QPointF((pt.x() + prePt.x()) / 2, pt.y());
                QPainterPath path;
                path.moveTo(prePt);
                path.cubicTo(tempPt1, tempPt2, pt);
                painter.drawPath(path);


                prePt = pt;
            }
        }
        painter.restore();
    }
    int t = 16;
    int l = width() - 200;
    for (int i = 0; i < m_series.count(); i++)
    {
        FnChartValues* dataValues = m_series.at(i);

        painter.save();
        QRect rc = QRect(l, t, 24, 24);
        dataValues->setColorRect(rc);
        painter.fillRect(rc, dataValues->isShow() ? dataValues->color() : QColor(197, 197, 197));
        QRect textRc = QRect(l + 36, t, 160, 24);
        painter.setPen(Qt::black);
        painter.drawText(textRc, Qt::AlignLeft | Qt::AlignVCenter, dataValues->caption());

        painter.restore();
        t += 36;

    }
    painter.end();
}

void FnChart::mousePressEvent(QMouseEvent* event)
{

    m_helper->startMouseDown();

}

void FnChart::mouseReleaseEvent(QMouseEvent* event)
{

    m_helper->startMouseUp();
}

void FnChart::mouseMoveEvent(QMouseEvent* event)
{
    if (m_helper->mousedownFlag())
    {
        QPoint pt = m_helper->cursorPos();
        int x = pt.x() - m_helper->mousedownPoint().x();
        int y = pt.y() - m_helper->mousedownPoint().y();
        m_startX += x;
        m_startY += y;
        m_helper->setMousedownPoint(pt);
        update();

    }

}

void FnChart::keyPressEvent(QKeyEvent* event)
{
    if (event->key() == Qt::Key_F5)
    {
        resetOrigin();

    }
}

void FnChart::resizeEvent(QResizeEvent* event)
{
    resetOrigin();
}

void FnChart::mouseDoubleClickEvent(QMouseEvent* event)
{
    QPoint pt = m_helper->cursorPos();
    for (int i = 0; i < m_series.count(); i++)
    {
        FnChartValues* dataValues = m_series.at(i);
        if (dataValues->colorRect().contains(pt))
        {
            dataValues->setIsShow(!dataValues->isShow());
        }

    }
    update();
}

int FnChart::xLabelWidth() const
{
    return m_xLabelWidth;
}

void FnChart::setXLabelWidth(int xLabelWidth)
{
    m_xLabelWidth = xLabelWidth;
}

void FnChart::addChartValues(FnChartValues* values)
{
    m_series << values;
    update();
}
