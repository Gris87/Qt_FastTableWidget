#-------------------------------------------------
#
# Project created by QtCreator 2012-04-25T10:48:37
#
#-------------------------------------------------

include("../../src/fasttable/fasttable.pri")

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = VsTableWidget
TEMPLATE = app

CONFIG (debug, debug|release) {
    DESTDIR = debug/
    OBJECTS_DIR = debug/gen
    MOC_DIR = debug/gen
    RCC_DIR = debug/gen
} else {
    DESTDIR = release/
    OBJECTS_DIR = release/gen
    MOC_DIR = release/gen
    RCC_DIR = release/gen
}

SOURCES +=  main.cpp\
            mainwindow.cpp \
            statisticsframe.cpp

HEADERS  += mainwindow.h \
            statisticsframe.h

FORMS    += mainwindow.ui \
            statisticsframe.ui