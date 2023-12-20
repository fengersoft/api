#ifndef ABSTRACTSPLITER_H
#define ABSTRACTSPLITER_H

#include <QObject>

class AbstractSpliter
{
public:
    AbstractSpliter();
    const QString& srcPath() const;
    void setSrcPath(const QString& newSrcPath);

    const QString& destFolder() const;
    virtual void split();

    void setDestFolder(const QString &newDestFolder);

protected:
    QString m_srcPath;
    QString m_destFolder;
};

#endif // ABSTRACTSPLITER_H
