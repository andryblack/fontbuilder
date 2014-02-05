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

#include "abstractlayouter.h"
#include "layoutdata.h"
#include "layoutconfig.h"

AbstractLayouter::AbstractLayouter(QObject *parent) :
    QObject(parent)
{
    m_config = 0;
    m_data = 0;
}


void AbstractLayouter::setConfig(const LayoutConfig* config) {
    m_config = config;
    connect(m_config,SIGNAL(layoutConfigChanged()),this,SLOT(on_LayoutDataChanged()));
}

void AbstractLayouter::setData(LayoutData* data) {
    m_data = data;
}

void AbstractLayouter::DoPlace(const QVector<LayoutChar>& chars) {
    m_data->beginPlacing();
    m_compact_w = 0;
    m_compact_h = 0;
    PlaceImages(chars);
    resize(m_compact_w,m_compact_h);
    m_data->endPlacing();
}

void AbstractLayouter::OptimizeLayout(QVector<LayoutChar> &)
{
}

void AbstractLayouter::on_ReplaceImages(const QVector<LayoutChar>& chars) {
    m_chars = chars;

    if (m_data!=0 && m_config!=0 ) {
        on_LayoutDataChanged();
    }
}


void AbstractLayouter::on_LayoutDataChanged() {
    if (m_data!=0 && m_config!=0 ) {
        QVector<LayoutChar> chars = m_chars;
        {
            for( int i=0;i<m_chars.size();i++) {
                if (m_config->onePixelOffset()) {
                    chars[i].w++;
                    chars[i].h++;
                }
                chars[i].w+=m_config->offsetLeft()+m_config->offsetRight();
                chars[i].h+=m_config->offsetTop()+m_config->offsetBottom();
            }
        }
        OptimizeLayout(chars);
        DoPlace(chars);
    }
}

static unsigned int nextpot(unsigned int val) {
    val--;
    val = (val >> 1) | val;
    val = (val >> 2) | val;
    val = (val >> 4) | val;
    val = (val >> 8) | val;
    val = (val >> 16) | val;
    val++;
    return val;
}

void AbstractLayouter::resize(int w,int h) {
    if (m_config) {
        if (m_config->onePixelOffset())
        {
            w+=2;
            h+=2;
        }

        if (m_config->potImage()) {
            w = nextpot(w);
            h = nextpot(h);
        }

        int sizeIncrement = m_config->sizeIncrement();
        if (sizeIncrement > 1)
        {
            w = ((w + sizeIncrement - 1) / sizeIncrement) * sizeIncrement;
            h = ((h + sizeIncrement - 1) / sizeIncrement) * sizeIncrement;
        }
    }
    if (m_data) {
        m_data->resize(w,h);
    }
}

int AbstractLayouter::width() const {
    int w = 0;
    if (m_data) {
        w = m_data->width();
    }
    if (m_config) {
        if (m_config->onePixelOffset())
            w-=2;
    }
    return w;
}
int AbstractLayouter::height() const {
    int h= 0;
    if (m_data) {
        h = m_data->height();
    }
    if (m_config) {
        if (m_config->onePixelOffset())
            h-=2;
    }
    return h;
}
void AbstractLayouter::place(const LayoutChar& c) {
    LayoutChar out = c;
    if ((out.x + out.w)>m_compact_w)
        m_compact_w = out.x + out.w;
    if ((out.y + out.h)>m_compact_h)
        m_compact_h = out.y + out.h;
    if (m_config) {
        if (m_config->onePixelOffset()) {
            out.x++;
            out.y++;
            out.w--;
            out.h--;
        }
    }
    if (m_data)
        m_data->placeChar(out);

}
