#-------------------------------------------------
#
# Project created by QtCreator 2019-10-22T15:55:09
#
#-------------------------------------------------

QT       += core gui core serialport sql network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = UPASS
TEMPLATE = app

SOURCES += main.cpp \
    databaseclass1.cpp \
    databaseclass2.cpp \
    serialclass.cpp \
    mainclass.cpp \

HEADERS += \
    databaseclass1.h \
    databaseclass2.h \
    mainclass.h \
    serialclass.h \

FORMS    += mainclass.ui

INCLUDEPATH += /usr/lib/arm-linux-gnueabihf
INCLUDEPATH += /usr/include
INCLUDEPATH += /usr/local
INCLUDEPATH += /usr/include/mysql

win32:CONFIG(release, debug|release): LIBS += -L$$/usr/local/lib/release/ -lwiringPi
else:win32:CONFIG(debug, debug|release): LIBS += -L$$/usr/local/lib/debug/ -lwiringPi
else:unix: LIBS += -L$$/usr/local/lib/ -lwiringPi

INCLUDEPATH += $$/usr/local/include
DEPENDPATH += $$/usr/local/include

win32:CONFIG(release, debug|release): LIBS += -L$$/usr/lib/arm-linux-gnueabihf/release/ -lmysqld
else:win32:CONFIG(debug, debug|release): LIBS += -L$$/usr/lib/arm-linux-gnueabihf/debug/ -lmysqld
else:unix: LIBS += -L$$/usr/lib/arm-linux-gnueabihf/ -lmysqld

INCLUDEPATH += $$/usr/lib/arm-linux-gnueabihf
DEPENDPATH += $$/usr/lib/arm-linux-gnueabihf

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$/usr/lib/arm-linux-gnueabihf/release/libmysqld.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $/usr/lib/arm-linux-gnueabihf/debug/libmysqld.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$/usr/lib/arm-linux-gnueabihf/release/mysqld.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$/usr/lib/arm-linux-gnueabihf/debug/mysqld.lib
else:unix: PRE_TARGETDEPS += $$/usr/lib/arm-linux-gnueabihf/libmysqld.a

win32:CONFIG(release, debug|release): LIBS += -L$/usr/lib/arm-linux-gnueabihf/release/ -lmysqlclient
else:win32:CONFIG(debug, debug|release): LIBS += -L$$/usr/lib/arm-linux-gnueabihf/debug/ -lmysqlclient
else:unix: LIBS += -L$$/usr/lib/arm-linux-gnueabihf/ -lmysqlclient

INCLUDEPATH += $/usr/lib/arm-linux-gnueabihf




win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../CTPOZ/Library/lib8/release/ -lCSJPOSLib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../CTPOZ/Library/lib8/debug/ -lCSJPOSLib
else:unix: LIBS += -L$$PWD/../CTPOZ/Library/lib8/ -lCSJPOSLib

INCLUDEPATH += $$PWD/../CTPOZ/Library/lib8
DEPENDPATH += $$PWD/../CTPOZ/Library/lib8
