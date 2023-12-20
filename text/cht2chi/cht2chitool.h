
#ifndef CHT2CHITOOL_H
#define CHT2CHITOOL_H


#include <QObject>
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QMap>


class Cht2ChiTool : public QObject
{
    Q_OBJECT
public:
    explicit Cht2ChiTool(QObject* parent = nullptr);

    QString libraryPath() const;
    void setLibraryPath(const QString& newLibraryPath);
    QString toChi(QString src);

signals:
private:
    QString m_libraryPath;
    QMap<QString, QString> m_dict;

};

#endif // CHT2CHITOOL_H
