#-------------------------------------------------
#
# Project created by QtCreator 2011-07-16T23:29:32
#
#-------------------------------------------------

include("src/fasttable/fasttable.pri")

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

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

SOURCES +=  \
            src/controller/aligndialog.cpp \
            src/controller/controllerdialog.cpp \
            src/controller/customfasttablepersonal.cpp \
            src/controller/viewdialog.cpp \
            src/main.cpp \
            src/main/mainwindow.cpp \
            src/tests/publictablewidget.cpp \
            src/tests/testdialog.cpp \
            src/tests/testframe.cpp

HEADERS  += \
            src/controller/aligndialog.h \
            src/controller/controllerdialog.h \
            src/controller/customfasttablepersonal.h \
            src/controller/viewdialog.h \
            src/main/mainwindow.h \
            src/tests/publictablewidget.h \
            src/tests/testdialog.h \
            src/tests/testframe.h

FORMS    += \
            src/controller/aligndialog.ui \
            src/controller/controllerdialog.ui \
            src/controller/viewdialog.ui \
            src/main/mainwindow.ui \
            src/tests/testdialog.ui \
            src/tests/testframe.ui

OTHER_FILES += \
            TODO.txt
