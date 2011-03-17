/**
 * Copyright (c) 2010-2011 Andrey AndryBlack Kunitsyn
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

#include "fontdrawwidget.h"
#include <QPainter>

FontDrawWidget::FontDrawWidget(QWidget *parent) :
    QWidget(parent)
{
    m_scale = 1.0f;
    m_draw_grid = true;

    m_layout_data = 0;
    m_renderer_data = 0;
    m_layout_config = 0;

}


void FontDrawWidget::setImage(const QImage& image) {

    QSize size =image.size();
    setFixedSize(size*m_scale);
    m_image = image;
    repaint();
}

void FontDrawWidget::setDrawGrid(bool draw) {
    m_draw_grid = draw;
    repaint();
}


void FontDrawWidget::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    painter.setCompositionMode(QPainter::CompositionMode_Source);
    painter.setRenderHint(QPainter::SmoothPixmapTransform,false);
    painter.setRenderHint(QPainter::Antialiasing,false);
    painter.drawImage(rect(),m_image);
    if (!m_draw_grid) return;
    if (!m_layout_data) return;
    if (!m_renderer_data) return;
    if (!m_layout_config) return;

    foreach (const LayoutChar& c,m_layout_data->placed()) {
        if (m_renderer_data->chars[c.symbol].locked)
            painter.setPen(QColor(255,0,0,255));
        else
            painter.setPen(QColor(0,0,255,255));
        painter.drawRect((c.x)*m_scale,(c.y)*m_scale,(c.w)*m_scale-1,(c.h)*m_scale-1);
    }
}

void FontDrawWidget::setScale(float s) {
    m_scale = s;
    QSize size = m_image.size();
    setFixedSize(size*m_scale);
    repaint();
}
