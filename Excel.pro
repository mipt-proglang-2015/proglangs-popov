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
LIBS += -lpython3.4m -lpthread -ldl  -lutil -lm  -Xlinker -export-dynamic


SOURCES += main.cpp \
    ExcelViewDialog.cpp \
    AbstractInterpreter.cpp \
    InterpreterFactory.cpp \
    PythonInterpreter.cpp

HEADERS  += \
    ExcelViewDialog.h \
    Constants.h \
    AbstractInterpreter.h \
    InterpreterFactory.h \
    PythonInterpreter.h

FORMS    += \
    ExcelViewDialog.ui

OTHER_FILES += \
    Excel.pro.user \
    test.txt
