#ifndef MAPROADPOINT_H
#define MAPROADPOINT_H

#include <QObject>
#include <QRect>

class MapRoadPoint : public QObject
{
    Q_OBJECT
public:
    explicit MapRoadPoint(QObject* parent = nullptr);
    void addPoint(int x, int y);
    int x() const;
    void setX(int newX);

    int y() const;
    void setY(int newY);

    const QRect &rect() const;
    void setRect(const QRect &newRect);

signals:
private:
    int m_x;
    int m_y;
    QString m_caption;
    QRect m_rect;

};

#endif // MAPROADPOINT_H
