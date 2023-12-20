#include "binarray.h"

BinArray::BinArray(QObject* parent)
    : QObject{parent}
{
    m_len = 16;

}

int BinArray::input() const
{
    return m_input;
}

void BinArray::setInput(int newInput)
{
    m_input = newInput;
    m_bin = QString("%1").arg(QString::number(m_input, 2), m_len, QLatin1Char('0'));
}

QString BinArray::bin() const
{
    return m_bin;
}

void BinArray::setBin(const QString& newBin)
{
    m_bin = newBin;
}

int BinArray::len() const
{
    return m_len;
}

void BinArray::setLen(int newLen)
{
    m_len = newLen;
}

int BinArray::binIndex(int i)
{
    return m_bin.indexOf(i);

}

bool BinArray::binIndexAsBool(int i)
{

}
