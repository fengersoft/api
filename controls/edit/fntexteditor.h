#ifndef FNTEXTEDITOR_H
#define FNTEXTEDITOR_H

#include <QWidget>
#include "fnlinenumber.h"
#include "fnplaintextedit.h"
#include "../base/fnwidgetapi.h"

namespace Ui {
class FnTextEditor;
}

class FnTextEditor : public QWidget
{
    Q_OBJECT

public:
    explicit FnTextEditor(QWidget *parent = nullptr);
    ~FnTextEditor();
private slots:
    void onBlockCountChanged(int newBlockCount);
    void onUpdateRequest(const QRect &rect, int dy);
    void onCursorPositionChanged();
private:
    Ui::FnTextEditor *ui;
    FnLineNumber *m_lineNumber;
    FnPlainTextEdit *m_textEdit;
};

#endif // FNTEXTEDITOR_H
