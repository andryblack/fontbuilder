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
#include <QDesktopServices>

FontConfig::FontConfig(QObject *parent) :
    QObject(parent)
{
    m_path = QDesktopServices::storageLocation(QDesktopServices::FontsLocation);
    m_size = 0;
    m_characters = "!\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~";
    m_autohinting = false;
    m_render_missing = false;
    m_antialiased = true;
    m_bold = 0;
    m_italic = false;
    m_width = 100.0f;
    m_height = 100.0f;
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


void FontConfig::setAutohinting(bool b) {
    if (m_autohinting!=b) {
        m_autohinting = b;
        renderingOptionsChanged();
    }
}

void FontConfig::setAntialiased(bool b) {
    if (m_antialiased!=b) {
        m_antialiased = b;
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
