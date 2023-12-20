#include "codeparser.h"

CodeParser::CodeParser(QObject* parent)
    : QObject{parent}
{

}

const QString& CodeParser::statement() const
{
    return m_statement;
}

void CodeParser::setStatement(const QString& newStatement)
{
    m_statement = newStatement;
    QString s = m_statement.trimmed();

    if (s.startsWith("//#"))
    {
        int m = s.indexOf("//#");
        m_tableName = s.mid(m + 3).trimmed();

    }
    if (s.startsWith("///"))
    {
        int m = s.indexOf("///");
        m_className = s.mid(m + 3).trimmed();

    }
    else
    {
        int m = s.indexOf(" ");
        m_dateType = s.left(m).trimmed();
        s = s.mid(m + 1);
        int n = s.indexOf("=");
        m_varibleName = s.left(n).trimmed();
        s = s.mid(n + 1);
        int p = s.indexOf(";");
        m_value = s.left(p).trimmed();
        if (m_value.startsWith("\""))
        {
            m_value = m_value.mid(1);
        }

        if (m_value.endsWith("\""))
        {
            m_value = m_value.left(m_value.length() - 1);
        }
        s = s.mid(p + 1);
        int q = s.indexOf("//");
        m_note = s.mid(q + 2).trimmed();

    }




}

const QString& CodeParser::dateType() const
{
    return m_dateType;
}

void CodeParser::setDateType(const QString& newDateType)
{
    m_dateType = newDateType;
}

const QString& CodeParser::varibleName() const
{
    return m_varibleName;
}

const QString& CodeParser::value() const
{
    return m_value;
}

void CodeParser::setValue(const QString& newValue)
{
    m_value = newValue;
}

const QString& CodeParser::note() const
{
    return m_note;
}

void CodeParser::setNote(const QString& newNote)
{
    m_note = newNote;
}

QString CodeParser::toDelphi()
{
    QString v;
    if (m_dateType == "string")
    {
        v = "'" + m_value + "'";
    }
    else
    {
        v = m_value;
    }

    QString s = m_varibleName + " : " + m_dateType + " = " + v + " ;  // " + m_note;
    return s;

}

QString CodeParser::toQt()
{
    QString v;
    if (m_dateType == "string")
    {
        v = "'" + m_value + "'";
    }
    else
    {
        v = m_value;
    }

    QString s = m_dateType + "  " + m_varibleName + " = " + v + " ;  // " + m_note;
    return s;

}

QString CodeParser::toSql(bool isLast)
{
    return "";

}

QString CodeParser::toSqlite(bool isLast)
{
    return "";

}

const QString& CodeParser::className() const
{
    return m_className;
}

void CodeParser::setClassName(const QString& newClassName)
{
    m_className = newClassName;
}

const QString& CodeParser::tableName() const
{
    return m_tableName;
}
