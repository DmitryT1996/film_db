#-------------------------------------------------
#
# Project created by QtCreator 2017-07-21T15:13:23
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Database
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    addrecord.cpp \
    inform.cpp

HEADERS  += mainwindow.h \
    addrecord.h \
    inform.h

FORMS    += mainwindow.ui \
    addrecord.ui \
    inform.ui
