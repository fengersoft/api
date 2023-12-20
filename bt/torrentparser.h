#ifndef TORRENTPARSER_H
#define TORRENTPARSER_H

#include <QObject>
#include <QFile>
#include <QDebug>


class TorrentParser : public QObject
{
    Q_OBJECT
public:
    explicit TorrentParser(QObject* parent = nullptr);

    QString pathName() const;
    void setPathName(const QString& newPathName);
    void loadFromPathName(QString pathName);
    int Key(QString s);
    QString getValue(QString s, int m, int n, int& retNum);
    QString name();
    QStringList paths();
signals:
private:
    QString m_pathName;
    QStringList m_values;

};

#endif // TORRENTPARSER_H
