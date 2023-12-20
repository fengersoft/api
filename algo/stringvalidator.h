#ifndef STRINGVALIDATOR_H
#define STRINGVALIDATOR_H

#include <QObject>
#include <QString>
#include <QByteArray>


bool isEnglish(QString str);
bool isNumber(QString str);
bool isChinese(QString str);


#endif // STRINGVALIDATOR_H
