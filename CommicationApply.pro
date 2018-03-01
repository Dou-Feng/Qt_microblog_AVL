#-------------------------------------------------
#
# Project created by QtCreator 2018-02-25T17:42:09
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CommicationApply
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
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
    ADT.cpp \
    AVLTree.cpp \
    DataDef.cpp \
    User.cpp \
    massagedialog.cpp \
    signupdialog.cpp \
    item.cpp

HEADERS += \
        mainwindow.h \
    ADT.h \
    AVLTree.h \
    DataDef.h \
    mainwindow.h \
    User.h \
    massagedialog.h \
    signupdialog.h \
    item.h

FORMS += \
        mainwindow.ui \
    massagedialog.ui \
    signupdialog.ui \
    item.ui

DISTFILES += \
    CommicationApply.pro.user \
    friends.txt \
    name.txt

RESOURCES += \
    menu.qrc \

SUBDIRS += \
    CommicationApply.pro
