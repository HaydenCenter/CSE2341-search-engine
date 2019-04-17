TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp \
    documenthandler.cpp \
    avltree.cpp

HEADERS += \
    documenthandler.h \
    avlnode.h \
    avltree.h
