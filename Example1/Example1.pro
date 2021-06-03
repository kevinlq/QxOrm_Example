include($$PWD/../QxOrm_Example.pri)

QT	 +=core sql network

TEMPLATE  =app
TARGET	 = Example1$${FILE_POSTFIX}

INCLUDEPATH +=$${QXORM_PATH}/include

SOURCES += \
    main.cpp \
    QPhoneVo.cpp \
    QDaoHelpBase.cpp \
    QPhoneDao.cpp \
    QDaoBase.cpp

HEADERS += \
    QPhoneVo.h \
    QDaoHelpBase.h \
    QPhoneDao.h \
    QDaoBase.h
