#include "sm4object.h"
#include "qchar.h"
#include <cstddef>
#include <string>

Sm4Object::Sm4Object()
{

}



void Sm4Object::setKey(const std::string& k)
{
    key = k;
}

void Sm4Object::setIv(const std::string& i)
{
    iv = i;
}

void Sm4Object::setType(Sm4Object::Type t)
{
    type = t;
}

std::string Sm4Object::encrypt(const std::string& data)
{
    if (key.size() != 16 || iv.size() != 16 || data.empty())
        return std::string();

    unsigned char _key[16] = {0};
    memcpy(_key, key.data(), 16);

    unsigned char _iv[16] = {0};
    memcpy(_iv, iv.data(), 16);

    //PKCS7Padding
    int length = data.size();
    int m = length % 16;

    if (m != 0)
    {
        length += (16 - m);
    }
    else
    {
        length += 16;
    }

    unsigned char input[length];
    memset(input, length - data.size(), length);
    memcpy(input, data.data(), data.size());

    unsigned char output[length];
    memset(output, 0, length);

    sm4_context ctx;
    sm4_setkey_enc(&ctx, _key);

    if (type == Type::ECB)
    {
        sm4_crypt_ecb(&ctx, 1, length, input, output);
    }
    else if (type == Type::CBC)
    {
        sm4_crypt_cbc(&ctx, 1, length, _iv, input, output);
    }

    std::string ret;
    ret.assign((const char*) output, length);
    return ret;
}

QString Sm4Object::encryptString(QString& data)
{
    std::string srcData = data.toStdString();

    std::string t = encrypt(srcData);


    QByteArray retData;
    for (size_t i = 0; i < t.length(); i++)
    {
        retData.append(t[i]);
    }

    QString ss;
    for (int i = 0; i < retData.size(); i++)
    {
        ss += QString("%1").arg((unsigned char)retData.at(i), 2, 16, QLatin1Char('0'));
    }

    return ss;

}

QString Sm4Object::decryptString(QString& data)
{
    data = data.replace("\n", "");
    int i = 0;
    QByteArray srcData;

    while (i < data.size())
    {
        QString temp = data.mid(i, 2);
        bool ok;
        int n = temp.toInt(&ok, 16);
        char c = (char)n;
        srcData.append(c);


        i += 2;
    }
    qDebug() << data.size() << srcData.size();
    std::string ret = decrypt(srcData.toStdString());
    QString retStr = QString::fromStdString(ret);
    return retStr;


}

QByteArray Sm4Object::encryptByteArray(QByteArray data)
{
    if (key.size() != 16 || iv.size() != 16 || data.isEmpty())
        return QByteArray();

    unsigned char _key[16] = {0};
    memcpy(_key, key.data(), 16);

    unsigned char _iv[16] = {0};
    memcpy(_iv, iv.data(), 16);

    //PKCS7Padding
    int length = data.size();
    int m = length % 16;
    if (m != 0)
    {
        length += (16 - m);
    }
    else
    {
        length += 16;
    }


    unsigned char* input = new unsigned char[length];
    memset(input, length - data.size(), length);
    memcpy(input, data.data(), data.size());

    unsigned char* output = new unsigned char[length];
    memset(output, 0, length);

    sm4_context ctx;
    sm4_setkey_enc(&ctx, _key);

    if (type == Type::ECB)
    {
        sm4_crypt_ecb(&ctx, 1, length, input, output);
    }
    else if (type == Type::CBC)
    {
        sm4_crypt_cbc(&ctx, 1, length, _iv, input, output);
    }


    QByteArray ret;
    for (int i = 0; i < length; i++)
    {
        ret.append(output[i]);
    }
    delete[] input;
    delete[] output;
    return ret;

}

QByteArray Sm4Object::encryptByteArray(QByteArray data, int block)
{
    int  i = 0;
    QByteArray ret;
    while (data.size() - i > 0)
    {
        int n = data.size() - i >= (block * 1024) ? block * 1024 : data.size() - i;
        QByteArray temp = data.mid(i, n);
        QByteArray tempRet = encryptByteArray(temp);
        ret.append(tempRet);
        qDebug() << temp.size() << tempRet.size();
        i += n;
    }
    return ret;

}

bool Sm4Object::encryptFile(QString srcPath, QString destPath)
{
    if (!QFile::exists(srcPath))
    {
        return false;
    }
    QFile file(srcPath);
    file.open(QIODevice::ReadOnly);
    QByteArray data = file.readAll();
    file.close();
    QByteArray retData = encryptByteArray(data);

    QFile retFile(destPath);
    retFile.open(QIODevice::WriteOnly);
    retFile.write(retData);
    retFile.close();
    return true;


}

std::string Sm4Object::decrypt(const std::string& data)
{
    if (key.size() != 16 || iv.size() != 16 || data.size() < 16)
        return std::string();

    int length = data.size();
    qDebug() << length;

    unsigned char _key[16] = {0};
    memcpy(_key, key.data(), 16);

    unsigned char _iv[16] = {0};
    memcpy(_iv, iv.data(), 16);

    unsigned char input[length];
    memcpy(input, data.data(), length);

    unsigned char* output = new unsigned char[length];
    memset(output, 0, length);

    sm4_context ctx;
    sm4_setkey_dec(&ctx, _key);
    if (type == Type::ECB)
    {
        sm4_crypt_ecb(&ctx, 0, length, input, output);
    }
    else if (type == Type::CBC)
    {
        sm4_crypt_cbc(&ctx, 0, length, _iv, input, output);
    }


    length = length - (int)(output[length - 1]);




    if (length < 0)
    {
        delete[] output;
        return std::string();
    }


    std::string ret;
    qDebug() << length;

    ret.assign((const char*) output, length);
    delete[] output;
    return ret;
}

bool Sm4Object::decryptFile(QString srcPath, QString destPath)
{
    if (!QFile::exists(srcPath))
    {
        return false;
    }
    QFile file(srcPath);
    file.open(QIODevice::ReadOnly);
    QByteArray data = file.readAll();
    file.close();
    QByteArray retData = decryptByteArray(data);
    int dataSize = data.size();
    int retSize = retData.size();
    qDebug() << dataSize << retSize;
    QFile retFile(destPath);
    retFile.open(QIODevice::WriteOnly);
    retFile.write(retData);
    retFile.close();
    return true;

}

QByteArray Sm4Object::decryptByteArray(QByteArray data)
{
    if (key.size() != 16 || iv.size() != 16 || data.size() < 16)
        return QByteArray();

    int dataLen = data.size();
    int length = data.size();

    unsigned char _key[16] = {0};
    memcpy(_key, key.data(), 16);

    unsigned char _iv[16] = {0};
    memcpy(_iv, iv.data(), 16);

    unsigned char* input = new unsigned char[length];
    memcpy(input, data.data(), length);

    unsigned char* output = new unsigned char[length];
    memset(output, 0, length);

    sm4_context ctx;
    sm4_setkey_dec(&ctx, _key);
    if (type == Type::ECB)
    {
        sm4_crypt_ecb(&ctx, 0, length, input, output);
    }
    else if (type == Type::CBC)
    {
        sm4_crypt_cbc(&ctx, 0, length, _iv, input, output);
    }
    qDebug() << "laseLen" << (int) output[length - 1];
    length = length - (int) output[length - 1];
    if (length < 0)
    {
        delete[] input;
        delete[] output;
        return QByteArray();
    }

    QByteArray ret;
    for (int i = 0; i < length; i++)
    {

        ret.append(output[i]);


    }
    delete[] input;
    delete[] output;
    return ret;

}

QByteArray Sm4Object::decryptByteArray(QByteArray data, int block)
{
    int  i = 0;
    QByteArray ret;
    int k = 0;
    while (data.size() - i > 0)
    {
        int n = data.size() - i >= (block * 1024) ? (block * 1024) : (data.size() - i);
        QByteArray temp = data.mid(i, n);
        QByteArray tempRet = decryptByteArray(temp);
        if (temp.size() != tempRet.size())
        {
            qDebug() << k << temp.size() << tempRet.size() << n;
        }
        ret.append(tempRet);
        i += n;
        k++;
    }
    qDebug() << "i:" << i << data.size();
    return ret;

}
