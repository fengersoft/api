#ifndef FNRICHEDIT_H
#define FNRICHEDIT_H

#include <QWidget>
#include <QInputMethodEvent>
#include <QKeyEvent>
#include <QPainter>
#include <QAction>
#include <QFileDialog>

#include "../base/widgethelper.h"


#include "fnricheditblock.h"


namespace Ui {
class FnRichEdit;
}

class FnRichEdit : public QWidget
{
    Q_OBJECT

public:
    explicit FnRichEdit(QWidget *parent = nullptr);
    ~FnRichEdit();
    void deSelectAll();
    FnRichEditBlock *blockInPoint(QPoint pt);
    void deleteSelected();
public slots:
    void onActionTriggered();

protected:
    void mousePressEvent(QMouseEvent *event);
      void inputMethodEvent(QInputMethodEvent *event);
      void keyPressEvent(QKeyEvent *event);
      void paintEvent(QPaintEvent *event);
      void mouseMoveEvent(QMouseEvent *event);
       void mouseReleaseEvent(QMouseEvent *event);
      int selectBlockCount();
       FnRichEditBlock* addCommit(QString s,FnRichEditBlockType blockType,bool isLetter=false);
private:
    Ui::FnRichEdit *ui;
    QList<FnRichEditBlock*> m_blocks;
    FnRichEditBlock* m_cursorBlock;
    WidgetHelper *m_helper;
    FnRichEditBlockInsertPos m_insertPos;
};

#endif // FNRICHEDIT_H
