#-------------------------------------------------
#
# Project created by QtCreator 2019-08-06T16:05:38
#
#-------------------------------------------------

QT       += core gui
QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DrevoPowerConsole
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    qkeyboardctrl.cpp \
    qkeyboardctrl_init.cpp \
    customkeywidget.cpp \
    custombutton.cpp \
    customknobwidget.cpp \
    keysetwidget.cpp \
    radilightwidget.cpp \
    devicecomm.cpp \
    devicedb.cpp \
    qtkeyboardkey.cpp

HEADERS += \
        mainwindow.h \
    qkeyboardctrl.h \
    customkeywidget.h \
    custombutton.h \
    customknobwidget.h \
    keysetwidget.h \
    radilightwidget.h \
    devicecomm.h \
    devicedb.h \
    keyboarddata.h \
    qtkeyboardkey.h

FORMS += \
        mainwindow.ui \
    customkeywidget.ui \
    customknobwidget.ui \
    keysetwidget.ui \
    radilightwidget.ui

RESOURCES += \
    keyboard_layout.qrc

LIBS += -L"usr/local/lib" -lusb-1.0
LIBS += -L"./lib/" -lhidkeyboard

DISTFILES +=
