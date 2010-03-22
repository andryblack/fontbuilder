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

#include "boxlayouter.h"
#include "../layoutdata.h"

BoxLayouter::BoxLayouter(QObject *parent) :
    AbstractLayouter(parent)
{
}

void BoxLayouter::PlaceImages(const QVector<LayoutChar>& chars) {
    int h = 0;
    int w = 0;
    if (!chars.isEmpty()) {
        resize(chars.front().w,chars.front().h);
        w = width();
        h = height();

        bool iteration = true;
        while (iteration) {
            int x = 0;
            int y = 0;
            int line_h = chars.front().h;
            iteration = false;
            foreach (const LayoutChar& c, chars) {

                if ((x+c.w)>w) {
                    x = 0;
                    y+=line_h;
                    line_h = c.h;
                }

               if ( (y+c.h)>h ) {
                    if (w>h) {
                        resize(width(),y+c.h);
                        h=height();
                    }
                    else {
                        resize(width()+c.w,height());
                        w=width();
                    }
                    iteration = true;
                    break;
                }

                if (c.h>line_h)
                    line_h = c.h;

                /// place
                x+=c.w;

            }
        }
    }

    w = width();
    h = height();
    int x = 0;
    int y = 0;
    int line_h = 0;
    foreach (const LayoutChar& c, chars) {

        if ((x+c.w)>w) {
            x = 0;
            y+=line_h;
            line_h = c.h;
        }

        if (c.h>line_h)
            line_h = c.h;

        LayoutChar l = c;
        l.x = x;
        l.y = y;
        place(l);

        x+=c.w;

    }
}


AbstractLayouter* BoxLayouterFactoryFunc (QObject* parent) {
    return new BoxLayouter(parent);
}
