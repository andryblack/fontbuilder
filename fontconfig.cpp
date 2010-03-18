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
    m_bold = false;
    m_italic = false;
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

void FontConfig::setItalic(bool b) {
    if (m_italic!=b) {
        m_italic = b;
        renderingOptionsChanged();
    }
}

void FontConfig::setBold(bool b) {
    if (m_bold!=b) {
        m_bold = b;
        renderingOptionsChanged();
    }
}
