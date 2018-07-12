# channel_broadcaster.pri
QT += bluetooth network

HEADERS += \
    $$PWD/broadcaster_bt.h \
    $$PWD/broadcaster_channel.h \
    $$PWD/broadcaster_http.h

SOURCES += \
    $$PWD/broadcaster_bt.cpp \
    $$PWD/broadcaster_channel.cpp \
    $$PWD/broadcaster_http.cpp

INCLUDEPATH += $$PWD/3rdparty/qhttp/src

QHTTP_SOURCE_DIR = $$PWD/3rdparty/qhttp/xbin
QHTTP_TARGET_DIR = $$OUT_PWD

unix {
    LIBFILE = $$QHTTP_SOURCE_DIR/libqhttp.a
    QMAKE_PRE_LINK += $$quote(cp $$LIBFILE $$QHTTP_TARGET_DIR)
}

win32 {
    LIBFILE = $$QHTTP_SOURCE_DIR/qhttp.lib
    LIBFILE ~= s,/,\\,g
    QHTTP_TARGET_DIR ~= s,/,\\,g
    QMAKE_PRE_LINK += $$quote(cmd /c copy /y $$LIBFILE $$QHTTP_TARGET_DIR)
}

LIBS += -L$$QHTTP_TARGET_DIR -lqhttp
