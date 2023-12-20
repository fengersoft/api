#include "fnyearcalendar.h"
#include "ui_fnyearcalendar.h"

FnYearCalendar::FnYearCalendar(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::FnYearCalendar)
{
    ui->setupUi(this);
    m_year = QDate::currentDate().year();
    m_factor = 1.0;
    m_cellWidth = 192.0;
    m_cellHeight = 108.0;
    m_helper = new WidgetHelper(this);
    m_helper->setControl(this);
    m_left = 0;
    m_top = 0;
    initDates();
}

FnYearCalendar::~FnYearCalendar()
{
    delete ui;
}

int FnYearCalendar::year() const
{
    return m_year;
}

void FnYearCalendar::setYear(int newYear)
{
    m_year = newYear;
}

void FnYearCalendar::initDates()
{
    QString monthNames[]
    {
        "一月",
        "二月",
        "三月",
        "四月",
        "五月",
        "六月",
        "七月",
        "八月",
        "九月",
        "十月",
        "十一月",
        "十二月"
    };
    for (int j = 1; j < 13; j++)
    {
        QDate d = QDate(m_year, j, 1);
        {
            FnCalenderData* data = new FnCalenderData();
            data->isSelected = false;
            data->year = m_year;
            data->month = j;
            data->day = 1;
            data->j = j - 1;
            data->i = 0;
            QDate curDate = QDate(m_year, data->month, data->day);
            data->yyyyMMdd = curDate.toString("yyyy-MM-dd");
            data->isNull = false;
            data->shortDateLabel = monthNames[data->j];
            data->backgroundColor = data->isNull ?
                                    QColor(230, 230, 230) : Qt::white;
            data->dataType = "月份";
            m_items << data;
        }

        for (int i = 1; i < 32; i++)
        {
            FnCalenderData* data = new FnCalenderData();
            data->isSelected = false;
            data->year = m_year;
            data->month = j;
            data->day = i;
            data->j = j - 1;
            data->i = i;
            QDate curDate = QDate(m_year, data->month, data->day);
            data->yyyyMMdd = curDate.toString("yyyy-MM-dd");
            data->isNull = i <= d.daysInMonth() ? false : true;
            data->shortDateLabel = QString("%1-%2").
                                   arg(data->month, 2, 10, QLatin1Char('0')).
                                   arg(data->day, 2, 10, QLatin1Char('0'));
            data->backgroundColor = data->isNull ?
                                    QColor(230, 230, 230) : Qt::white;
            data->dataType = "日期";
            m_items << data;
        }
    }

}

void FnYearCalendar::paintEvent(QPaintEvent* event)
{
    int w = m_cellWidth * m_factor;
    int h = m_cellHeight * m_factor;
    QPainter painter;

    painter.begin(this);
    painter.setRenderHints(QPainter::Antialiasing);
    for (int i = 0; i < m_items.count(); i++)
    {
        FnCalenderData* data = m_items.at(i);
        QRectF rc(m_left + (data->i)*w, m_top + (data->j)*h, w, h);
        data->rcf = rc;
        if (rc.left() > width())
        {
            continue;
        }
        else if (rc.right() < 0)
        {
            continue;
        }
        else if (rc.bottom() < 0)
        {
            continue;
        }
        else if (rc.top() > height())
        {
            break;
        }
        QColor backColor = data->backgroundColor;
        if (data->isSelected)
        {
            backColor = QColor(197, 197, 197);
        }
        painter.fillRect(rc, QBrush(backColor));
        painter.drawRect(rc);

        if (data->isNull == false)
        {
            QRect textRc(rc.left() + 6, rc.top(), rc.width() - 6, 16);

            painter.drawText(textRc, data->shortDateLabel, Qt::AlignLeft | Qt::AlignVCenter);

            if (data->num != 0)
            {
                QRect numRc(rc.left(), rc.bottom() - 16, rc.width() - 6, 16);

                painter.drawText(numRc, QString("%1").arg(data->num), Qt::AlignRight | Qt::AlignVCenter);
            }
            int remarkTop = rc.top() + 32;
            for (int j = 0; j < data->remarkNames.count(); j++)
            {
                QRect remarkNameRc(rc.left() + 6, remarkTop, rc.width() - 6, 16);
                if (rc.bottom() - remarkNameRc.bottom() <= 16)
                {
                    break;
                }

                painter.drawText(remarkNameRc, data->remarkNames[j], Qt::AlignLeft | Qt::AlignVCenter);
                remarkTop += 16;
            }

        }


    }
    painter.end();

}

void FnYearCalendar::mouseMoveEvent(QMouseEvent* event)
{
    if (m_helper->mousedownFlag())
    {
        QPoint pt = m_helper->cursorPos();
        QPoint pt0 = m_helper->mouseMovePoint();
        m_left += (pt.x() - pt0.x());
        m_top += (pt.y() - pt0.y());
        m_helper->setMouseMovePoint(pt);
        update();
    }
}

void FnYearCalendar::wheelEvent(QWheelEvent* event)
{
    int d = event->angleDelta().y();
    if (event->modifiers() == Qt::ControlModifier)
    {
        m_top += d;
    }
    else if (event->modifiers() == Qt::ShiftModifier)
    {
        if (d > 0)
        {
            m_factor *= 1.1;
        }
        else
        {
            m_factor *= 0.8;
        }
    }
    else
    {
        m_left += d;
    }

    update();


}

void FnYearCalendar::mouseDoubleClickEvent(QMouseEvent* event)
{
    QPoint pt = m_helper->cursorPos();
    for (int i = 0; i < m_items.count(); i++)
    {
        FnCalenderData* item = m_items.at(i);
        item->isSelected = false;
        if (item->isNull)
        {
            continue;
        }
        if (item->rcf.contains(pt))
        {
            item->isSelected = true;
            emit cellDoubleClick(item);

        }
    }
    update();

}

void FnYearCalendar::mouseReleaseEvent(QMouseEvent* event)
{
    m_helper->startMouseUp();
    if (m_helper->isClicked())
    {
        QPoint pt = m_helper->cursorPos();
        for (int i = 0; i < m_items.count(); i++)
        {
            FnCalenderData* item = m_items.at(i);
            item->isSelected = false;
            if (item->isNull)
            {
                continue;
            }
            if (item->rcf.contains(pt))
            {
                item->isSelected = true;
                emit cellClick(item);

            }
        }
    }
    update();

}

void FnYearCalendar::mousePressEvent(QMouseEvent* event)
{
    m_helper->startMouseDown();

}

float FnYearCalendar::factor() const
{
    return m_factor;
}

void FnYearCalendar::setFactor(float newFactor)
{
    m_factor = newFactor;
}

void FnYearCalendar::updateCellData(std::function<void (FnCalenderData*)> updateEvent)
{
    for (int i = 0; i < m_items.count(); i++)
    {
        FnCalenderData* data = m_items.at(i);
        updateEvent(data);
    }
    update();

}
