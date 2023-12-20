#ifndef ABSTRACTCONVERTER_H
#define ABSTRACTCONVERTER_H
#include <QObject>

class AbstractConverter
{
public:
    AbstractConverter();
    const QString& srcPath() const;
    void setSrcPath(const QString& newSrcPath);

    const QString& destPath() const;
    virtual void convert();
protected:
    QString m_srcPath;
    QString m_destPath;

};

#endif // ABSTRACTCONVERTER_H
