#include "linelayouter.h"
#include "../rendererdata.h"
#include "../layoutdata.h"

LineLayouter::LineLayouter(QObject *parent) :
    AbstractLayouter(parent)
{
}


void LineLayouter::PlaceImages() {
    int h = 0;
    int w = 0;
    foreach (const LayoutChar& c, chars()) {
        w+=c.w;
        if (c.h>h)
            h = c.h;
    }
    resize(w,h);
    int x = 0;
    int y = 0;
    foreach (const LayoutChar& c, chars()) {
        LayoutChar l = c;
        l.x = x;
        l.y = y;
        place(c);
        x+=c.w;
    }
}


AbstractLayouter* LineLayouterFactoryFunc (QObject* parent) {
    return new LineLayouter(parent);
}
