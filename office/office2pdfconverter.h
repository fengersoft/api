#ifndef OFFICE2PDFCONVERTER_H
#define OFFICE2PDFCONVERTER_H

#include <QObject>

class Office2PdfConverter : public QObject
{
    Q_OBJECT
public:
    explicit Office2PdfConverter(QObject *parent = nullptr);

signals:

};

#endif // OFFICE2PDFCONVERTER_H
