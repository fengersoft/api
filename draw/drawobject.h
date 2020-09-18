#ifndef DRAWOBJECT_H
#define DRAWOBJECT_H

#include <QObject>
#include <QPainter>
class DrawObject : public QObject
{
    Q_OBJECT
public:
    explicit DrawObject(QObject* parent = nullptr);
    void retSetPoints(QPoint& pt1, QPoint& pt2);


signals:

private:



};

#endif // DRAWOBJECT_H
