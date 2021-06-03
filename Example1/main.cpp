#include <QCoreApplication>
#include <QVariantMap>
#include <QJsonDocument>
#include <QDebug>

#include "QPhoneDao.h"


int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    QVariantMap map = {{"strDatabaseType", "QSQLITE"}, {"strHostName", "localHost"}, {"nPort", 0}
                       ,{"strUserName", "devstone"}, {"strPwd", "123456"}, {"strDatabaseName", "QTools.db"}};

    QString strJsonInfo = QString(QJsonDocument::fromVariant(map).toJson());

    if ( !QPhoneDao::initDataBase(strJsonInfo))
    {
        qDebug() << "initDataBase error..";
        return 0;
    }

    qDebug() << "initDataBase ok ";

    QPhoneDao::initTable();

    return app.exec();
}
