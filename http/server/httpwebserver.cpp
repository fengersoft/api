
#include "httpwebserver.h"
static QString replyTextFormat(
    "HTTP/1.1 %1 OK\r\n"
    "Content-Type: %2\r\n"
    "Content-Length: %3\r\n"
    "Access-Control-Allow-Origin: *\r\n"
    "keep-alive:keep-alive\r\n"
    "Keep-Alive: timeout=5\r\n"
    "\r\n"
    "%4"
);

static QString replyRedirectsFormat(
    "HTTP/1.1 %1 OK\r\n"
    "Content-Type: %2\r\n"
    "Content-Length: %3\r\n"
    "Access-Control-Allow-Origin: *\r\n"
    "\r\n"
    "%4"
);

static QString replyFileFormat(
    "HTTP/1.1 %1 OK\r\n"
    "Content-Disposition: attachment;filename=%2\r\n"
    "Content-Length: %3\r\n"
    "Access-Control-Allow-Origin: *\r\n"
    "\r\n"
);
static QString replyDataFormat(
    "HTTP/1.1 %1\r\n"
    "Content-Type: %2/%3\r\n"
    "Content-Length: %4\r\n"
    "Access-Control-Allow-Origin: *\r\n"
    "\r\n"
);
static QString replyImageFormat(
    "HTTP/1.1 %1\r\n"
    "Content-Type: image/%2\r\n"
    "Content-Length: %3\r\n"
    "Access-Control-Allow-Origin: *\r\n"
    "\r\n"
);

static QString replyBytesFormat(
    "HTTP/1.1 %1 OK\r\n"
    "Content-Type: application/octet-stream\r\n"
    "Content-Length: %2\r\n"
    "Access-Control-Allow-Origin: *\r\n"
    "\r\n"
);
static QString replyPdfFormat(
    "HTTP/1.1 %1 OK\r\n"
    "Content-Type: application/pdf\r\n"
    "Content-Length: %2\r\n"
    "Access-Control-Allow-Origin: *\r\n"
    "\r\n"
);

static QString replyOptionsFormat(
    "HTTP/1.1 200 OK\r\n"
    "Allow: OPTIONS, GET, POST, PUT, HEAD\r\n"
    "Access-Control-Allow-Methods: OPTIONS, GET, POST, PUT, HEAD\r\n"
    "Content-Length: 0\r\n"
    "Access-Control-Allow-Origin: *\r\n"
    "\r\n"
);
HttpWebServer::HttpWebServer(QObject* parent)
    : QObject{parent}
{
    m_server = new QTcpServer(this);
    connect(m_server, &QTcpServer::newConnection, this,
            &HttpWebServer::onNewConnection);
    m_imageSuffixes << "png" << "jpg" << "webp" << "bmp" << "ico";

}

QTcpServer* HttpWebServer::server() const
{
    return m_server;
}

void HttpWebServer::setServer(QTcpServer* newServer)
{
    m_server = newServer;
}

int HttpWebServer::port() const
{
    return m_port;
}

void HttpWebServer::setPort(int newPort)
{
    m_port = newPort;
}

void HttpWebServer::startServer(int port)
{
    m_port = port;
    m_server->listen(QHostAddress::Any, port);

}

void HttpWebServer::onNewConnection()
{
    QTcpSocket* socket = m_server->nextPendingConnection();
    connect(socket, &QIODevice::readyRead, this, &HttpWebServer::
            onClientReadyRead);

}

void HttpWebServer::onClientReadyRead()
{
    QTcpSocket* socket = static_cast<QTcpSocket*>(sender());
    QByteArray data = socket->readAll();
    QString request = data;
    RequestParser* paser = new RequestParser(this);
    paser->setRequestInfo(request);
    QString reqeustInfo = paser->requestPath();
    QString filePathName = getServerFilePathName(reqeustInfo);
    QFileInfo fileInfo(filePathName);
    if (fileInfo.exists())
    {

        QString suffix = fileInfo.suffix().toLower();
        if (m_imageSuffixes.contains(suffix))
        {
            sendServerData(fileInfo, socket, "image", suffix);
        }
        else if (suffix == "pdf")
        {
            sendServerData(fileInfo, socket, "application", "pdf");

        }
        else
        {
            QStringList responses;
            QFile file(fileInfo.absoluteFilePath());
            file.open(QIODevice::ReadOnly);
            QString ret = file.readAll();
            file.close();
            QByteArray retData = replyTextFormat.arg(
                                     QString::number(200),
                                     getContextType(suffix),
                                     QString::number(ret.toUtf8().size()),
                                     ret
                                 ).toUtf8();
            socket->write(retData);
        }

    }
    else
    {
        emit processRequest(paser, socket);

        qDebug() << fileInfo;
    }
    qDebug() << fileInfo;
    delete paser;

}

QString HttpWebServer::getContextType(QString suffix)
{

    if (suffix == "js")
    {
        return "application/x-javascript";
    }
    if (suffix == "css")
    {
        return "text/css";
    }
    else
    {
        return "text;charset=UTF-8";
    }
}

QStringList HttpWebServer::rootPaths() const
{
    return m_rootPaths;
}

void HttpWebServer::setRootPaths(const QStringList& newRootPaths)
{
    m_rootPaths = newRootPaths;
}

void HttpWebServer::addRootPath(QString path)
{
    m_rootPaths << path;

}

QString HttpWebServer::getServerFilePathName(QString pathName)
{
    if (pathName == "/")
    {
        pathName = m_defaultPagePath;
    }
    for (const QString& folder : qAsConst(m_rootPaths))
    {
        if (QFile::exists(folder + pathName))
        {
            return folder + pathName;
        }
    }

    return "";

}

void HttpWebServer::sendServerData(QFileInfo& fileInfo, QTcpSocket* socket,
                                   QString dataType, QString suffix)
{

    QFile file(fileInfo.absoluteFilePath());
    file.open(QIODevice::ReadOnly);
    QByteArray retData2 = file.readAll();
    int fileSize = file.size();
    file.close();
    QByteArray retData1 = replyDataFormat.arg(
                              QString::number(200),
                              dataType, suffix,
                              QString::number(fileSize)
                          ).toUtf8();
    QByteArray retData;
    retData.append(retData1);
    retData.append(retData2);
    socket->write(retData);

}

QString HttpWebServer::defaultPagePath() const
{
    return m_defaultPagePath;
}

void HttpWebServer::setDefaultPagePath(const QString& newDefaultPagePath)
{
    m_defaultPagePath = newDefaultPagePath;
}

