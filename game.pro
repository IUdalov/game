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
    physics/physics.cpp \
    inits/resources_declarations.cpp \
    models/field.cpp \
    models/checker_manager.cpp \
    models/menu.cpp \
    models/show_menu.cpp \
    INDIan/geo.cpp \
    inits/declarations.cpp

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
    inits/declarations.h \
    models/field.h \
    models/checker_manager.h \
    models/menu.h \
    INDIan/geo.h
    inits/declarations.h

OTHER_FILES += \
    ../README.txt \
    images/Untitled.bmp \
    images/mask.bmp \
    README.md \
    images/arrow_mask.bmp \
    images/arrow.bmp \
    images/cell_mask.bmp \
    images/cell.bmp \
    images/small_ch_mask.bmp \
    images/small_checker2.bmp \
    images/small_checker.bmp \
    images/small_ch2_mask.bmp \
    images/middle_ch_mask.bmp \
    images/middle_checker2.bmp \
    images/middle_checker.bmp \
    images/middle_ch2_mask.bmp \
    images/button_play_mask.bmp \
    images/button_play.bmp \
    images/big_ch_mask.bmp \
    images/big_checker2.bmp \
    images/big_checker.bmp \
    images/big_ch2_mask.bmp \
    images/selector_small_mask.bmp \
    images/selector_small.bmp \
    images/selector_middle_mask.bmp \
    images/selector_middle.bmp \
    images/selector_big_mask.bmp \
    images/selector_big.bmp
