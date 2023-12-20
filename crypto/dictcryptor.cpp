#include "dictcryptor.h"

DictCryptor::DictCryptor(QObject* parent)
    : QObject{parent}
{

}

void DictCryptor::genCryptoKey()
{
    short k = -128;
    for (int i = 0; i < 256; i++)
    {
        m_keys[i] = (char)k;
        k++;
    }

    for (int i = 0; i < 256; i++)
    {
        int n = QRandomGenerator::global()->bounded(0, 255);

        char c = m_keys[i];
        m_keys[i] = m_keys[n];
        m_keys[n] = c;



    }
    k = -128;
    m_mapKeys.clear();
    for (int i = 0; i < 256; i++)
    {
        m_mapKeys[k] = (short)m_keys[i];


        k++;
    }
    for (int i = 0; i < 256; i++)
    {
        m_decryptKeys[i] = m_mapKeys.key(i - 128);
    }
    qDebug() << m_mapKeys;





}

void DictCryptor::saveCryptoKeyToJson(QString pathName)
{
    QMap<short, short>::Iterator it = m_mapKeys.begin();
    QJsonArray jarr;
    for (; it != m_mapKeys.end(); it++)
    {
        QJsonObject jobj;
        jobj["k"] = it.key();
        jobj["v"] = it.value();
        jarr.append(jobj);
    }
    QJsonDocument jdoc;
    jdoc.setArray(jarr);
    QByteArray data = jdoc.toJson();
    QFile file(pathName);
    file.open(QFile::WriteOnly);
    file.write(data);
    file.close();



}

void DictCryptor::loadCryptoKeyFromJson(QString pathName)
{
    QFile file(pathName);
    file.open(QIODevice::ReadOnly);
    QByteArray data = file.readAll();
    QJsonDocument jdoc = QJsonDocument::fromJson(data);
    QJsonArray jarr = jdoc.array();
    m_mapKeys.clear();
    for (int i = 0; i < jarr.count(); i++)
    {
        QJsonObject jobj = jarr.at(i).toObject();
        m_mapKeys[jobj["k"].toInt()] = jobj["v"].toInt();
        m_keys[jobj["k"].toInt() + 128] = (char)jobj["v"].toInt();
    }
    file.close();
    for (int i = 0; i < 256; i++)
    {
        m_decryptKeys[i] = m_mapKeys.key(i - 128);
    }



}

QString DictCryptor::encryptStringToBase64(QString s)
{
    QByteArray data;
    QByteArray ret;
    data.append(s.toLocal8Bit());
    for (int i = 0; i < data.length(); i++)
    {
        short k = (short)data.at(i);
        short v = m_mapKeys[k];
        ret.append((char)v);
    }
    QString retStr;
    retStr = ret.toHex();
    return retStr;


}

QString DictCryptor::decryptStringFromBase64(QString s)
{
    QByteArray data = hexStringToByteArray(s);
    QByteArray ret;
    for (int i = 0; i < data.length(); i++)
    {
        short k = (short)data.at(i);
        short v = m_mapKeys.key(k);
        ret.append((char)v);
    }

    QString retStr;
    retStr = QString::fromLocal8Bit(ret);
    return retStr;

}

void DictCryptor::encryptFile(QString srcPathName, QString destPathName)
{
    QFile srcFile(srcPathName);
    srcFile.open(QFile::ReadOnly);
    QByteArray srcData = srcFile.readAll();
    QByteArray destData;
    destData.resize(srcData.size());
    char* destPData = destData.data();
    srcFile.close();
    char* srcPData = srcData.data();
    qsizetype fileSize = srcData.length();
    for (qsizetype i = 0; i < fileSize; i++)
    {
        short k = (short)srcPData[i];
        short v = m_keys[k + 128];

        destPData[i] = (char)v;
    }
    QFile destFile(destPathName);
    destFile.open(QFile::WriteOnly);
    destFile.write(destData);
    destFile.close();



}

void DictCryptor::decryptFile(QString srcPathName, QString destPathName)
{
    QFile srcFile(srcPathName);
    srcFile.open(QFile::ReadOnly);
    QByteArray srcData = srcFile.readAll();

    srcFile.close();
    qsizetype fileSize = srcData.length();
    QByteArray destData;
    destData.resize(fileSize);
    char* srcPData = srcData.data();
    char* destPData = destData.data();
    for (qsizetype i = 0; i < fileSize ; i++)
    {
        short k = (short)srcPData[i];
        short v = m_decryptKeys[k + 128];
        destPData[i] = (char)v;
    }
    QFile destFile(destPathName);
    destFile.open(QFile::WriteOnly);
    destFile.write(destData);
    destFile.close();

}

QByteArray DictCryptor::hexStringToByteArray(QString s)
{
    int i = 0;
    QByteArray ret;
    while (i < s.length())
    {
        QString v = s.mid(i, 2);
        int k = v.toInt(nullptr, 16);

        char c = (char)k;
        ret.append(c);
        i += 2;
    }
    return ret;

}
