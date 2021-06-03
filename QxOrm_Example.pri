# Config Para

QXORM_PATH=$$PWD/3rdparty/QxOrm/

CONFIG(debug, debug|release):{
        FILE_POSTFIX = D
        DIR_COMPILEMODE = Debug
}
else:CONFIG(release, debug|release):{
        FILE_POSTFIX =
        DIR_COMPILEMODE = Release
}

win32:{
    FILE_DLL_PREFIX =
    FILE_DLL_EXT = .dll
    DIR_PLATFORM = Win32
}
else:linux:{
    FILE_DLL_PREFIX =
    FILE_DLL_EXT = .sp
    DIR_PLATFORM = linux
}

DIR_DEPEND_QXORM_DEST = $${QXORM_PATH}/Lib/$${DIR_PLATFORM}/
INCLUDEPATH +=$${QXORM_PATH}/include

include($${QXORM_PATH}/QxOrm.pri)

DESTDIR	= $$PWD/Bin/$${DIR_PLATFORM}/

LIBS += -L$${DIR_DEPEND_QXORM_DEST} -lQxOrm$${FILE_POSTFIX}
