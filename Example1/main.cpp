#include <QCoreApplication>
#include <QVariantMap>
#include <QJsonDocument>
#include <QDebug>

#include "QPhoneDao.h"
#include "QPhoneVo.h"

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    QVariantMap map = {{"strDatabaseType", "QSQLITE"}, {"strHostName", "localHost"}, {"nPort", 0}
                       ,{"strUserName", "devstone"}, {"strPwd", "123456"}, {"strDatabaseName", "Example.db"}};

    QString strJsonInfo = QString(QJsonDocument::fromVariant(map).toJson());

    if ( !QPhoneDao::initDataBase(strJsonInfo))
    {
        qDebug() << "initDataBase error..";
        return 0;
    }

    qDebug() << "initDataBase ok ";

    QPhoneDao::initTable();

    QPhoneVo phone;
    phone.m_lID = 1;
    phone.m_strName = "xiao mi";

    QPhoneDao::insertInfo(&phone);

    QPhoneVo phone2;
    QPhoneDao::getInfo(1, &phone2);
    qDebug() << "#phone2:" << phone2.m_strName;

    return app.exec();
}
