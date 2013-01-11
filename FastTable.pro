#-------------------------------------------------
#
# Project created by QtCreator 2011-07-16T23:29:32
#
#-------------------------------------------------

include("src/fasttable/fasttable.pri")

QT       += core gui

TARGET = FastTable
TEMPLATE = app

RC_FILE = Resources.rc
RESOURCES += Resources.qrc

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

SOURCES +=  src/main.cpp\
            src/main/mainwindow.cpp \
            src/tests/testdialog.cpp \
            src/tests/testframe.cpp \
            src/tests/publictablewidget.cpp \
            src/controller/controllerdialog.cpp \
            src/controller/viewdialog.cpp \
            src/controller/aligndialog.cpp

HEADERS  += src/main/mainwindow.h \
            src/tests/testdialog.h \
            src/tests/testframe.h \
            src/tests/publictablewidget.h \
            src/controller/controllerdialog.h \
            src/controller/viewdialog.h \
            src/controller/aligndialog.h

FORMS    += src/main/mainwindow.ui \
            src/tests/testdialog.ui \
            src/tests/testframe.ui \
            src/controller/controllerdialog.ui \
            src/controller/viewdialog.ui \
            src/controller/aligndialog.ui

OTHER_FILES += \
    TODO.txt
