/**
 * Copyright (C) 2010-2010, by Andrey AndryBlack Kunitsyn
 * (support.andryblack@gmail.com)
 */

#ifndef LAYOUTCHAR_H
#define LAYOUTCHAR_H

#include <Qt>

struct LayoutChar {
    ushort symbol;
    int x;
    int y;
    int w;
    int h;
    LayoutChar(ushort s,int x,int y,int w,int h) :
            symbol(s),x(x),y(y),w(w),h(h)
    {
    }
    LayoutChar(ushort s,int w,int h) :
            symbol(s),x(0),y(0),w(w),h(h)
    {
    }
    LayoutChar() : symbol(0),x(0),y(0),w(0),h(0) {}
};

#endif // LAYOUTCHAR_H
