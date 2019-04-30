TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp \
    documenthandler.cpp \
    porter2_stemmer.cpp \
    word.cpp \
    hashtableadapt.cpp \

HEADERS += \
    documenthandler.h \
    avlnode.h \
    avltree.h \
    util/hash.h \
    util/string_view.h \
    porter2_stemmer.h \
    word.h \
    hashtable.h \
    hashtableadapt.h \
    json.hpp

DISTFILES += \
    ../stopwords.txt
