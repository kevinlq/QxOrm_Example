#include "QPhoneVo.h"

QX_REGISTER_CPP_QX_MODEL(QPhoneVo)

namespace qx {
template <> void register_class(QxClass<QPhoneVo> & t)
{
    t.setName("t_PhoneInfo");

    long lVersion = 1;

    t.id   (&QPhoneVo::m_lID,                 "PhoneID",          lVersion);

    t.data (&QPhoneVo::m_strName,             "PhoneName",        lVersion);
}
}

QPhoneVo::QPhoneVo()
{

}
