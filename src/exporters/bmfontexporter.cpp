#include "bmfontexporter.h"
#include "../fontconfig.h"

BMFontExporter::BMFontExporter(QObject *parent) :
    AbstractExporter(parent)
{
    setExtension("fnt");
}

bool BMFontExporter::Export(QByteArray &out)
{
    // Format description:
    // http://www.angelcode.com/products/bmfont/doc/file_format.html

    const FontConfig* cfg = fontConfig();

    out.append( QString("info")
        + QString(" face=\"%1\"").arg(cfg->family())
        + QString(" size=%1").arg(cfg->size())
        + QString(" bold=%1").arg(cfg->bold() ? 1 : 0)
        + QString(" italic=%1").arg(cfg->italic() ? 1 : 0)
        + QString(" smooth=%1").arg(cfg->antialiased() ? 1 : 0)
        + QString(" spacing=%1,%2").arg(cfg->charSpacing()).arg(cfg->lineSpacing())
        .toUtf8()).append('\n');

    out.append( QString("common")
        + QString(" lineHeight=%1").arg(metrics().height)
        + QString(" base=%1").arg(metrics().ascender)
        + QString(" scaleW=%1").arg(texWidth())
        + QString(" scaleH=%1").arg(texHeight())
        + QString(" pages=1")
        .toUtf8()).append('\n');

    out.append( QString("page")
        + QString(" id=%1").arg(0)
        + QString(" file=\"%1\"").arg(texFilename())
        .toUtf8()).append('\n');

    foreach(const Symbol& c , symbols()) {
        out.append( QString("char")
            + QString(" id=%1").arg(c.id)
            + QString(" x=%1").arg(c.placeX)
            + QString(" y=%1").arg(c.placeY)
            + QString(" width=%1").arg(c.placeW)
            + QString(" height=%1").arg(c.placeH)
            + QString(" xoffset=%1").arg(c.offsetX)
            + QString(" yoffset=%1").arg(c.offsetY)
            + QString(" xadvance=%1").arg(c.advance)
            + QString(" page=%1").arg(0)
            .toUtf8()).append('\n');
    }

    typedef QMap<uint,int>::ConstIterator Kerning;
    foreach(const Symbol& c , symbols()) {
        for (Kerning k = c.kerning.begin();k!=c.kerning.end();k++) {
            out.append( QString("kerning")
                + QString(" first=%1").arg(c.id)
                + QString(" second=%1").arg(k.key())
                + QString(" amount=%1").arg(k.value())
                .toUtf8()).append('\n');
        }
    }

    return true;
}

AbstractExporter* BMFontExporterFactoryFunc (QObject* parent) {
    return new BMFontExporter(parent);
}
