#include "layoutdata.h"
#include <QPainter>

LayoutData::LayoutData(QObject *parent) :
    QObject(parent)
{
}


void LayoutData::resize(int w,int h) {
    m_width = w;
    m_height = h;
}

void LayoutData::beginPlacing() {
    m_placed.clear();
}

void LayoutData::placeChar(const LayoutChar& c) {
  m_placed.push_back(c);
}


void LayoutData::endPlacing() {
    layoutChanged();
}
