#ifndef ESCAPECONVERTER_H
#define ESCAPECONVERTER_H

#include <QObject>

class EscapeConverter : public QObject
{
    Q_OBJECT
public:
    explicit EscapeConverter(QObject *parent = nullptr);
    QString decode(const QString s);
signals:

};

#endif // ESCAPECONVERTER_H
