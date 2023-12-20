#ifndef STRINGCOMPARE_H
#define STRINGCOMPARE_H

#include <QObject>

class StringCompare : public QObject
{
    Q_OBJECT
public:
    explicit StringCompare(QObject *parent = nullptr);

    const QString &value1() const;
    void setValue1(const QString &newValue1);

    const QString &value2() const;
    void setValue2(const QString &newValue2);
    int sameNumber();

signals:
private:
    QString m_value1;
    QString m_value2;

};

#endif // STRINGCOMPARE_H
