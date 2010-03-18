/**
 * Copyright (C) 2010-2010, by Andrey AndryBlack Kunitsyn
 * (support.andryblack@gmail.com)
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
    }
    bool iteration = true;
    while (iteration) {
        int x = 0;
        int y = 0;
        int line_h = 0;
        iteration = false;
        foreach (const LayoutChar& c, chars) {
            if (c.h>line_h)
                line_h = c.h;
            if ((y+line_h)>=h) {
                resize(width(),y+line_h);
                h = height();
            }

            if ((x+c.w)>=w) {
                x = 0;
                if ((y+line_h)>=h) {
                    if (w>h) {
                        resize(width(),height()+line_h);
                        h=height();
                    }
                    else {
                        resize(width()+c.w*2,height());
                        w=width();
                    }
                    iteration = true;
                    break;
                }
                y+=line_h;
            }
            x+=c.w;
        }
    }
    w = width();
    h = height();
    int x = 0;
    int y = 0;
    int line_h = 0;
    foreach (const LayoutChar& c, chars) {
        if (c.h>line_h)
            line_h = c.h;
        if ((x+c.w)>=w){
            y+=line_h;
            x = 0;
        } else {
        }
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
