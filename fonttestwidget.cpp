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
#include "fontconfig.h"

#include <QPaintEvent>
#include <QPainter>


FontTestWidget::FontTestWidget(QWidget *parent) :
    QWidget(parent) , m_layout_data(0),m_renderer_data(0),m_font_config(0)
{
    setUseKerning(false);
    m_align = ALIGN_CENTER;
}


const LayoutChar*   FontTestWidget::layoutChar(ushort c) const {
    foreach (const LayoutChar& lc, m_layout_data->placed()) {
        if (c==lc.symbol)
            return &lc;
    }
    return 0;
}

int FontTestWidget::lineWidth(const ushort* chars) const {
    int x = 0;
    while (*chars) {
        ushort c = *chars++;
        if (c=='\n') {
            break;
        } else
        if (m_renderer_data->chars.contains(c)) {
            const RenderedChar& rendered = m_renderer_data->chars[c];
            x+=rendered.advance + m_font_config->charSpacing();
            if (useKerning() && (*chars!=0)) {
                if (rendered.kerning.contains(*chars)) {
                    x+=rendered.kerning[*chars];
                }
            }
        }

    }
    return x;
}

void	FontTestWidget::paintEvent ( QPaintEvent * event ) {
    if (!m_renderer_data || !m_layout_data || !m_font_config) return;
    Q_UNUSED(event);
    calcBBox();
    QPainter painter(this);
    painter.fillRect(rect(),QBrush(QColor(0,0,0)));
    if (!m_renderer_data || !m_layout_data) return;

    int x = m_left;

    int y = m_top;
    const ushort* chars = m_text.utf16();

    if (m_align!=ALIGN_LEFT) {
        int width = lineWidth(chars);
        if (m_align==ALIGN_RIGHT) {
            x = m_left+m_width-width;
        } else {
            x = m_left+(m_width-width)/2;
        }
    }
    while (*chars) {
        ushort c = *chars++;
        if (c=='\n') {
            x = m_left;
            if (m_align!=ALIGN_LEFT) {
                int width = lineWidth(chars);
                if (m_align==ALIGN_RIGHT) {
                    x = m_left+m_width-width;
                } else {
                    x = m_left+(m_width-width)/2;
                }
            }
            y += m_renderer_data->metrics.height+m_font_config->lineSpacing();
        } else
        if (m_renderer_data->chars.contains(c)) {
            const RenderedChar& rendered = m_renderer_data->chars[c];
            const LayoutChar* layout = layoutChar(c);
            if (layout) {
                painter.drawImage(x+rendered.offsetX,y-rendered.offsetY,
                                  m_layout_data->image(),
                                  layout->x,layout->y,
                                  layout->w,layout->h);
            }
            x+=rendered.advance + m_font_config->charSpacing();
            if (useKerning() && (*chars!=0)) {
                if (rendered.kerning.contains(*chars)) {
                    x+=rendered.kerning[*chars];
                }
            }
        }

    }
}

void FontTestWidget::calcBBox() {
    if (!m_renderer_data || !m_layout_data || !m_font_config) return;
    int left = 0;
    int right = 1;
    int top = 0;
    int bottom = 1;
    const ushort* chars = m_text.utf16();
    int x = left;
    int y = top;
    int max_x = x;
    bool first = true;
    bool last = false;
    while (*chars) {
        ushort c = *chars++;
        if (c=='\n') {
            x=0;
            y += m_renderer_data->metrics.height+m_font_config->lineSpacing();
            first = true;
        } else
        if (m_renderer_data->chars.contains(c)) {
            const RenderedChar& rendered = m_renderer_data->chars[c];
            const LayoutChar* layout = layoutChar(c);
            if (!layout) continue;
            last = (*chars=='\n')||(*chars==0);
            if ( first ) {
                if ( (rendered.offsetX) < left)
                    left = rendered.offsetX;
            }
            if (last) {
                if ( (rendered.offsetX+layout->w-rendered.advance - m_font_config->charSpacing()) > right)
                    right = rendered.offsetX+layout->w-rendered.advance - m_font_config->charSpacing();
            }
            {
                if ( (y-rendered.offsetY) < top)
                    top = y-rendered.offsetY;
                if ( (y-rendered.offsetY+layout->h) > bottom)
                    bottom = y-rendered.offsetY+layout->h;
            }
            x+=rendered.advance + m_font_config->charSpacing();
            first = false;
            if (useKerning() && (*chars!=0)) {
                if (rendered.kerning.contains(*chars)) {
                    x+=rendered.kerning[*chars];
                }
            }
            if (x>max_x)
                max_x = x;
        }


    }

    m_left = -left+1;
    m_width = max_x;
    m_top = -top+1;
    resize(max_x+right-left+2,bottom-top+2);
    setMinimumSize(max_x+right-left+2,bottom-top+2);
}

void FontTestWidget::setText(const QString& text) {
    m_text = text;
    refresh();
}

void FontTestWidget::refresh() {

    repaint();
}
