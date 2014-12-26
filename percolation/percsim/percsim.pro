#-------------------------------------------------
#
# Project created by QtCreator 2014-12-18T21:42:23
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = percsim
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    newdialog.cpp \
    percwidget.cpp \
    percwindow.cpp \
    percthread.cpp \
    unionfind.cpp \
    percolation.cpp \
    quickfind.cpp \
    quickunion.cpp \
    weightedquickunion.cpp \
    percpicture.cpp \
    quickunioncompressed.cpp \
    stopwatch.cpp

HEADERS  += mainwindow.h \
    newdialog.h \
    percwidget.h \
    percwindow.h \
    percthread.h \
    percolation.h \
    perctype.h \
    unionfind.h \
    quickfind.h \
    quickunion.h \
    weightedquickunion.h \
    percpicture.h \
    quickunioncompressed.h \
    stopwatch.h

FORMS    += mainwindow.ui \
    newdialog.ui
