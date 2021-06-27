#ifndef IOUTILS_H
#define IOUTILS_H

#include <QObject>
#include <QFile>
#include <QTextCodec>
#include <QDebug>

QString readString(QByteArray data);
QString readString(QString filePath);
#endif // IOUTILS_H
