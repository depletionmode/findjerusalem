#-------------------------------------------------
#
# Project created by QtCreator 2010-08-03T04:27:27
#
#-------------------------------------------------

QT       += core gui network svg

TARGET = FindJerusalem
TEMPLATE = app


SOURCES += main.cpp\
        findjerusalem.cpp \
    compassthread.cpp

HEADERS  += findjerusalem.h \
    compassthread.h

FORMS    += findjerusalem.ui

CONFIG += mobility
MOBILITY = location sensors

symbian {
    TARGET.UID3 = 0xe7264c8d
    TARGET.CAPABILITY += Location
    TARGET.EPOCSTACKSIZE = 0x14000
    TARGET.EPOCHEAPSIZE = 0x020000 0x800000
}

RESOURCES += \
    images.qrc
