#-------------------------------------------------
#
# Project created by QtCreator 2011-07-16T23:29:32
#
#-------------------------------------------------

QT       += core gui

TARGET = FastTable
TEMPLATE = app


SOURCES += src/main.cpp\
        src/main/mainwindow.cpp \
        src/main/testdialog.cpp \
        src/fasttable/fasttablewidget.cpp \
        src/fasttable/fasttabletest.cpp

HEADERS  += src/main/mainwindow.h \
        src/main/testdialog.h \
        src/fasttable/fasttablewidget.h \
        src/fasttable/fasttabletest.h

FORMS    += src/main/mainwindow.ui \
            src/main/testdialog.ui

OTHER_FILES += \
    README \
    push.sh \
    .gitignore
