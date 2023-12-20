#ifndef TEXT2PDFCONVERTER_H
#define TEXT2PDFCONVERTER_H

#include "qcolor.h"
#include <QObject>
#include "../file/ioutils.h"
#include <QPrinter>
#include <QPainter>
#include <QApplication>
#include <cmath>

class Text2PdfConverter : public QObject
{
    Q_OBJECT
public:
    explicit Text2PdfConverter(QObject* parent = nullptr);

    const QString& srcPath() const;

    const QString& destPath() const;
    void setDestPath(const QString& newDestPath);

    const QColor& backColor() const;
    void startConvert();
    QStringList stringToStringList(QString s, int maxLen);

    void setSrcPath(const QString& newSrcPath);

signals:
private:
    QString m_srcPath;
    QString m_destPath;
    QColor m_backColor;

};

#endif // TEXT2PDFCONVERTER_H
