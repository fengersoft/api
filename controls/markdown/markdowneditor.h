#ifndef MARKDOWNEDITOR_H
#define MARKDOWNEDITOR_H

#include <QWidget>
#include "../base/widgethelper.h"
#include "markdownline.h"
#include <QList>
#include <QColor>
#include "markdownlineedit.h"

namespace Ui
{
class MarkdownEditor;
}

class MarkdownEditor : public QWidget
{
    Q_OBJECT

public:
    explicit MarkdownEditor(QWidget* parent = nullptr);
    ~MarkdownEditor();
    const QColor& backgroundColor() const;
    void setBackgroundColor(const QColor& newBackgroundColor);
    void loadFromFile(QString path);
public slots:
    void onAddNewLine(MarkdownLine* oldLine);

protected:
    void paintEvent(QPaintEvent* event);
    void mouseDoubleClickEvent(QMouseEvent* event);
    void mousePressEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    void wheelEvent(QWheelEvent* event);
private:
    Ui::MarkdownEditor* ui;
    WidgetHelper* m_helper;
    QColor m_backgroundColor;
    QList<MarkdownLine*> m_markdownLines;
    MarkdownLineEdit* m_lineEdit;
};

#endif // MARKDOWNEDITOR_H
