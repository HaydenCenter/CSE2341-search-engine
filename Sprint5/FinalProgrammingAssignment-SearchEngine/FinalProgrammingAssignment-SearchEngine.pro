TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp \
    documenthandler.cpp \
    avltree.cpp \
    porter2_stemmer.cpp

HEADERS += \
    documenthandler.h \
    avlnode.h \
    avltree.h \
    util/hash.h \
    util/string_view.h \
    porter2_stemmer.h \
    json.hpp

DISTFILES += \
    ../stopwords.txt
