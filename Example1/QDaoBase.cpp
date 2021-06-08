#include "QDaoBase.h"
#include "QDaoHelpBase.h"

#include <QJsonDocument>
#include <QVariantMap>
#include <QDebug>

QDaoBase::QDaoBase()
{
}

QDaoBase::~QDaoBase()
{
}

bool QDaoBase::initDataBase(const QString &strJsonInfo)
{
    QByteArray baData = strJsonInfo.toLatin1();
    QJsonDocument doc = QJsonDocument::fromJson(baData);

    QVariantMap map = doc.toVariant().toMap();
    if (map.isEmpty () || !map.contains ("strDatabaseType"))
    {
        qDebug() << "json format is invalid!  " << strJsonInfo;
        return false;
    }

    QString strDataBaseType     = map.value ("strDatabaseType").toString ();
    QString strHostName         = map.value ("strHostName").toString ();
    int nPort                   = map.value ("nPort").toInt ();
    QString strUserName         = map.value ("strUserName").toString ();
    QString strPwd              = map.value ("strPwd").toString ();
    QString strDataBaseName     = map.value ("strDatabaseName").toString ();

    QDAOHELP->initDataBase(strDataBaseType, strHostName, nPort, strUserName, strPwd, strDataBaseName);

    return true;
}

bool QDaoBase::isDataBaseValid()
{
    return QDAOHELP->getDatabase().isValid();
}

bool QDaoBase::dbOperateValid()
{
    return (isDataBaseValid() && isDataBaseOpen());
}

bool QDaoBase::isDataBaseOpen()
{
    return QDAOHELP->getDatabase().isOpen();
}

void QDaoBase::closeDataBase()
{
    QDAOHELP->getDatabase().close();
}
