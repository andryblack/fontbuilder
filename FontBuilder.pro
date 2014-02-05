# /**
# * Copyright (c) 2010-2010 Andrey AndryBlack Kunitsyn
# * email:support.andryblack@gmail.com
# *
# * Report bugs and download new versions at http://code.google.com/p/fontbuilder
# *
# * This software is distributed under the MIT License.
# *
# * Permission is hereby granted, free of charge, to any person
# * obtaining a copy of this software and associated documentation
# * files (the "Software"), to deal in the Software without
# * restriction, including without limitation the rights to use,
# * copy, modify, merge, publish, distribute, sublicense, and/or sell
# * copies of the Software, and to permit persons to whom the
# * Software is furnished to do so, subject to the following
# * conditions:
# *
# * The above copyright notice and this permission notice shall be
# * included in all copies or substantial portions of the Software.
# *
# * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
# * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
# * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
# * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
# * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
# * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
# * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
# * OTHER DEALINGS IN THE SOFTWARE.
# */
# -------------------------------------------------
# Project created by QtCreator 2010-03-15T19:36:33
# -------------------------------------------------
TARGET = FontBuilder
TEMPLATE = app
SOURCES += src/main.cpp \
    src/fontbuilder.cpp \
    src/colorbutton.cpp \
    src/fontselectframe.cpp \
    src/fontoptionsframe.cpp \
    src/fontrenderer.cpp \
    src/charactersframe.cpp \
    src/fontconfig.cpp \
    src/abstractlayouter.cpp \
    src/layoutconfig.cpp \
    src/layoutdata.cpp \
    src/layouters/linelayouter.cpp \
    src/layouterfactory.cpp \
    src/layouters/boxlayouter.cpp \
    src/layoutconfigframe.cpp \
    src/outputconfig.cpp \
    src/outputframe.cpp \
    src/abstractexporter.cpp \
    src/exporters/ghlexporter.cpp \
    src/exporterfactory.cpp \
    src/abstractimagewriter.cpp \
    src/imagewriterfactory.cpp \
    src/image/builtinimagewriter.cpp \
    src/exporters/zfiexporter.cpp \
    src/image/targawriter.cpp \
    src/fonttestframe.cpp \
    src/fonttestwidget.cpp \
    src/exporters/divoexporter.cpp \
    src/charmapdialog.cpp \
    src/charsselectwidget.cpp \
    src/exporters/nglexporter.cpp \
    src/exporters/luaexporter.cpp \
    src/fontdrawwidget.cpp \
    src/fontloader.cpp \
    src/exporters/sparrowexporter.cpp \
    src/exporters/simpleexporter.cpp \
    src/layouters/boxlayouteroptimized.cpp
HEADERS += src/fontbuilder.h \
    src/colorbutton.h \
    src/fontselectframe.h \
    src/fontoptionsframe.h \
    src/fontrenderer.h \
    src/charactersframe.h \
    src/fontconfig.h \
    src/rendererdata.h \
    src/abstractlayouter.h \
    src/layoutconfig.h \
    src/layoutdata.h \
    src/layouters/linelayouter.h \
    src/layouterfactory.h \
    src/layoutchar.h \
    src/layouters/boxlayouter.h \
    src/layoutconfigframe.h \
    src/outputconfig.h \
    src/outputframe.h \
    src/abstractexporter.h \
    src/exporters/ghlexporter.h \
    src/exporterfactory.h \
    src/abstractimagewriter.h \
    src/imagewriterfactory.h \
    src/image/builtinimagewriter.h \
    src/exporters/zfiexporter.h \
    src/image/targawriter.h \
    src/fonttestframe.h \
    src/fonttestwidget.h \
    src/exporters/divoexporter.h \
    src/charmapdialog.h \
    src/charsselectwidget.h \
    src/exporters/nglexporter.h \
    src/exporters/luaexporter.h \
    src/fontdrawwidget.h \
    src/fontloader.h \
    src/exporters/sparrowexporter.h \
    src/exporters/simpleexporter.h \
    src/layouters/boxlayouteroptimized.h
FORMS += src/fontbuilder.ui \
    src/fontselectframe.ui \
    src/fontoptionsframe.ui \
    src/charactersframe.ui \
    src/layoutconfigframe.ui \
    src/outputframe.ui \
    src/fonttestframe.ui \
    src/charmapdialog.ui
TRANSLATIONS = fontbuilder_en.ts \
    fontbuilder_ru.ts
QT += xml

DESTDIR = bin
OBJECTS_DIR = .obj
MOC_DIR = .obj
UI_DIR = .obj
TARGET = FontBuilder

INCLUDEPATH+=src/
mac { 
    INCLUDEPATH += ../include
    INCLUDEPATH += ../include/freetype2
    LIBS += -L../lib -lfreetype -lz
# macports support
    INCLUDEPATH += /opt/local/include /opt/local/include/freetype2
    LIBS += -L/opt/local/lib
}
win32 { 
    INCLUDEPATH += ../include
    INCLUDEPATH += ../include/freetype2
    LIBS += -L../lib \
        -lfreetype
}
linux*|freebsd* { 
    CONFIG += link_pkgconfig
    PKGCONFIG += freetype2
}
OTHER_FILES += fontbuilder_ru.ts \
    fontbuilder_en.ts
