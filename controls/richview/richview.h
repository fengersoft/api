#ifndef RICHVIEW_H
#define RICHVIEW_H

#include <QWidget>
#include <QListWidget>
#include <QTextEdit>
#include <QDebug>
#include <QAction>

#include "richviewtextitem.h"
#include "richviewimageitem.h"
#include "richviewitemcontainer.h"

namespace Ui
{
class RichView;
}

class RichView : public QListWidget
{
    Q_OBJECT

public:
    explicit RichView(QWidget* parent = nullptr);
    ~RichView();
    RichViewItemContainer* addTextArea(int textHeight);
    RichViewItemContainer* addImageArea(int imageHeight);

    void recalItemHeight(QTextEdit* selEdit);
    void recalAllItemHeight();
public slots:
    void onTextContentsChanged();
    void onTriggered();
protected:
    void resizeEvent(QResizeEvent* event);
private:
    Ui::RichView* ui;
};

#endif // RICHVIEW_H
