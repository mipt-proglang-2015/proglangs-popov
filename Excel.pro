#-------------------------------------------------
#
# Project created by QtCreator 2015-09-12T18:52:54
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Excel
TEMPLATE = app


SOURCES += main.cpp \
    ExcelModel.cpp \
    ExcelViewDialog.cpp

HEADERS  += \
    ExcelModel.h \
    ExcelViewDialog.h

FORMS    += \
    ExcelViewDialog.ui
