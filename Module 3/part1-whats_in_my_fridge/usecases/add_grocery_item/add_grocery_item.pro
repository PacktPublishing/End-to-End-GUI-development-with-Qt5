#-------------------------------------------------
#
# Project created by QtCreator 2017-09-18T10:31:50
#
#-------------------------------------------------

QT       += testlib

QT       -= gui

TARGET = tst_add_grocery_item
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

include(../../entities/entities.pri)
include(../../repositories/repositories.pri)
include(../check_available_groceries/check_available_groceries.pri)
include(add_grocery_item.pri)

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        tst_add_grocery_item.cpp 

DEFINES += SRCDIR=\\\"$$PWD/\\\"
