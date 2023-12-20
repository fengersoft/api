#ifndef DICTCRYPTOR_H
#define DICTCRYPTOR_H

#include <QObject>
#include <QByteArray>
#include <QDebug>
#include <QRandomGenerator>
#include <QMap>
#include <QJsonDocument>
#include <QFile>
#include <QJsonArray>
#include <QJsonObject>

class DictCryptor : public QObject
{
    Q_OBJECT
public:
    explicit DictCryptor(QObject* parent = nullptr);
    void genCryptoKey();
    void saveCryptoKeyToJson(QString pathName);
    void loadCryptoKeyFromJson(QString pathName);
    QString encryptStringToBase64(QString s);
    QString decryptStringFromBase64(QString s);
    void encryptFile(QString srcPathName, QString destPathName);
    void decryptFile(QString srcPathName, QString destPathName);
    QByteArray hexStringToByteArray(QString s);
signals:

private:
    char m_keys[256];
    char m_decryptKeys[256];
    QMap<short, short> m_mapKeys;


};

#endif // DICTCRYPTOR_H
