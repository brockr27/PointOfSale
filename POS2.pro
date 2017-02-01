#-------------------------------------------------
#
# Project created by QtCreator 2014-09-24T11:40:17
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = POS2
TEMPLATE = app

CONFIG += c++11

SOURCES += main.cpp\
    mainwindow.cpp \
    OrderForm.cpp \
    TableWindow.cpp \
    OrderTicket.cpp \
    MenuItem.cpp \
    Employee.cpp \
    FileSystem.cpp

HEADERS  += \
    MenuItem.h \
    Employee.h \
    OrderTicket.h \
    ReceiptTicket.h \
    TableWindow.h \
    OrderForm.h \
    MainWindow.h \
    FileSystem.h

FORMS    += \
    MainWindow.ui \
    OrderForm.ui \
    TableWindow.ui

