#-------------------------------------------------
#
# Project created by QtCreator 2019-10-15T22:17:28
#
#-------------------------------------------------

QT       += core gui websockets sql network printsupport




greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = FingerManager-Server
TEMPLATE = app
RC_FILE = myapp.rc

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11
SOURCES += \
        qdateconvertor.cpp \
        logmanagement.cpp \
        main.cpp \
        mainwidget.cpp \
        usermanagement.cpp \
        websocket.cpp \
        globals.cpp


HEADERS += \
        qdateconvertor.h \
        logmanagement.h \
        mainwidget.h \
        usermanagement.h \
        websocket.h \
        globals.h

FORMS += \
        mainwidget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


win32:CONFIG(release, debug|release): LIBS += -L$$PWD/build-FingerManager-Server-Desktop_Qt_5_12_2_MinGW_32_bit-Release/release/ -lUCBioBSP
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/build-FingerManager-Server-Desktop_Qt_5_12_2_MinGW_32_bit-Release/debug/ -lUCBioBSP
else:unix: LIBS += -L$$PWD/build-FingerManager-Server-Desktop_Qt_5_12_2_MinGW_32_bit-Release/ -lUCBioBSP

INCLUDEPATH += $$PWD/build-FingerManager-Server-Desktop_Qt_5_12_2_MinGW_32_bit-Release/release
DEPENDPATH += $$PWD/build-FingerManager-Server-Desktop_Qt_5_12_2_MinGW_32_bit-Release/release

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/build-FingerManager-Server-Desktop_Qt_5_12_2_MinGW_32_bit-Release/release/ -lUCSAPI40
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/build-FingerManager-Server-Desktop_Qt_5_12_2_MinGW_32_bit-Release/debug/ -lUCSAPI40
else:unix: LIBS += -L$$PWD/build-FingerManager-Server-Desktop_Qt_5_12_2_MinGW_32_bit-Release/ -lUCSAPI40

INCLUDEPATH += $$PWD/build-FingerManager-Server-Desktop_Qt_5_12_2_MinGW_32_bit-Release/release
DEPENDPATH += $$PWD/build-FingerManager-Server-Desktop_Qt_5_12_2_MinGW_32_bit-Release/release

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/build-FingerManager-Server-Desktop_Qt_5_12_2_MinGW_32_bit-Debug/release/ -lUCBioBSP
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/build-FingerManager-Server-Desktop_Qt_5_12_2_MinGW_32_bit-Debug/debug/ -lUCBioBSP
else:unix: LIBS += -L$$PWD/build-FingerManager-Server-Desktop_Qt_5_12_2_MinGW_32_bit-Debug/ -lUCBioBSP

INCLUDEPATH += $$PWD/build-FingerManager-Server-Desktop_Qt_5_12_2_MinGW_32_bit-Debug/debug
DEPENDPATH += $$PWD/build-FingerManager-Server-Desktop_Qt_5_12_2_MinGW_32_bit-Debug/debug

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/build-FingerManager-Server-Desktop_Qt_5_12_2_MinGW_32_bit-Debug/release/ -lUCSAPI40
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/build-FingerManager-Server-Desktop_Qt_5_12_2_MinGW_32_bit-Debug/debug/ -lUCSAPI40
else:unix: LIBS += -L$$PWD/build-FingerManager-Server-Desktop_Qt_5_12_2_MinGW_32_bit-Debug/ -lUCSAPI40

INCLUDEPATH += $$PWD/build-FingerManager-Server-Desktop_Qt_5_12_2_MinGW_32_bit-Debug/debug
DEPENDPATH += $$PWD/build-FingerManager-Server-Desktop_Qt_5_12_2_MinGW_32_bit-Debug/debug
