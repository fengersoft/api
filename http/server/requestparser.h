
#ifndef REQUESTPARSER_H
#define REQUESTPARSER_H


#include <QObject>


class RequestParser : public QObject
{
    Q_OBJECT
public:
    explicit RequestParser(QObject* parent = nullptr);

    QString requestInfo() const;
    void setRequestInfo(const QString& newRequestInfo);

    QStringList requestInfoList() const;
    void setRequestInfoList(const QStringList& newRequestInfoList);
    QString requestPath();
    QString method();
signals:
private:
    QString m_requestInfo;
    QStringList m_requestInfoList;

};

#endif // REQUESTPARSER_H
