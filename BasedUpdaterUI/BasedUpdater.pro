#-------------------------------------------------
#
# Project created by QtCreator 2015-09-09T23:59:35
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

LIBS += -lws2_32

TARGET = BasedUpdater
TEMPLATE = app

SOURCES += main.cpp\
    basedupdater.cpp \
    aboutdialog.cpp

HEADERS  += basedupdater.h \
    aboutdialog.h

FORMS    += basedupdater.ui \
    dialog.ui \
    aboutdialog.ui
