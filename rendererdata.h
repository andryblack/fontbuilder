#ifndef RENDERERDATA_H
#define RENDERERDATA_H

#include <QMap>
#include <QImage>

struct RenderedChar {
    ushort symbol;
    int offset_x;
    int offset_y;
    int advance;
    QImage img;
    RenderedChar() : symbol(0) {}
    RenderedChar(ushort symbol,int x,int y,int a,const QImage& img) :
            symbol(symbol),offset_x(x),offset_y(y),advance(a),img(img) {}
};

typedef QMap<ushort,RenderedChar> RendererData;


#endif // RENDERERDATA_H
