#-------------------------------------------------
#
# Project created by QtCreator 2013-12-18T16:50:38
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = fractalExplorer
TEMPLATE = app


SOURCES += main.cpp \
        mainwindow.cpp \
    fractal.cpp \
    fractalexplorer.cpp \
    fractalmandelbrot.cpp \
    fractaltricorn.cpp \
    fractalburningship.cpp

HEADERS  += mainwindow.h \
    fractal.h \
    fractalexplorer.h \
    fractalmandelbrot.h \
    fractaltricorn.h \
    fractalburningship.h

FORMS    += mainwindow.ui
