
#include "codeanalyse.h"




bool getCodeParams(QString code, QString& key, QString& value, CodeLang lang)
{
    if (lang == CodeLang::LangDelphi)
    {
        code = code.replace(";", "");
        int n = code.indexOf(":=");
        if (n < 0)
        {
            return false;
        }
        int m = code.indexOf("'");
        if (m < 0)
        {
            return false;
        }

        if (n < m)
        {
            QString s0 = code.left(n);
            QString s1 = getValueFromCode(code);
            key = s0.trimmed();
            value = s1.trimmed();
        }
        else
        {
            QString s0 = code.mid(n + 2);
            QString s1 = getValueFromCode(code);
            key = s1.trimmed();
            value = s0.trimmed();
        }
        return true;

    }
    return false;
}

QString getValueFromCode(QString code, QString ch)
{
    int n = code.indexOf(ch);
    if (n < 0)
    {
        return "";
    }
    code = code.mid(n + 1);
    n = code.indexOf(ch);
    if (n < 0)
    {
        return "";
    }
    return code.left(n);











}
