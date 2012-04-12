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
           src/fasttable/customfasttablewidget.cpp \
           src/fasttable/fasttablewidget.cpp \
           src/tests/testdialog.cpp \
           src/tests/testframe.cpp \
           src/tests/publictablewidget.cpp

HEADERS  += src/main/mainwindow.h \
           src/fasttable/customfasttablewidget.h \
           src/fasttable/fasttablewidget.h \
           src/tests/testdialog.h \
           src/tests/testframe.h \
           src/tests/publictablewidget.h

FORMS    += src/main/mainwindow.ui \
            src/tests/testdialog.ui \
            src/tests/testframe.ui

OTHER_FILES += \
    TODO.txt

