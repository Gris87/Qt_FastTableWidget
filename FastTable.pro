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
    src/widgets/testframe.cpp \
    src/fasttable/publictablewidget.cpp \
    src/fasttable/customfasttablewidget.cpp

HEADERS  += src/main/mainwindow.h \
        src/main/testdialog.h \
        src/fasttable/fasttablewidget.h \
    src/widgets/testframe.h \
    src/fasttable/publictablewidget.h \
    src/fasttable/customfasttablewidget.h

FORMS    += src/main/mainwindow.ui \
            src/main/testdialog.ui \
    src/widgets/testframe.ui
