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

#include "fonttestwidget.h"
#include "layoutdata.h"
#include "rendererdata.h"

#include <QPaintEvent>
#include <QPainter>


FontTestWidget::FontTestWidget(QWidget *parent) :
    QWidget(parent) , m_layout_data(0),m_renderer_data(0)
{
    setUseKerning(false);
}


const LayoutChar*   FontTestWidget::layoutChar(ushort c) const {
    foreach (const LayoutChar& lc, m_layout_data->placed()) {
        if (c==lc.symbol)
            return &lc;
    }
    return 0;
}

void	FontTestWidget::paintEvent ( QPaintEvent * event ) {
    Q_UNUSED(event);
    calcBBox();
    QPainter painter(this);
    painter.fillRect(rect(),QBrush(QColor(0,0,0)));
    if (!m_renderer_data || !m_layout_data) return;
    int left = 0;
    int x = m_left;
    int y = m_top;
    const ushort* chars = m_text.utf16();
    while (*chars) {
        ushort c = *chars++;
        if (m_renderer_data->chars.contains(c)) {
            const RenderedChar& rendered = m_renderer_data->chars[c];
            const LayoutChar* layout = layoutChar(c);
            if (layout) {
                painter.drawImage(x+rendered.offset_x,y-rendered.offset_y,
                                  m_layout_data->image(),
                                  layout->x,layout->y,
                                  layout->w,layout->h);
            }
            x+=rendered.advance;
            if (useKerning() && (*chars!=0)) {
                if (rendered.kerning.contains(*chars)) {
                    x+=rendered.kerning[*chars];
                }
            }
        }
        if (c=='\n') {
            x = left;
            y += m_renderer_data->metrics.height;
        }
    }
}

void FontTestWidget::calcBBox() {
    if (!m_renderer_data || !m_layout_data) return;
    int left = 0;
    int right = 1;
    int top = 0;
    int bottom = 1;
    const ushort* chars = m_text.utf16();
    int x = left;
    int y = top;
    while (*chars) {
        ushort c = *chars++;
        if (m_renderer_data->chars.contains(c)) {
            const RenderedChar& rendered = m_renderer_data->chars[c];
            const LayoutChar* layout = layoutChar(c);

            if ( layout ) {
                if ( (x+rendered.offset_x) < left)
                    left = x+rendered.offset_x;
                if ( (x+rendered.offset_x+layout->w) > right)
                    right = x+rendered.offset_x+layout->w;
                if ( (y-rendered.offset_y) < top)
                    top = y-rendered.offset_y;
                if ( (y-rendered.offset_y+layout->h) > bottom)
                    bottom = y-rendered.offset_y+layout->h;
            }
            x+=rendered.advance;
            if (useKerning() && (*chars!=0)) {
                if (rendered.kerning.contains(*chars)) {
                    x+=rendered.kerning[*chars];
                }
            }
        }
        if (c=='\n') {
            x=left;
            y+=m_renderer_data->metrics.height;
        }

    }

    m_left = -left+1;
    m_top = -top+1;
    resize(right-left+2,bottom-top+2);
    setMinimumSize(right-left+2,bottom-top+2);
}

void FontTestWidget::setText(const QString& text) {
    m_text = text;
    refresh();
}

void FontTestWidget::refresh() {

    repaint();
}
