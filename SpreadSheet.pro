#-------------------------------------------------
#
# Project created by QtCreator 2016-03-10T00:02:22
#
#-------------------------------------------------

QT       += core

QT       += gui
QT       += network
QT       += script

TARGET = SpreadSheet
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    fetcher.cpp \
    info.cpp \
    server.cpp \
    spreadsheet_service.cpp \
    token.cpp

HEADERS += \
    fetcher.h \
    info.h \
    server.h \
    spreadsheet.h \
    spreadsheet_service.h \
    token.h \
    worksheet.h
