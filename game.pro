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
    INDIan/main_window.cpp \
    INDIan/formuls.cpp \
    INDIan/graphics.cpp \
    INDIan/root.cpp \
    INDIan/models.cpp \
    INDIan/obj_manager.cpp \
    INDIan/object.cpp \
    INDIan/resources.cpp \
    resources_declaretion.cpp \
    example_model.cpp \
    physics/physics.cpp

HEADERS  += \
    INDIan/core_includes.h \
    physics/param.h \
    physics/data.h \
    physics/physics.h \
    INDIan/formuls.h \
    INDIan/graphics.h \
    INDIan/main_window.h \
    INDIan/models.h \
    INDIan/obj_manager.h \
    INDIan/object.h \
    INDIan/resources.h \
    INDIan/root.h \
    INDIan/transport.h \
    INDIan/dependences.h \
    example_model.h

OTHER_FILES += \
    ../README.txt \
    Build/Images/Untitled.bmp \
    Build/Images/mask.bmp \
    README.md \
    Build/Images/arrow_mask.bmp \
    Build/Images/arrow.bmp
