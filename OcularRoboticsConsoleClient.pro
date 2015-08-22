#-------------------------------------------------
#
# Project created by QtCreator 2015-08-18T22:33:22
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = OcularRoboticsConsoleClient
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp\
        udphost.cpp

HEADERS  += mainwindow.h\
            udphost.h

FORMS    += mainwindow.ui
