#include "QPhoneDao.h"
#include "QDaoHelpBase.h"
#include "QPhoneVo.h"

QPhoneDao::QPhoneDao()
{

}

bool QPhoneDao::initTable()
{
    if (!dbOperateValid())
    {
        return false;
    }

    QSqlError sqlError = QDAOHELP->createTable<QPhoneVo>();

    return sqlError.type() == QSqlError::NoError;
}

bool QPhoneDao::insertInfo(QPhoneVo *pInfo)
{
    QSqlError sqlError = QDAOHELP->insert(pInfo);

    return sqlError.type() == QSqlError::NoError;
}

bool QPhoneDao::getInfo(long id, QPhoneVo *pInfo)
{
    if (!dbOperateValid())
    {
        return false;
    }

    QString strSql = QString(" WHERE PhoneID = '%1'").arg(id);
    QSqlError error = QDAOHELP->fetch_by_query(strSql, pInfo);


    bool bResult = error.type() == QSqlError::NoError;

    return bResult;
}
