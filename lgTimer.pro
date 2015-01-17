#-------------------------------------------------
#
# Project created by QtCreator 2015-01-17T16:12:59
#
#-------------------------------------------------

QT       += core \
    gui \
    multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = lgTimer
TEMPLATE = app

ICON = icons/timer.icns

SOURCES += main.cpp\
        mainwindow.cpp \
    settings.cpp

HEADERS  += mainwindow.h \
    settings.h

FORMS    += mainwindow.ui \
    settings.ui

RESOURCES += \
    icons.qrc
