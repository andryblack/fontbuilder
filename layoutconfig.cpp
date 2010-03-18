#include "layoutconfig.h"

LayoutConfig::LayoutConfig(QObject *parent) :
    QObject(parent)
{
    m_one_pixel_offset = true;
}


void LayoutConfig::setOnePixelOffset(bool b) {
    if (m_one_pixel_offset!=b) {
        m_one_pixel_offset = b;
        layoutConfigChanged();
    }
}
