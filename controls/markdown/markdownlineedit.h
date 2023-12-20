#ifndef MARKDOWNLINEEDIT_H
#define MARKDOWNLINEEDIT_H


#include "qobjectdefs.h"
#include "qwidget.h"
#include <QObject>
#include <QLineEdit>
#include <QDebug>
#include <QKeyEvent>

#include <QLineEdit>
#include "markdownline.h"

class MarkdownLineEdit : public QLineEdit
{
    Q_OBJECT
public:
    explicit MarkdownLineEdit(QWidget* parent = nullptr);



    MarkdownLine* markdownLine() const;
    void setMarkdownLine(MarkdownLine* newMarkdownLine);
    void showEdit(MarkdownLine* newMarkdownLine);
    void hideEdit();
signals:
    void addNewLine(MarkdownLine* oldLine);
protected:
    void keyPressEvent(QKeyEvent* event) override;
signals:
private:
    MarkdownLine* m_markdownLine;

};

#endif // MARKDOWNLINEEDIT_H
