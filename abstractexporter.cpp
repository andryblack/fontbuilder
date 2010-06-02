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

#include "abstractexporter.h"
#include "layoutdata.h"
#include "layoutconfig.h"
#include "rendererdata.h"
#include "fontconfig.h"

AbstractExporter::AbstractExporter(QObject *parent) :
    QObject(parent)
{
    m_extension = "font";
    m_tex_width = 0;
    m_tex_height = 0;
}


void AbstractExporter::setData(const LayoutData* data,const RendererData& rendered) {
    m_metrics = rendered.metrics;
    m_metrics.height+=fontConfig()->lineSpacing();
    m_symbols.clear();
    foreach ( const LayoutChar& lc, data->placed()) {
        Symbol symb;
        symb.id = lc.symbol;
        symb.placeX = lc.x;
        symb.placeY = lc.y;
        symb.placeW = lc.w;
        symb.placeH = lc.h;
        const RenderedChar& rc = rendered.chars[symb.id];
        symb.offsetX = rc.offsetX-layoutConfig()->offsetLeft();
        symb.offsetY = rc.offsetY+layoutConfig()->offsetTop();
        symb.advance = rc.advance + fontConfig()->charSpacing();
        symb.kerning = rc.kerning;
        m_symbols.push_back(symb);
    }
    m_tex_width = data->width();
    m_tex_height = data->height();
}


bool AbstractExporter::Write(QByteArray& bytes) {
    if (Export(bytes)) {
       return true;
    }
    return false;
}

