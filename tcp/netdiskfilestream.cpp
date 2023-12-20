#include "netdiskfilestream.h"

NetDiskFileStream::NetDiskFileStream(QObject* parent) : QObject(parent)
{

}

const QString& NetDiskFileStream::PathName() const
{
    return m_PathName;
}

void NetDiskFileStream::setPathName(const QString& newPathName)
{
    m_PathName = newPathName;
}

void NetDiskFileStream::write(QTcpSocket* socket)
{
    //1 总大小  int
    //2 md5内容大小 int
    //3  文件大小 int
    //4 md5内容
    //5 文件内容


    QByteArray block; //用于暂存我们要发送的数据
    QDataStream out(&block, QIODevice::ReadWrite);
    out.setVersion(QDataStream::Qt_4_6);
    //设置头
    out << quint64(0) << quint64(0) << quint64(0);




    QFile file(m_PathName);
    file.open(QIODevice::ReadOnly);
    QByteArray fileData = file.readAll();

    QCryptographicHash md5(QCryptographicHash::Md5);
    md5.addData(fileData);
    QByteArray md5Data = md5.result().toHex().toLower();
    out << md5Data;
    out << fileData;
    out.device()->seek(0);
    out << quint64(block.size());
    out.device()->seek(sizeof(quint64));
    out << quint64(md5Data.size());
    out.device()->seek(sizeof(quint64) * 2);
    out << quint64(fileData.size());






    out.device()->seek(0);
    socket->write(block, block.size());

    socket->waitForBytesWritten();


}

void NetDiskFileStream::write(QTcpSocket* socket, QString relativePath)
{
    //1 总大小  int
    //2 相对路径 int
    //3  文件大小 int
    //4 相对路径
    //5 文件内容


    QByteArray block; //用于暂存我们要发送的数据
    QDataStream out(&block, QIODevice::ReadWrite);
    out.setVersion(QDataStream::Qt_4_6);
    //设置头
    out << quint64(0) << quint64(0) << quint64(0);




    QFile file(m_PathName);
    file.open(QIODevice::ReadOnly);
    QByteArray fileData = file.readAll();


    QByteArray rData = relativePath.toLocal8Bit();
    out << rData;
    out << fileData;
    out.device()->seek(0);
    out << quint64(block.size());
    out.device()->seek(sizeof(quint64));
    out << quint64(rData.size());
    out.device()->seek(sizeof(quint64) * 2);
    out << quint64(fileData.size());






    out.device()->seek(0);
    socket->write(block, block.size());

    socket->waitForBytesWritten();

}

void NetDiskFileStream::writeDataPack(QTcpSocket* socket, quint64 dataType, QString caption, QByteArray& data)
{
    //1总大小
    //2 数据类型  int
    //3 相对路径 int
    //4  文件大小 int
    //4 标题
    //5 文件内容


    QByteArray block; //用于暂存我们要发送的数据
    QDataStream out(&block, QIODevice::ReadWrite);
    out.setVersion(QDataStream::Qt_4_6);
    //设置头
    out << quint64(0) << quint64(0) << quint64(0) << quint64(0);

    QByteArray captionData = caption.toLocal8Bit();
    out << captionData;
    out << data;

    out.device()->seek(0);
    out << quint64(block.size());
    out.device()->seek(sizeof(quint64));
    out << dataType;
    out.device()->seek(sizeof(quint64) * 2);
    out << quint64(captionData.size());
    out.device()->seek(sizeof(quint64) * 3);
    out << quint64(data.size());


    out.device()->seek(0);
    socket->write(block, block.size());
    socket->flush();
    qDebug() << block.size();




}

void NetDiskFileStream::writeDataPack(QTcpSocket* socket, quint64 dataType, QString caption, QString userInfo, QByteArray& data)
{
    //1总大小
    //2 数据类型  int
    //3 相对路径 int
    //4 用户信息大小 int
    //5  文件大小 int
    //6 标题
    //7 用户信息
    //8 文件内容


    QByteArray block; //用于暂存我们要发送的数据
    QDataStream out(&block, QIODevice::ReadWrite);
    out.setVersion(QDataStream::Qt_4_6);
    //设置头
    out << quint64(0) << quint64(0) << quint64(0) << quint64(0) << quint64(0);

    QByteArray captionData = caption.toUtf8();
    out << captionData;
    QByteArray userInfoData = userInfo.toUtf8();
    out << userInfoData;
    out << data;

    out.device()->seek(0);
    out << quint64(block.size());
    out.device()->seek(sizeof(quint64));
    out << dataType;
    out.device()->seek(sizeof(quint64) * 2);
    out << quint64(captionData.size());
    out.device()->seek(sizeof(quint64) * 3);
    out << quint64(userInfoData.size());

    out.device()->seek(sizeof(quint64) * 4);
    out << quint64(data.size());

    out.device()->seek(0);
    socket->write(block, block.size());
    socket->flush();
    qDebug() << block.size();

}

void NetDiskFileStream::read(QTcpSocket* socket, quint64& md5Size, quint64& fileSize,  QByteArray& md5Data, QByteArray& fileData)
{
    while (socket->bytesAvailable() == 0)
    {
        QApplication::processEvents();
    }
    QByteArray data;
    do
    {
        data.append(socket->readAll());
    }
    while (socket->waitForReadyRead(100));
    qDebug() << "client" << data.size();
    QDataStream stream(data);
    quint64 allSize;
    stream.device()->seek(0);
    stream >> allSize;
    qDebug() << allSize;
    stream >> md5Size;
    qDebug() << md5Size;

    stream >> fileSize;
    qDebug() << fileSize;
    md5Data.resize(32);
    stream >> md5Data;
    qDebug() << md5Data;
    fileData.resize(fileSize);
    stream >> fileData;

}

quint64 NetDiskFileStream::readDataPack(QTcpSocket* socket, quint64& dataType, quint64& captionSize, QString& caption, quint64& dataSize, QByteArray& data)
{

    quint64 allSize;
    QByteArray recData;
    QByteArray headData;
    int readSize = sizeof(quint64);
    headData = socket->read(sizeof(quint64));
    recData.append(headData);
    QDataStream headStream(headData);
    headStream >> allSize;
    while (quint64(recData.size()) < allSize)
    {
        int n = allSize - recData.size();
        if (n >= 1024)
        {
            recData.append(socket->read(1024));
        }
        else
        {
            recData.append(socket->read(n));
        }

        socket->waitForReadyRead(50);
    }

    qDebug() << "client" << data.size();
    QDataStream stream(recData);

    stream.device()->seek(0);
    stream >> allSize;
    qDebug() << allSize;
    stream >> dataType;
    qDebug() << allSize;

    stream >> captionSize;
    stream >> dataSize;
    QByteArray captionData;
    stream >> captionData;
    captionData.resize(captionSize);
    caption = QString::fromLocal8Bit(captionData);


    data.resize(dataSize);
    stream >> data;
    qDebug() << allSize << recData.size();
    m_receiveData.clear();
    m_receiveData.append(recData);
    return allSize;

}

quint64 NetDiskFileStream::readDataPack(QTcpSocket* socket, quint64& dataType, quint64& captionSize, QString& caption, quint64& userInfoSize, QString& userInfo, quint64& dataSize, QByteArray& data)
{
    quint64 allSize;
    QByteArray recData;
    QByteArray headData;
    int readSize = sizeof(quint64);
    headData = socket->read(sizeof(quint64));
    recData.append(headData);
    QDataStream headStream(headData);
    headStream >> allSize;
    while (quint64(recData.size()) < allSize)
    {
        int n = allSize - recData.size();
        if (n >= 1024)
        {
            recData.append(socket->read(1024));
        }
        else
        {
            recData.append(socket->read(n));
        }

        socket->waitForReadyRead(50);
    }

    qDebug() << "client" << data.size();
    QDataStream stream(recData);

    stream.device()->seek(0);
    stream >> allSize;
    qDebug() << allSize;
    stream >> dataType;
    qDebug() << allSize;

    stream >> captionSize;
    stream >> userInfoSize;
    stream >> dataSize;

    QByteArray captionData;
    stream >> captionData;
    captionData.resize(captionSize);
    caption = QString::fromLocal8Bit(captionData);

    QByteArray userInfoData;
    stream >> userInfoData;
    userInfoData.resize(userInfoSize);
    userInfo = QString::fromLocal8Bit(userInfoData);


    data.resize(dataSize);
    stream >> data;
    qDebug() << allSize << recData.size();
    m_receiveData.clear();
    m_receiveData.append(recData);
    return allSize;

}

void NetDiskFileStream::readByRpath(QTcpSocket* socket, quint64& rPathSize, quint64& fileSize, QByteArray& rPathData, QByteArray& fileData)
{
    while (socket->bytesAvailable() == 0)
    {
        QApplication::processEvents();
    }
    QByteArray data;
    do
    {
        data.append(socket->readAll());
    }
    while (socket->waitForReadyRead(100));

    QDataStream stream(data);
    quint64 allSize;
    stream.device()->seek(0);
    stream >> allSize;

    stream >> rPathSize;


    stream >> fileSize;
    rPathData.resize(rPathSize);
    stream >> rPathData;
    fileData.resize(fileSize);
    stream >> fileData;

}



QByteArray NetDiskFileStream::receiveData() const
{
    return m_receiveData;
}

void NetDiskFileStream::setReceiveData(const QByteArray& newReceiveData)
{
    m_receiveData = newReceiveData;
}


