#-------------------------------------------------
#
# Project created by QtCreator 2013-09-09T21:57:39
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = game
TEMPLATE = app


SOURCES += INDIan/main.cpp\
    INDIan/MainWindow.cpp \
    INDIan/Root.cpp \
    INDIan/Models.cpp \
    INDIan/Object.cpp \
    INDIan/Graphics.cpp \
    INDIan/Resources.cpp \
    INDIan/Formuls.cpp

HEADERS  += \
    INDIan/MainWindow.h \
    INDIan/Root.h \
    INDIan/Graphics.h \
    INDIan/Transport.h \
    INDIan/Formuls.h \
    INDIan/Models.h \
    INDIan/core_includes.h \
    INDIan/Object.h \
    INDIan/Resources.h \
    physics/param.h \
    physics/data.h \
    physics/physics.h

OTHER_FILES += \
    ../README.txt
