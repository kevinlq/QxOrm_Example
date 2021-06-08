#ifndef QPHONEDAO_H
#define QPHONEDAO_H

#include "QDaoBase.h"

class QPhoneVo;

class QPhoneDao : public QDaoBase
{
public:
    QPhoneDao();

    static bool initTable();

    static bool insertInfo(QPhoneVo* pInfo);

    static bool getInfo(long id, QPhoneVo* pInfo);
};

#endif // QPHONEDAO_H
