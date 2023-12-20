#ifndef CODEPARSER_H
#define CODEPARSER_H

#include <QObject>

class CodeParser : public QObject
{
    Q_OBJECT
public:
    explicit CodeParser(QObject* parent = nullptr);

    const QString& statement() const;
    void setStatement(const QString& newStatement);

    const QString& dateType() const;
    void setDateType(const QString& newDateType);

    const QString& varibleName() const;


    const QString& value() const;
    void setValue(const QString& newValue);

    const QString& note() const;
    void setNote(const QString& newNote);

    QString toDelphi();
    QString toQt();
    QString toSql(bool isLast = false);
    QString toSqlite(bool isLast = false);

    const QString& className() const;
    void setClassName(const QString& newClassName);

    const QString& tableName() const;

signals:
private:
    QString m_statement;
    QString m_dateType;
    QString m_varibleName;
    QString m_value;
    QString m_note;
    QString m_className;
    QString m_tableName;

};

#endif // CODEPARSER_H
