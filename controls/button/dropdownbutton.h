#ifndef DROPDOWNBUTTON_H
#define DROPDOWNBUTTON_H

#include <QWidget>
#include <QPainter>
#include "../base/widgethelper.h"
#include <QStylePainter>
#include <QStyleOptionButton>
#include "../../draw/drawobject.h"
#include <QMenu>

namespace Ui
{
class DropDownButton;
}

class DropDownButton : public QWidget
{
    Q_OBJECT

public:
    explicit DropDownButton(QWidget* parent = nullptr);
    ~DropDownButton();
    const QStringList& dropDownList() const;
    void setDropDownList(const QStringList& newDropDownList);
    const QString& caption() const;
    void setCaption(const QString& newCaption);

public slots:
    void onActionTriggered();
protected:
    void paintEvent(QPaintEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    void leaveEvent(QEvent* event);
    void mousePressEvent(QMouseEvent* event);
private:
    Ui::DropDownButton* ui;
    WidgetHelper* m_helper;
    DrawObject* m_draw;
    QRect m_arrowRect;
    QStringList m_dropDownList;
    QString m_caption;
};

#endif // DROPDOWNBUTTON_H
