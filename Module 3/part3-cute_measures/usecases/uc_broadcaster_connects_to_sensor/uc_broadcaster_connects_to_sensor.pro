#-------------------------------------------------
#
# Project created by QtCreator 2017-11-16T14:38:36
#
#-------------------------------------------------

QT       += testlib

QT       -= gui

TARGET = tst_uc_broadcaster_connects_to_sensor
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

include(uc_broadcaster_connects_to_sensor.pri)
include(../../entities/entities.pri)

SOURCES += tst_uc_broadcaster_connects_to_sensor.cpp

DEFINES += SRCDIR=\\\"$$PWD/\\\"

