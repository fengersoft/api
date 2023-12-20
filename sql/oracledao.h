#ifndef ORACLEDAO_H
#define ORACLEDAO_H

#include <QCoreApplication>

#include <QObject>
#include <QSettings>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QtDebug>
#include <memory>
using namespace std;

class OracleDao : public QObject
{
    Q_OBJECT
public:
    static shared_ptr<OracleDao> instance();

    bool connectDB();
    void loadInfoFromConfig();
    void getInfoFromConfig(QString& ip, QString& db, QString& user, QString& pwd);
    void saveInfoToConfig(QString ip, QString db, QString user, QString pwd);
    bool isConnected();
    bool testConnected(QString ip, QString db, QString user, QString pwd);
    bool select(QString sql, QSqlQuery& qry);
    bool execute(QString sql);

private:
    explicit OracleDao(QObject* parent = nullptr);
    static shared_ptr<OracleDao> m_instance;
    QSqlDatabase m_DbInstance;
    QString m_ip;
    QString m_db;
    QString m_user;
    QString m_pwd;
    bool m_isConnected;
signals:

public slots:
};
shared_ptr<OracleDao> oracleDao();

#endif // ORACLEDAO_H
