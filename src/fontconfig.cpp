/**
 * Copyright (c) 2010-2010 Andrey AndryBlack Kunitsyn
 * email:support.andryblack@gmail.com
 *
 * Report bugs and download new versions at http://code.google.com/p/fontbuilder
 *
 * This software is distributed under the MIT License.
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

#include "fontconfig.h"
#if (QT_VERSION >= QT_VERSION_CHECK(5, 0, 0))
#include <QStandardPaths>
#else
#include <QDesktopServices>
#endif

FontConfig::FontConfig(QObject *parent) :
    QObject(parent)
{
    m_path = defaultFontsPath();
    m_size = 0;
    m_characters = defaultCharacters();
    m_hinting = HintingDefault;
    m_render_missing = false;
    m_antialiased = true;
    m_aamethod = AAliasingNormal;
    m_bold = 0;
    m_italic = false;
    m_width = 100.0f;
    m_height = 100.0f;
    m_line_spacing = 0;
    m_char_spacing = 0;
    m_dpi = 96;
}


const QString& FontConfig::defaultCharacters() const {
    static const QString def = " !\"#$%&'()*+,-./0123456789:;<=>?@"
                               "ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`"
                               "abcdefghijklmnopqrstuvwxyz{|}~";
    return def;
}


void FontConfig::setPath(const QString& path) {
    m_filename = QString();
    m_path = path;
}

void FontConfig::setFilename(const QString& filename) {
    if (m_filename!=filename) {
        m_filename = filename;
        m_face_index = 0;
        m_size = 0;
        fileChanged();
    }
}

void FontConfig::setFamily(const QString& family) {
    if (m_family!=family) {
        m_family = family;
        nameChanged();
    }
}

void FontConfig::setStyle(const QString& style) {
    if (m_style!=style) {
        m_style = style;
        nameChanged();
    }
}

void FontConfig::setFaceIndex(int indx) {
    if (m_face_index!=indx) {
        m_face_index = indx;
        m_size = 0;
        faceIndexChanged();
    }
}


void FontConfig::setSize(int size) {
    if (m_size!=size) {
        m_size = size;
        sizeChanged();
    }
}


void FontConfig::setCharacters(const QString& characters) {
    if (m_characters!=characters) {
        m_characters=characters;
        charactersChanged();
    }
}


void FontConfig::setHinting(int h) {
    if (m_hinting!=h) {
        m_hinting = h;
        renderingOptionsChanged();
    }
}

void FontConfig::setAntialiased(bool b) {
    if (m_antialiased!=b) {
        m_antialiased = b;
        renderingOptionsChanged();
    }
}

void FontConfig::setAntiAliasing(int b) {
    if (m_aamethod!=b) {
        m_aamethod = b;
        renderingOptionsChanged();
    }
}

void FontConfig::setRenderMissing(bool b) {
    if (m_render_missing!=b) {
        m_render_missing = b;
        renderingOptionsChanged();
    }
}

void FontConfig::setItalic(int b) {
    if (m_italic!=b) {
        m_italic = b;
        renderingOptionsChanged();
    }
}

void FontConfig::setBold(int b) {
    if (m_bold!=b) {
        m_bold = b;
        renderingOptionsChanged();
    }
}

void FontConfig::setWidth(float b) {
    if (m_width!=b) {
        m_width = b;
        sizeChanged();
    }
}

void FontConfig::setHeight(float b) {
    if (m_height!=b) {
        m_height = b;
        sizeChanged();
    }
}

void FontConfig::emmitChange() {
    fileChanged();
    nameChanged();
    sizeChanged();
}

void FontConfig::setLineSpacing(int s) {
    if (m_line_spacing!=s) {
        m_line_spacing = s;
        spacingChanged();
    }
}

void FontConfig::setCharSpacing(int s) {
    if (m_char_spacing!=s) {
        m_char_spacing = s;
        spacingChanged();
    }
}

void FontConfig::setDPI(int dpi) {
    if (m_dpi!=dpi) {
        m_dpi = dpi;
        sizeChanged();
    }
}

QString FontConfig::defaultFontsPath()
{
#if (QT_VERSION >= QT_VERSION_CHECK(5, 0, 0))
    QStringList locations = QStandardPaths::standardLocations(QStandardPaths::FontsLocation);
    if (locations.isEmpty()) {
        return "/usr/X11/share/fonts/TTF";
    }
    return locations.front();
#else
    return QDesktopServices::storageLocation(QDesktopServices::FontsLocation);
#endif
}

void FontConfig::normalize() {
    switch (m_hinting) {
    case HintingDisable:
    case HintingDefault:
    case HintingForceFreetypeAuto:
    case HintingDisableFreetypeAuto:
        break;
    default:
        m_hinting = HintingDefault;
        break;
    }
}
