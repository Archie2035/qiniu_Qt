#-------------------------------------------------
#
# Project created by QtCreator 2016-11-01T21:28:47
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = qiniu_demo
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    aqiniuapi.cpp \
    asettingwidget.cpp

HEADERS  += mainwindow.h \
    aqiniuapi.h \
    asettingwidget.h

FORMS    += mainwindow.ui \
    asettingwidget.ui

RESOURCES += \
    asset.qrc
