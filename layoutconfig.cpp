#include "layoutconfig.h"

LayoutConfig::LayoutConfig(QObject *parent) :
    QObject(parent)
{
    m_one_pixel_offset = true;
    m_pot_image = true;
    m_offset_left = 0;
    m_offset_top = 0;
    m_offset_right = 0;
    m_offset_bottom = 0;
}


void LayoutConfig::setOnePixelOffset(bool b) {
    if (m_one_pixel_offset!=b) {
        m_one_pixel_offset = b;
        layoutConfigChanged();
    }
}

void LayoutConfig::setPotImage(bool b) {
    if (m_pot_image!=b) {
        m_pot_image = b;
        layoutConfigChanged();
    }
}

void LayoutConfig::setOffsetLeft(int v) {
    if (m_offset_left!=v) {
        m_offset_left = v;
        layoutConfigChanged();
    }
}

void LayoutConfig::setOffsetRight(int v) {
    if (m_offset_right!=v) {
        m_offset_right= v;
        layoutConfigChanged();
    }
}

void LayoutConfig::setOffsetTop(int v) {
    if (m_offset_top!=v) {
        m_offset_top= v;
        layoutConfigChanged();
    }
}

void LayoutConfig::setOffsetBottom(int v) {
    if (m_offset_bottom!=v) {
        m_offset_bottom= v;
        layoutConfigChanged();
    }
}
