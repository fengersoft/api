
#ifndef CODEANALYSE_H
#define CODEANALYSE_H


#include <QObject>
#include "codelang.h"

QString getValueFromCode(QString code, QString ch = "'");

bool getCodeParams(QString code, QString& key, QString& value, CodeLang lang);



#endif // CODEANALYSE_H
