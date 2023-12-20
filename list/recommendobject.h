#ifndef RECOMMENDOBJECT_H
#define RECOMMENDOBJECT_H

#include "qdatetime.h"
#include <QObject>
#include <QDateTime>
#include <QRect>
class RecommendObject : public QObject
{
    Q_OBJECT
public:
    explicit RecommendObject(QObject* parent = nullptr);

    const QString& name() const;
    void setName(const QString& newName);





    const QDateTime& latestSelectedTime() const;
    void setLatestSelectedTime(const QDateTime& newLatestSelectedTime);

    int selectedCount() const;
    void setSelectedCount(int newSelectedCount);
    void incSelectedCount();

    const QRect& rect() const;
    void setRect(const QRect& newRect);

signals:
private:
    QString m_name;
    int m_selectedCount;
    QDateTime m_latestSelectedTime;
    QRect m_rect;

};

#endif // RECOMMENDOBJECT_H
