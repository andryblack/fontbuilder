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

#include "monoboxlayouter.h"
#include "../layoutdata.h"

#include <cmath>
#include <algorithm>

MonoBoxLayouter::MonoBoxLayouter(QObject *parent) :
    AbstractLayouter(parent)
{
}

struct Line {
    int min_y;
    int max_y;
    int max_h;
    int y;
    Line() : min_y(0),max_y(0),max_h(0),y(0) {}
    Line(const LayoutChar& c,int const max_h) : max_h(max_h),y(0) {
        min_y = c.y;
	max_y = c.y + max_h;
    }
    int h() const { return max_y - min_y;}
    void append(const LayoutChar& c) {
        if (c.y < min_y) {
            min_y = c.y;
	    max_y = c.y+max_h;
        }
        chars.push_back(&c);
    }

    QVector<const LayoutChar*> chars;
};

void MonoBoxLayouter::PlaceImages(const QVector<LayoutChar>& chars) {
    int h = 0;
    int w = 0;
    if (chars.isEmpty()) return;

    int maxw = -1;
    int maxh = -1;
    foreach (const LayoutChar& c, chars) {
	maxw = std::max(c.w,maxw);
	maxh = std::max(c.h,maxh);
    }
    /// speed up
    int area = chars.size() * maxw * maxh;
    int dim = ::sqrt(area);

    resize(dim,dim);
    w = width();
    h = height();


    std::vector<Line> lines;

    bool iteration = true;
    while (iteration) {
        int x = 0;
        lines.clear();
        lines.push_back(Line(chars.front(),maxh));
        iteration = false;
        foreach (const LayoutChar& c, chars) {

            if ((x+maxw)>w) {
                x = 0;
                int y = lines.back().y;
                int h = lines.back().h();
                lines.push_back(Line(c,maxh));
                lines.back().y = y + h;
            }

           if ( (lines.back().y+maxh)>h ) {
                if (w>h) {
                    resize(width(),lines.back().y+maxh);
                    h=height();
                }
                else {
                    resize(width()+maxw,height());
                    w=width();
                }
                iteration = true;
                break;
            }



            /// place
           lines.back().append(c);
           x+=maxw;

        }
    }


    w = width();
    h = height();
    int x = 0;
    foreach (const Line& line, lines) {
        x = 0;
        foreach (const LayoutChar* c , line.chars ) {
            LayoutChar l = *c;
            l.x = x;
            l.y = line.y + (c->y-line.min_y);
            place(l);
            x+=maxw;
        }

    }
}


AbstractLayouter* MonoBoxLayouterFactoryFunc (QObject* parent) {
    return new MonoBoxLayouter(parent);
}
