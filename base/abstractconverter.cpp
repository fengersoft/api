#include "abstractconverter.h"

AbstractConverter::AbstractConverter()
{

}

const QString &AbstractConverter::srcPath() const
{
    return m_srcPath;
}

void AbstractConverter::setSrcPath(const QString &newSrcPath)
{
    m_srcPath = newSrcPath;
}

const QString &AbstractConverter::destPath() const
{
    return m_destPath;
}

void AbstractConverter::convert()
{

}
