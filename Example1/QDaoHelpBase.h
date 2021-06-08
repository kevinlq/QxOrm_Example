#ifndef QDAOHELPBASE_H
#define QDAOHELPBASE_H

#include "../3rdparty/QxOrm/precompiled.h"

#define QDAOHELP QDaoHelpBase::getInstance (MY_SQLLITE_DB_NAME)

class QDaoHelpBase
{
private:
    QDaoHelpBase();

public:
    QSqlDatabase getDatabase();
    static QDaoHelpBase * getInstance ( QString name);
    bool initDataBase(QString strDriverName, QString strHostName,
                      int nPort, QString strUserName,
                      QString strPasswd,QString strDatabaseName);

    template<class T >
    QSqlError createTable(QSqlDatabase * pDatabase = nullptr)
    {
        Q_UNUSED(pDatabase);
        return qx::dao::create_table<T>();
    }

    //插入数据
    template<class T>
    QSqlError insert(T &t,QSqlDatabase *pDatabase = nullptr)
    {
        return qx::dao::insert(t, pDatabase);
    }

    //保存数据
    template<class T>
    QSqlError save(T &t,QSqlDatabase *pDatabase = nullptr )
    {
        return qx::dao::save(t,pDatabase);
    }

    /*删除数据*/
    template<class T >
    QSqlError delete_by_id(T &t, QSqlDatabase *pDatabase = nullptr)
    {
        return qx::dao::delete_by_id(t, pDatabase);
    }

    template<class T >
    QSqlError fetch_by_query(QString sql, T &t, QSqlDatabase *pDatabase = nullptr)
    {
        qx::QxSqlQuery query(sql);
        return qx::dao::fetch_by_query(query, t, pDatabase);
    }

protected:
    QString m_driverName    = "";
    QString m_hostName      = "";
    int m_port              = 0;
    QString m_userName      = "";
    QString m_passwd        = "";
    QString m_databaseName  = "";

    static QMap<QString, QDaoHelpBase*> m_strDaoNameToDaoHelp;
};

#endif // QDAOHELPBASE_H
