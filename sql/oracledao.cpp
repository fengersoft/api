#include "oracledao.h"

shared_ptr<OracleDao> OracleDao::m_instance = nullptr;
shared_ptr<OracleDao> OracleDao::instance()
{
    if (m_instance == nullptr)
    {
        m_instance = shared_ptr<OracleDao>(new OracleDao());
    }
    return m_instance;
}

bool OracleDao::connectDB()
{
    loadInfoFromConfig();
    m_DbInstance.close();
    m_DbInstance.removeDatabase("db1");


    m_DbInstance = QSqlDatabase::addDatabase("QODBC", "db1");
    m_DbInstance.setDatabaseName(m_db);
    m_DbInstance.setUserName(m_user);
    m_DbInstance.setPassword(m_pwd);
    m_DbInstance.open();
    m_isConnected = m_DbInstance.isOpen();
    qDebug() << "oracle:" << m_DbInstance.lastError();

    return m_isConnected;
}

void OracleDao::loadInfoFromConfig()
{
    QSettings ini(QCoreApplication::applicationDirPath() + "/config.ini", QSettings::IniFormat);
    ini.beginGroup("database");
    m_ip = ini.value("ip").toString();
    m_db = ini.value("db").toString();
    m_user = ini.value("user").toString();
    m_pwd = ini.value("pwd").toString();
    ini.endGroup();
}

void OracleDao::getInfoFromConfig(QString& ip, QString& db, QString& user, QString& pwd)
{
    ip = m_ip;
    db = m_db;
    user = m_user;
    pwd = m_pwd;
}

void OracleDao::saveInfoToConfig(QString ip, QString db, QString user, QString pwd)
{
    QSettings ini(QCoreApplication::applicationDirPath() + "/config.ini", QSettings::IniFormat);
    ini.beginGroup("database");
    m_ip = ip;
    ini.setValue("ip", ip);
    m_db = db;
    ini.setValue("db", db);
    m_user = user;
    ini.setValue("user", user);
    m_pwd = pwd;
    ini.setValue("pwd", pwd);

    ini.endGroup();
}

bool OracleDao::isConnected()
{
    return m_isConnected;
}

bool OracleDao::testConnected(QString ip, QString db, QString user, QString pwd)
{
    QSqlDatabase m_testdb;
    m_testdb.close();
    m_testdb.removeDatabase("db2");
    // QString connStr = QString("Driver={sql server};server=%1;database=%2;uid=%3;pwd=%4;")
    QString connStr = QString("Provider=OraOLEDB.Oracle.1;Password=%3;Persist Security Info=True;User ID=%2;Data Source=%1")
                      .arg(db)
                      .arg(user)
                      .arg(pwd);
    m_testdb = QSqlDatabase::addDatabase("QODBC", "db2");
    m_testdb.setDatabaseName(connStr);
    m_testdb.open();
    bool ret = m_testdb.isOpen();
    if (ret == true)
    {
        qDebug() << "连接成功";
    }
    else
    {
        qDebug() << "连接失败，原因是:" + m_testdb.lastError().text();
    }
    m_testdb.close();
    return ret;
}

bool OracleDao::select(QString sql, QSqlQuery& qry)
{
    if (!m_DbInstance.isOpen())
    {
        m_DbInstance.open();
    }
    qry = QSqlQuery(m_DbInstance);
    return qry.exec(sql);
}

bool OracleDao::execute(QString sql)
{
    QSqlQuery qry(m_DbInstance);
    int ret = qry.exec(sql);

    if (ret == false)
    {
        qDebug() << sql;
        qDebug() << qry.lastError();
    }
    else
    {
        qDebug() << sql;
    }
    return  ret;
}

OracleDao::OracleDao(QObject* parent)
    : QObject(parent)
{
}

shared_ptr<OracleDao> oracleDao()
{
    return OracleDao::instance();
}
