#include "abstractspliter.h"

AbstractSpliter::AbstractSpliter()
{

}

const QString &AbstractSpliter::srcPath() const
{
    return m_srcPath;
}

void AbstractSpliter::setSrcPath(const QString &newSrcPath)
{
    m_srcPath = newSrcPath;
}

const QString &AbstractSpliter::destFolder() const
{
    return m_destFolder;
}

void AbstractSpliter::split()
{

}

void AbstractSpliter::setDestFolder(const QString &newDestFolder)
{
    m_destFolder = newDestFolder;
}
