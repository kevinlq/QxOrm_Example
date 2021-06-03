#ifndef QPHONEVO_H
#define QPHONEVO_H

#include "../3rdparty/QxOrm/precompiled.h"

class QPhoneVo
{
    QX_REGISTER_FRIEND_CLASS(QPhoneVo)
public:
    QPhoneVo();

    long        m_lID = 0;
    QString     m_strName = "";
};

QX_REGISTER_HPP_QX_MODEL(QPhoneVo, qx::trait::no_base_class_defined, 1)

#endif // QPHONEVO_H
