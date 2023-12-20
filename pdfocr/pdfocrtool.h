
#ifndef PDFOCRTOOL_H
#define PDFOCRTOOL_H


#include <QObject>
#include <QWidget>
#include <QApplication>
#include  <QDebug>
#include <QtPdfium/pdfium/qpdfium.h>
#include "../ocr/ocrapi.h"


class PdfOcrTool : public QObject
{
    Q_OBJECT
public:
    explicit PdfOcrTool(QObject* parent = nullptr);

    QString filePathName() const;
    void setFilePathName(const QString& newFilePathName);
    void loadFromFilePathName(QString pathName);

    QStringList& pageTextInfos() ;

signals:
    void progress(int i, int n);
private:
    QString m_filePathName;
    QStringList m_pageTextInfos;

};

#endif // PDFOCRTOOL_H
