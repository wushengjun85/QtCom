#-------------------------------------------------
#
# Project created by QtCreator 2016-09-21T11:54:36
#
#-------------------------------------------------

QT       += core gui

TARGET = myCom
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    qextserialbase.cpp \
    posix_qextserialport.cpp

HEADERS  += widget.h \
    qextserialbase.h \
    posix_qextserialport.h

FORMS    += widget.ui
