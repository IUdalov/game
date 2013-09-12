#-------------------------------------------------
#
# Project created by QtCreator 2013-09-09T21:57:39
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = game
TEMPLATE = app


SOURCES += main.cpp\
    MainWindow.cpp \
    Root.cpp \
    Models.cpp \
    Object.cpp \
    Graphics.cpp \
    Resources.cpp \
    Formuls.cpp

HEADERS  += \
    MainWindow.h \
    Root.h \
    Graphics.h \
    Transport.h \
    Formuls.h \
    Models.h \
    core_includes.h \
    Object.h \
    Resources.h

OTHER_FILES += \
    ../README.txt
