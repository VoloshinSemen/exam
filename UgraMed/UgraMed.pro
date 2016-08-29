#-------------------------------------------------
#
# Project created by QtCreator 2016-08-26T16:36:47
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = UgraMed
TEMPLATE = app


SOURCES += main.cpp\
        ugramed.cpp \
    log.cpp \
    logwidget.cpp

HEADERS  += ugramed.h \
    log.h \
    logwidget.h

FORMS    += ugramed.ui \
    logwidget.ui
