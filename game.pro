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
    INDIan/obj_manager.cpp \
    INDIan/formuls.cpp \
    INDIan/graphics.cpp \
    INDIan/main_window.cpp \
    INDIan/models.cpp \
    INDIan/object.cpp \
    INDIan/resources.cpp \
    INDIan/root.cpp \
    resources_declaretion.cpp \
    example_model.cpp

HEADERS  += \
    INDIan/core_includes.h \
    physics/param.h \
    physics/data.h \
    physics/physics.h \
    INDIan/obj_manager.h \
    ../Virus War/INDIan/CORE/ObjManager.h \
    INDIan/formuls.h \
    INDIan/graphics.h \
    INDIan/main_window.h \
    INDIan/models.h \
    INDIan/object.h \
    INDIan/resources.h \
    INDIan/root.h \
    INDIan/transport.h \
    INDIan/dependences.h \
    example_model.h

OTHER_FILES += \
    ../README.txt
