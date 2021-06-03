#ifndef QDAOBASE_H
#define QDAOBASE_H

#include <QString>

class QDaoBase
{
public:
    QDaoBase();
    virtual ~QDaoBase();

    //初始化数据库
    static bool initDataBase(const QString &strJsonInfo);

    //数据库是否有效
    static bool isDataBaseValid();

    static bool dbOperateValid();

    static bool isDataBaseOpen();
    //关闭数据库
    static void closeDataBase();
};

#endif // QDAOBASE_H
