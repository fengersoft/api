#ifndef STRINGCHECKER_H
#define STRINGCHECKER_H

#include "qset.h"
#include <QObject>

class StringChecker : public QObject
{
    Q_OBJECT
public:
    explicit StringChecker(QObject* parent = nullptr);

    const QString& info() const;
    void setInfo(const QString& newInfo);

    const QSet<QString>& keywords() const;
    void setKeywords(const QSet<QString>& newKeywords);
    bool isChecked();
    static bool isChecked(QString info, QSet<QString> keywords);
signals:
private:
    QString m_info;
    QSet<QString> m_keywords;

};

#endif // STRINGCHECKER_H
