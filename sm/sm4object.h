#ifndef SM4OBJECT_H
#define SM4OBJECT_H
extern "C"
{
#include "sm4.h"

}
#include <string>
#include <memory.h>
#include <iostream>
#include <QString>
#include <QDebug>
#include <QByteArray>
#include <QFile>
using namespace std;

class Sm4Object
{

public:
    enum Type
    {
        ECB,
        CBC
    };
    Sm4Object();




    void setKey(const std::string& k);
    void setIv(const std::string& i);
    void setType(Type t = Type::ECB);

    std::string encrypt(const std::string& data);
    QString encryptString(QString& data);
    QString decryptString(QString& data);
    QByteArray encryptByteArray(QByteArray data);
    QByteArray encryptByteArray(QByteArray data, int block);
    bool encryptFile(QString srcPath, QString destPath);
    std::string decrypt(const std::string& data);
    bool decryptFile(QString srcPath, QString destPath);
    QByteArray decryptByteArray(QByteArray data);
    QByteArray decryptByteArray(QByteArray data, int block);


private:
    std::string key;
    std::string iv;
    Type type;
};

#endif // SM4OBJECT_H
