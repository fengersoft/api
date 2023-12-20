#include "fncurvechart.h"
#include "ui_fncurvechart.h"

FnCurveChart::FnCurveChart(QWidget* parent) :
    QWidget(parent),
    ui(new Ui::FnCurveChart)
{
    ui->setupUi(this);
    m_currentIndex = 0;
    m_helper = new WidgetHelper(this);
    m_helper->setControl(this);
}

FnCurveChart::~FnCurveChart()
{
    delete ui;
}

QList<FnChartView*> FnCurveChart::views() const
{
    return m_views;
}

void FnCurveChart::setViews(const QList<FnChartView*>& newViews)
{
    m_views = newViews;
}

void FnCurveChart::addView()
{
    FnChartView* view = new FnChartView(this);
    view->setIndex(m_views.count());
    m_views << view;

}

int FnCurveChart::currentIndex() const
{
    return m_currentIndex;
}

void FnCurveChart::setCurrentIndex(int newCurrentIndex)
{
    m_currentIndex = newCurrentIndex;
}

FnChartView* FnCurveChart::view(int index)
{
    return m_views.at(index);

}

void FnCurveChart::paintEvent(QPaintEvent* event)
{
    QPainter painter;
    painter.begin(this);
    painter.setRenderHints(QPainter::Antialiasing);
    for (int i = 0; i < m_views.count(); i++)
    {
        FnChartView* view = m_views.at(i);
        QRect tagRect(width() - (i + 1) * 116, 21, 100, 24);
        view->setTagRect(tagRect);
        QRect btnRc(tagRect.left(), tagRect.top(), 24, 24);
        painter.fillRect(btnRc, QBrush(view->color()));
        painter.setPen(view->color());
        QRect btnTextRc(tagRect.left() + 32, tagRect.top(), tagRect.width() - 32, 24);
        painter.drawText(btnTextRc, view->caption(), Qt::AlignLeft | Qt::AlignVCenter);

        if (view->index() != m_currentIndex)
        {
            continue;
        }
        painter.setPen(view->color());
        painter.drawLine(64, 64, 64, height() - 64);
        painter.drawLine(64, height() - 64, width(), height() - 64);
        int t = height() - 64;
        int s = view->minValue();
        int hh = (height() - 128) / ((view->maxValue() - view->minValue()) / 10);

        while (s <= view->maxValue())
        {
            QRect yLabelRc(0, t - 12, 48, 24);
            painter.drawText(yLabelRc, QString("%1").arg(s), Qt::AlignRight | Qt::AlignVCenter);
            s = s + 10;
            t = t - hh;
        }
        for (int j = 0; j < view->values()->values.count(); j++)
        {
            FnChartYValue* value = view->values()->values.at(j);
            value->setX(32 + (j + 2) * 32);
            double factor = (height() - 128) / (view->maxValue() - view->minValue());
            int y = height() - 64 - ((value->value() - view->minValue()) * factor);
            value->setY(y);
            QPoint pt = value->point();
            painter.drawPoint(pt);
            QRect textRc(pt.x() - 16, height() - 64, 32, 32);

            painter.drawText(textRc,  Qt::AlignCenter, value->caption());
        }
        painter.save();
        QRect clipRc(64, 64, width() - 64, height());
        painter.setClipRect(clipRc);
        if (view->values()->values.count() > 2)
        {
            QPainterPath path;
            path.moveTo(view->values()->values.at(0)->point());
            for (int j = 0; j < view->values()->values.count() - 1; j++)
            {
                QPointF sp = view->values()->values.at(j)->point();
                QPointF ep = view->values()->values.at(j + 1)->point();
                QPointF c1 = QPointF((sp.x() + ep.x()) / 2, sp.y());
                QPointF c2 = QPointF((sp.x() + ep.x()) / 2, ep.y());

                path.cubicTo(c1, c2, ep);
            }
            painter.drawPath(path);
        }
        painter.restore();


    }
    painter.end();


}

void FnCurveChart::mousePressEvent(QMouseEvent* event)
{
    QPoint pt = m_helper->cursorPos();
    for (int i = 0; i < m_views.count(); i++)
    {
        FnChartView* view = m_views.at(i);
        QRect rect = view->tagRect();
        if (rect.contains(pt))
        {
            m_currentIndex = i;
            update();
            break;
        }
    }


}
