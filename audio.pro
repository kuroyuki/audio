#-------------------------------------------------
#
# Project created by QtCreator 2015-03-04T08:08:03
#
#-------------------------------------------------

QT       += core

QT       += gui sql

TARGET = audio
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    audiorecognition.cpp \
    dojo/dojo.cpp \
    dojo/dojonode.cpp \
    dojo/dojosynapse.cpp \
    dojo/dojostructs.cpp

HEADERS += \
    audiorecognition.h \
    dojo/dojo.h \
    dojo/dojonode.h \
    dojo/dojosynapse.h \
    dojo/dojostructs.h
