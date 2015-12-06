#-------------------------------------------------
#
# Project created by QtCreator 2015-09-12T18:52:54
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Excel
TEMPLATE = app

INCLUDEPATH += /usr/include/python3.4m
LIBS += -L/usr/lib/x86_64-linux-gnu
LIBS += -Wl,-Bstatic -lpython3.4m -Wl,-Bdynamic
LIBS += -lz -lexpat -ldl -lutil

SOURCES += main.cpp \
    ExcelViewDialog.cpp \
    AbstractInterpreter.cpp \
    InterpreterFactory.cpp \
    PythonInterpreter.cpp \
    Actor.cpp

HEADERS  += \
    ExcelViewDialog.h \
    Constants.h \
    AbstractInterpreter.h \
    InterpreterFactory.h \
    PythonInterpreter.h \
    Actor.h

FORMS    += \
    ExcelViewDialog.ui

OTHER_FILES += \
    Excel.pro.user \
    test.txt
