#include "markdowneditor.h"
#include "markdownblock.h"
#include "markdownline.h"
#include "markdownlineedit.h"
#include "qalgorithms.h"
#include "qapplication.h"
#include "qbrush.h"
#include "qcolor.h"
#include "qfont.h"
#include "qfontmetrics.h"
#include "qnamespace.h"
#include "qpoint.h"
#include "ui_markdowneditor.h"

MarkdownEditor::MarkdownEditor(QWidget* parent) :
    QWidget(parent),
    ui(new Ui::MarkdownEditor)
{
    ui->setupUi(this);
    setMouseTracking(true);
    m_helper = new WidgetHelper(this);
    m_helper->setControl(this);
    m_backgroundColor = QColor(30, 30, 30);
    m_lineEdit = new MarkdownLineEdit(this);
    m_lineEdit->setHidden(true);
    m_helper->setItemsTop(16);
    m_helper->setMaxTop(16);
    connect(m_lineEdit, &MarkdownLineEdit::addNewLine, this, &MarkdownEditor::onAddNewLine);
}


MarkdownEditor::~MarkdownEditor()
{
    delete ui;
}

void MarkdownEditor::paintEvent(QPaintEvent* event)
{
    QRect clientRc = m_helper->clientRect();
    QPoint curPt = m_helper->cursorPos();
    QPainter painter;
    painter.begin(this);
    painter.fillRect(clientRc, QBrush(m_backgroundColor));
    int t = m_helper->itemsTop();
    for (int i = 0; i < m_markdownLines.count(); i++)
    {
        MarkdownLine* line = m_markdownLines.at(i);
        QString showText = line->showText();
        QFont font = painter.font();
        font.setPointSize(line->fontSize());
        painter.setFont(font);
        QFontMetrics fm = painter.fontMetrics();
        int h = fm.height() + fm.ascent() + fm.descent();
        QRect lineRc(48, t, width() - 96, h);
        painter.setPen(Qt::white);
        line->setRect(lineRc);
        if ((m_lineEdit->isHidden()) && (line->rect().contains(curPt)))
        {
            QRect selRect(lineRc.left() - 12, lineRc.top() + (lineRc.height() - fm.height()) / 2, 8, fm.height());
            painter.fillRect(selRect, QBrush(QColor(120, 120, 120)));
        }
        else if ((!m_lineEdit->isHidden()) && (line == m_lineEdit->markdownLine()))
        {
            QRect selRect(lineRc.left() - 12, m_lineEdit->y(), 8, m_lineEdit->height());
            painter.fillRect(selRect, QBrush(QColor(120, 120, 120)));
        }
        if (line != m_lineEdit->markdownLine())
        {
            if ((line->blocks().count() == 1) && (line->text().indexOf("*") < 0))
            {
                painter.drawText(lineRc, line->showText(), Qt::AlignVCenter | Qt::AlignLeft);
            }
            else
            {
                painter.save();
                painter.setPen(Qt::NoPen);
                painter.drawText(lineRc, line->showText(), Qt::AlignVCenter | Qt::AlignLeft);
                painter.setPen(Qt::white);
                int bt = lineRc.top();
                int bl = lineRc.left();
                h = 0;
                for (int j = 0; j < line->blocks().count(); j++)
                {
                    MarkdownBlock* block = line->blocks().at(j);
                    QFont font = painter.font();
                    font.setBold(block->bold());
                    font.setItalic(block->italic());

                    painter.setFont(font);
                    QString blockText = block->text();
                    QFontMetrics blockFm = painter.fontMetrics();
                    int bh = blockFm.lineSpacing() + font.letterSpacing();
                    h = bh;
                    for (int k = 0; k < blockText.count(); k++)
                    {
                        int bw = blockFm.width(blockText.at(k)) + 2;
                        QRect blockRc(bl, bt, bw, bh);
                        painter.drawText(blockRc, Qt::AlignCenter, blockText.at(k));
                        bl += bw;
                        if (bl > lineRc.right())
                        {
                            bl = lineRc.left();
                            bt += bh;
                            h += bh;
                        }


                    }

                }

                painter.restore();

            }

        }

        t += h + 16;
    }

    painter.end();

}

void MarkdownEditor::mouseDoubleClickEvent(QMouseEvent* event)
{
    if (m_markdownLines.count() == 0)
    {
        MarkdownLine* line = new MarkdownLine(this);
        m_markdownLines << line;
        update();
        QApplication::processEvents();
        m_lineEdit->showEdit(line);
        update();
        return;
    }

    QPoint curPt = m_helper->cursorPos();
    for (int i = 0; i < m_markdownLines.count(); i++)
    {
        MarkdownLine* line = m_markdownLines.at(i);
        if (line->rect().contains(curPt))
        {
            m_lineEdit->showEdit(line);
            update();
            return;
        }
    }

}

void MarkdownEditor::mousePressEvent(QMouseEvent* event)
{
    if (!m_lineEdit->isHidden())
    {
        MarkdownLine* line = m_lineEdit->markdownLine();
        line->setText(m_lineEdit->text());
        m_lineEdit->hideEdit();
        update();
        return;
    }



}

void MarkdownEditor::mouseMoveEvent(QMouseEvent* event)
{
    update();

}

void MarkdownEditor::wheelEvent(QWheelEvent* event)
{
    int d = event->delta();
    m_helper->moveTop(d);

}

const QColor& MarkdownEditor::backgroundColor() const
{
    return m_backgroundColor;
}

void MarkdownEditor::setBackgroundColor(const QColor& newBackgroundColor)
{
    m_backgroundColor = newBackgroundColor;
}

void MarkdownEditor::loadFromFile(QString path)
{
    QFile file(path);
    file.open(QIODevice::ReadOnly);
    QString s = file.readAll();
    QStringList stl = s.split("\n");
    qDeleteAll(m_markdownLines);
    m_markdownLines.clear();
    m_helper->setItemsTop(16);
    m_lineEdit->hide();
    for (int i = 0; i < stl.count(); i++)
    {
        MarkdownLine* line = new MarkdownLine(this);
        line->setText(stl[i]);
        m_markdownLines << line;


    }
    update();

    file.close();

}

void MarkdownEditor::onAddNewLine(MarkdownLine* oldLine)
{
    if (oldLine == m_markdownLines.last())
    {
        oldLine->setText(m_lineEdit->text());
        MarkdownLine* line = new MarkdownLine(this);
        line->setText("");
        m_markdownLines << line;
        update();
        QApplication::processEvents();
        m_lineEdit->showEdit(line);

        update();

    }
    else
    {
        oldLine->setText(m_lineEdit->text());
        MarkdownLine* line = new MarkdownLine(this);
        line->setText("");
        int n = m_markdownLines.indexOf(oldLine) + 1;
        m_markdownLines.insert(n, line);
        update();
        QApplication::processEvents();
        m_lineEdit->showEdit(line);
    }

}
