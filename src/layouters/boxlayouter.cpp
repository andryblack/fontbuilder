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

#include <cmath>

BoxLayouter::BoxLayouter(QObject *parent) :
    AbstractLayouter(parent)
{
}

struct Line {
    int min_y;
    int max_y;
    int y;
    Line() : min_y(0),max_y(0),y(0) {}
    explicit Line(const LayoutChar& c) : y(0) {
        min_y = c.y;
        max_y = c.y + c.h;
        //chars.push_back(&c);
    }
    int h() const { return max_y - min_y;}
    void append(const LayoutChar& c) {
        if (c.y < min_y)
            min_y = c.y;
        if ((c.y+c.h)>max_y)
            max_y = c.y + c.h;
        chars.push_back(&c);
    }

    QVector<const LayoutChar*> chars;
};

struct SortCharsByHeight
{
    bool operator()(const LayoutChar &a, const LayoutChar &b)
    {
        if (a.h + a.y > b.h + b.y)
            return false;
        else if (a.h + a.y == b.h + b.y)
        {
            if (a.w > b.w)
                return false;
            else if (a.w == b.w)
            {
                if (a.y > b.y)
                    return false;
                else if (a.y == b.y)
                {
                    if (a.symbol > b.symbol)
                        return false;
                }
            }
        }
        return true;
    }
};

void BoxLayouter::PlaceImages(const QVector<LayoutChar>& inputChars) {
    int h = 0;
    int w = 0;
    if (inputChars.isEmpty()) return;

    QVector<LayoutChar> chars(inputChars);
    std::sort(chars.begin(), chars.end(), SortCharsByHeight());

    /// speed up
    int area = 0;
    foreach (const LayoutChar& c, chars)
        area+=c.w*c.h;
    int dim = ::sqrt(area);

    resize(dim,dim);
    w = width();
    h = height();


    QVector<Line> lines;

    bool iteration = true;
    while (iteration) {
        int x = 0;
        lines.clear();
        lines.push_back(Line(chars.front()));
        iteration = false;
        foreach (const LayoutChar& c, chars) {

            if ((x+c.w)>w) {
                x = 0;
                int y = lines.back().y;
                int h = lines.back().h();
                lines.push_back(Line(c));
                lines.back().y = y + h;
            }

           if ( (lines.back().y+c.h)>h ) {
                if (w>h) {
                    resize(width(),lines.back().y+c.h);
                    h=height();
                }
                else {
                    resize(width()+c.w,height());
                    w=width();
                }
                iteration = true;
                break;
            }



            /// place
           lines.back().append(c);
           x+=c.w;

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
            x+=c->w;
        }

    }
}


AbstractLayouter* BoxLayouterFactoryFunc (QObject* parent) {
    return new BoxLayouter(parent);
}
