#ifndef BINARRAY_H
#define BINARRAY_H

#include <QObject>

class BinArray : public QObject
{
    Q_OBJECT
public:
    explicit BinArray(QObject* parent = nullptr);

    int input() const;
    void setInput(int newInput);

    QString bin() const;
    void setBin(const QString& newBin);

    int len() const;
    void setLen(int newLen);
    int binIndex(int i);
    bool binIndexAsBool(int i);

signals:
private:
    int m_input;
    QString m_bin;
    int m_len;

};

#endif // BINARRAY_H
