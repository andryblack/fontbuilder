# -------------------------------------------------
# Project created by QtCreator 2010-03-15T19:36:33
# -------------------------------------------------
TARGET = FontBuilder
TEMPLATE = app
SOURCES += main.cpp \
    fontbuilder.cpp \
    colorbutton.cpp \
    fontselectframe.cpp \
    fontoptionsframe.cpp \
    fontrenderer.cpp \
    charactersframe.cpp \
    fontconfig.cpp \
    abstractlayouter.cpp \
    layoutconfig.cpp \
    layoutdata.cpp \
    layouters/linelayouter.cpp \
    layouterfactory.cpp \
    layouters/boxlayouter.cpp \
    layoutconfigframe.cpp
HEADERS += fontbuilder.h \
    colorbutton.h \
    fontselectframe.h \
    fontoptionsframe.h \
    fontrenderer.h \
    charactersframe.h \
    fontconfig.h \
    rendererdata.h \
    abstractlayouter.h \
    layoutconfig.h \
    layoutdata.h \
    layouters/linelayouter.h \
    layouterfactory.h \
    layoutchar.h \
    layouters/boxlayouter.h \
    layoutconfigframe.h
FORMS += fontbuilder.ui \
    fontselectframe.ui \
    fontoptionsframe.ui \
    charactersframe.ui \
    layoutconfigframe.ui
mac { 
    INCLUDEPATH += /Users/andry/src/include
    INCLUDEPATH += /Users/andry/src/include/freetype2
    LIBS += -L/Users/andry/src/lib \
        -lfreetype
}
unix { 
    CONFIG += link_pkgconfig
    PKGCONFIG += freetype2
}
/**test**/
