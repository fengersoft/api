#ifndef NETDISKFILESTREAM_H
#define NETDISKFILESTREAM_H

#include <QObject>
#include <QDataStream>
#include <QTcpSocket>
#include <QDebug>
#include <QFile>
#include <QCryptographicHash>
#include <QFileInfo>
#include <QApplication>

const quint64 NetDiskFileStream_String = 0;
const quint64 NetDiskFileStream_Json = 1;
const quint64 NetDiskFileStream_File = 2;
const quint64 NetDiskFileStream_UserName = 4;
const quint64 NetDiskFileStream_Png = 5;
const quint64 NetDiskFileStream_PngData = 6;
class NetDiskFileStream : public QObject
{
    Q_OBJECT
public:
    explicit NetDiskFileStream(QObject* parent = nullptr);

    const QString& PathName() const;
    void setPathName(const QString& newPathName);
    void write(QTcpSocket* socket);
    void write(QTcpSocket* socket, QString relativePath);
    void writeDataPack(QTcpSocket* socket, quint64 dataType, QString caption, QByteArray& data);
    void writeDataPack(QTcpSocket* socket, quint64 dataType, QString caption, QString userInfo, QByteArray& data);
    void read(QTcpSocket* socket, quint64& md5Size, quint64& fileSize, QByteArray& md5Data,
              QByteArray& fileData);

    quint64 readDataPack(QTcpSocket* socket, quint64& dataType, quint64& captionSize, QString& caption,
                         quint64& dataSize,
                         QByteArray& data);
    quint64 readDataPack(QTcpSocket* socket, quint64& dataType,
                         quint64& captionSize, QString& caption,
                         quint64& userInfoSize, QString& userInfo,
                         quint64& dataSize,
                         QByteArray& data);
    void readByRpath(QTcpSocket* socket, quint64& rPathSize, quint64& fileSize, QByteArray& rPathData,
                     QByteArray& fileData);


    QByteArray receiveData() const;
    void setReceiveData(const QByteArray& newReceiveData);

signals:
private:
    QString m_PathName;
    QByteArray m_receiveData;

};

#endif // NETDISKFILESTREAM_H
