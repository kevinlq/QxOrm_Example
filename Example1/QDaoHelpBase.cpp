#include "QDaoHelpBase.h"

QMap<QString, QDaoHelpBase *> QDaoHelpBase::m_strDaoNameToDaoHelp;

QDaoHelpBase::QDaoHelpBase()
{
}

QSqlDatabase QDaoHelpBase::getDatabase()
{
    return qx::QxSqlDatabase::getDatabase ();
}

QDaoHelpBase *QDaoHelpBase::getInstance(QString name)
{
    QDaoHelpBase *pInstance = m_strDaoNameToDaoHelp.value(name);
    if ( pInstance == Q_NULLPTR )
    {
        pInstance = new QDaoHelpBase();
        m_strDaoNameToDaoHelp.insert(name,pInstance );
    }

    return pInstance;
}

bool QDaoHelpBase::initDataBase(QString strDriverName, QString strHostName, int nPort
                                , QString strUserName, QString strPasswd, QString strDatabaseName)
{
    m_driverName = strDriverName;
    m_hostName = strHostName;
    m_port = nPort;
    m_userName = strUserName;
    m_passwd = strPasswd;
    m_databaseName = strDatabaseName;

    if ( !m_driverName.isNull () && !m_driverName.trimmed ().isEmpty ())
    {
        qx::QxSqlDatabase::getSingleton ()->setDriverName (m_driverName);
    }
    if ( !m_databaseName.isNull () && !m_databaseName.trimmed ().isEmpty ())
    {
        qx::QxSqlDatabase::getSingleton ()->setDatabaseName (m_databaseName);
    }
    if ( !m_hostName.isNull () && !m_hostName.trimmed ().isEmpty ())
    {
        qx::QxSqlDatabase::getSingleton ()->setHostName (m_hostName);
    }
    if ( m_port > 0)
    {
        qx::QxSqlDatabase::getSingleton ()->setPort ( m_port );
    }
    if ( !m_userName.isNull () && !m_userName.trimmed ().isEmpty ())
    {
        qx::QxSqlDatabase::getSingleton ()->setUserName (m_userName);
    }
    if ( !m_passwd.isNull () && !m_passwd.trimmed ().isEmpty () )
    {
        qx::QxSqlDatabase::getSingleton ()->setPassword (m_passwd);
    }

    return true;
}
