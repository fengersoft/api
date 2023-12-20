#ifndef NUMBERFORMATTER_H
#define NUMBERFORMATTER_H

#include <QObject>

class NumberFormatter : public QObject
{
    Q_OBJECT
public:
    explicit NumberFormatter(QObject *parent = nullptr);
    QString numberToChinese(int n);

signals:

};

#endif // NUMBERFORMATTER_H
