#-------------------------------------------------
#
# Project created by QtCreator 2011-07-16T23:29:32
#
#-------------------------------------------------

QT       += core gui

TARGET = FastTable
TEMPLATE = app

RC_FILE = Resources.rc
RESOURCES += Resources.qrc

SOURCES += src/main.cpp\
           src/main/mainwindow.cpp \
           src/fasttable/customfasttablewidget.cpp \
           src/fasttable/fasttablewidget.cpp \
           src/tests/testdialog.cpp \
           src/tests/testframe.cpp \
           src/tests/publictablewidget.cpp \
           src/controller/controllerdialog.cpp \
           src/controller/viewdialog.cpp \
           src/controller/aligndialog.cpp

HEADERS  += src/main/mainwindow.h \
            src/fasttable/customfasttablewidget.h \
            src/fasttable/fasttablewidget.h \
            src/tests/testdialog.h \
            src/tests/testframe.h \
            src/tests/publictablewidget.h \
            src/controller/controllerdialog.h \
            src/controller/viewdialog.h \
            src/controller/aligndialog.h \
            src/fasttable/fastdefines.h

FORMS    += src/main/mainwindow.ui \
            src/tests/testdialog.ui \
            src/tests/testframe.ui \
            src/controller/controllerdialog.ui \
            src/controller/viewdialog.ui \
            src/controller/aligndialog.ui

OTHER_FILES += \
    TODO.txt
