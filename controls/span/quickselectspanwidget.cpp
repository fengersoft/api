#include "quickselectspanwidget.h"
#include "qalgorithms.h"
#include "qbrush.h"
#include "qcolor.h"
#include "qdatetime.h"
#include "qfontmetrics.h"
#include "qglobal.h"
#include "qnamespace.h"
#include "qpainter.h"
#include "qpen.h"
#include "qpoint.h"
#include "spanbutton.h"
#include "ui_quickselectspanwidget.h"
#include <cerrno>

QuickSelectSpanWidget::QuickSelectSpanWidget(QWidget* parent) :
    QWidget(parent),
    ui(new Ui::QuickSelectSpanWidget)
{
    ui->setupUi(this);
    m_helper = new WidgetHelper(this);
    m_helper->setControl(this);
    setMouseTracking(true);
    m_spanType = QuickSelectSpanType::QsDate;
    addButtons();
}

QuickSelectSpanWidget::~QuickSelectSpanWidget()
{
    delete ui;
}

const QDate& QuickSelectSpanWidget::startDate() const
{
    return m_startDate;
}

void QuickSelectSpanWidget::setStartDate(const QDate& newStartDate)
{
    m_startDate = newStartDate;
}

const QDate& QuickSelectSpanWidget::endDate() const
{
    return m_endDate;
}

void QuickSelectSpanWidget::setEndDate(const QDate& newEndDate)
{
    m_endDate = newEndDate;
}

void QuickSelectSpanWidget::addButtons()
{
    qDeleteAll(m_buttons);
    m_buttons.clear();
    QStringList names;
    names.clear();
    if (m_spanType == QuickSelectSpanType::QsDate)
    {
        names << "昨天";
        names << "今天";
        names << "明天";
        names << "上周";
        names << "上周工作日";
        names << "上周末";
        names << "本周";
        names << "本周工作日";
        names << "本周末";
        names << "下周";
        names << "下周工作日";
        names << "下周末";
        names << "上月";
        names << "本月";
        names << "下月";
    }
    else
    {
        names << "1分钟后";
        names << "5分钟后";
        names << "10分钟后";
        names << "15分钟后";
        names << "30分钟后";
        names << "45分钟后";
        names << "1小时后";
        names << "2小时后";
    }

    for (int i = 0; i < names.count(); i++)
    {
        SpanButton* btn = new SpanButton(this);
        btn->setCaption(names[i]);
        m_buttons << btn;
    }
    update();

}

void QuickSelectSpanWidget::calSpan(QString caption, bool bDblClick)
{

    QDate today = QDate::currentDate();
    QDateTime curTime = QDateTime::currentDateTime();
    int n = today.dayOfWeek();
    if (caption == "昨天")
    {
        m_startDate = today.addDays(-1);
        m_endDate = today.addDays(-1);
    }
    else if (caption == "今天")
    {
        m_startDate = today;
        m_startDate = today;
    }
    else if (caption == "明天")
    {
        m_startDate = today.addDays(1);
        m_endDate = today.addDays(1);
    }
    else if (caption == "上周")
    {
        m_endDate = today.addDays(-n);
        m_startDate = m_endDate.addDays(-6);
    }
    else if (caption == "上周工作日")
    {
        m_endDate = today.addDays(-n - 2);
        m_startDate = m_endDate.addDays(-4);

    }
    else if (caption == "上周末")
    {
        m_endDate = today.addDays(-n);
        m_startDate = m_endDate.addDays(-1);

    }
    else if (caption == "本周")
    {
        m_startDate = today.addDays(1 - n);
        m_endDate = m_startDate.addDays(6);

    }
    else if (caption == "本周工作日")
    {
        m_startDate = today.addDays(1 - n);
        m_endDate = m_startDate.addDays(4);

    }
    else if (caption == "本周末")
    {
        m_startDate = today.addDays(6 - n);
        m_endDate = m_startDate.addDays(1);

    }
    else if (caption == "下周")
    {
        m_startDate = today.addDays(8 - n);
        m_endDate = m_startDate.addDays(6);

    }
    else if (caption == "下周工作日")
    {
        m_startDate = today.addDays(8 - n);
        m_endDate = m_startDate.addDays(4);

    }
    else if (caption == "下周末")
    {
        m_startDate = today.addDays(13 - n);
        m_endDate = m_startDate.addDays(1);

    }
    else if (caption == "上月")
    {
        m_startDate = today.addMonths(-1);
        m_startDate.setDate(m_startDate.year(), m_startDate.month(), 1);
        m_endDate = m_startDate.addDays(m_startDate.daysInMonth() - 1);

    }
    else if (caption == "本月")
    {
        m_startDate = today;
        m_startDate.setDate(m_startDate.year(), m_startDate.month(), 1);
        m_endDate = m_startDate.addDays(m_startDate.daysInMonth() - 1);

    }
    else if (caption == "下月")
    {
        m_startDate = today.addMonths(1);
        m_startDate.setDate(m_startDate.year(), m_startDate.month(), 1);
        m_endDate = m_startDate.addDays(m_startDate.daysInMonth() - 1);

    }
    else if (caption == "1分钟后")
    {
        afterMinutes(1);

    }
    else if (caption == "5分钟后")
    {
        afterMinutes(5);

    }
    else if (caption == "10分钟后")
    {
        afterMinutes(10);

    }
    else if (caption == "15分钟后")
    {
        afterMinutes(15);

    }
    else if (caption == "30分钟后")
    {
        afterMinutes(30);

    }
    else if (caption == "45分钟后")
    {
        afterMinutes(45);

    }
    else if (caption == "1小时后")
    {
        afterMinutes(60);

    }
    else if (caption == "2小时后")
    {
        afterMinutes(120);

    }



    if (m_spanType == QuickSelectSpanType::QsDate)
    {
        if (bDblClick)
        {
            emit doubleClickSpanButton(caption, m_startDate, m_endDate);

        }
        else
        {
            emit clickSpanButton(caption, m_startDate, m_endDate);
        }
        qDebug() << m_startDate << m_endDate;
    }
    else
    {
        if (bDblClick)
        {
            emit doubleClickSpanTimeButton(caption, m_startDateTime, m_endDateTime, m_afterMinutes);

        }
        else
        {
            emit clickSpanTimeButton(caption, m_startDateTime, m_endDateTime, m_afterMinutes);
            qDebug() << m_startDateTime << m_endDateTime << m_afterMinutes;
        }

    }


}

void QuickSelectSpanWidget::paintEvent(QPaintEvent* event)
{
    Q_UNUSED(event);
    QPoint curPt = m_helper->cursorPos();
    QPainter painter;
    painter.begin(this);
    painter.setRenderHints(QPainter::Antialiasing);
    int l = 6;
    int t = (height() - 24) / 2;
    QFontMetrics fm = painter.fontMetrics();
    for (int i = 0; i < m_buttons.count(); i++)
    {
        SpanButton* btn = m_buttons.at(i);

        QRect btnRc(l, t, fm.boundingRect(btn->caption()).width() + 24, 24);
        btn->setRect(btnRc);

        QPen pen = painter.pen();
        pen.setWidthF(0.5);
        if (btnRc.contains(curPt))
        {
            pen.setColor(QColor(0, 120, 212));
            painter.setBrush(QBrush(QColor(224, 238, 249)));
        }
        else
        {
            pen.setColor(QColor(208, 208, 208));
            painter.setBrush(QBrush(QColor(253, 253, 253)));
        }
        painter.setPen(pen);
        painter.drawRoundedRect(btnRc, 12, 12);
        painter.setPen(Qt::black);
        painter.drawText(btnRc, Qt::AlignCenter, btn->caption());
        l += btn->rect().width() + 6;

    }
    painter.end();

}

void QuickSelectSpanWidget::mouseMoveEvent(QMouseEvent* event)
{
    update();

}

void QuickSelectSpanWidget::mousePressEvent(QMouseEvent* event)
{
    QPoint curPt = m_helper->cursorPos();
    for (int i = 0; i < m_buttons.count(); i++)
    {
        SpanButton* btn = m_buttons.at(i);
        if (btn->rect().contains(curPt))
        {
            qDebug() << btn->caption();
            calSpan(btn->caption());

            break;
        }
    }

}

void QuickSelectSpanWidget::mouseDoubleClickEvent(QMouseEvent* event)
{
    QPoint curPt = m_helper->cursorPos();
    for (int i = 0; i < m_buttons.count(); i++)
    {
        SpanButton* btn = m_buttons.at(i);
        if (btn->rect().contains(curPt))
        {
            qDebug() << btn->caption();
            calSpan(btn->caption(), true);
            break;
        }
    }

}

QuickSelectSpanType QuickSelectSpanWidget::spanType() const
{
    return m_spanType;
}

void QuickSelectSpanWidget::setSpanType(QuickSelectSpanType newSpanType)
{
    m_spanType = newSpanType;
    addButtons();
}

void QuickSelectSpanWidget::afterMinutes(int minutes)
{
    m_startDateTime = QDateTime::currentDateTime();
    m_endDateTime = m_startDateTime.addSecs(minutes * 60);
    m_afterMinutes = minutes;
}
