#ifndef PDFSPLITER_H
#define PDFSPLITER_H

#include <QObject>
#include "../base/abstractspliter.h"
#include "QtPdfium/pdfium/qpdfium.h"
#include <QApplication>
#include <QFile>

class PdfSpliter : public QObject, public AbstractSpliter
{
    Q_OBJECT
public:
    explicit PdfSpliter(QObject* parent = nullptr);
    void  split();
signals:

};

#endif // PDFSPLITER_H
