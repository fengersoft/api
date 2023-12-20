#ifndef ICONITEMWIDGET_H
#define ICONITEMWIDGET_H

#include "qobjectdefs.h"
#include "qpixmap.h"
#include <QWidget>
#include <QPainter>
#include <QDebug>

namespace Ui
{
class IconItemWidget;
}

class IconItemWidget : public QWidget
{
    Q_OBJECT

public:
    explicit IconItemWidget(QWidget* parent = nullptr);
    ~IconItemWidget();

    const QString& path() const;
    void setPath(const QString& newPath);
    bool selected() const;
    void setSelected(bool newSelected);
signals:
    void clickItemWidget(IconItemWidget* w);
protected:
    void paintEvent(QPaintEvent* event);
    void mousePressEvent(QMouseEvent* event);
private:
    Ui::IconItemWidget* ui;
private:
    QString m_path;
    QPixmap m_pix;
    bool m_selected;
};

#endif // ICONITEMWIDGET_H
