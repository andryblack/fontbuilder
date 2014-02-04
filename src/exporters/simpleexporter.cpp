#include "simpleexporter.h"
#include "../fontconfig.h"

SimpleExporter::SimpleExporter(QObject *parent) :
    AbstractExporter(parent)
{
    setExtension("sfl");
}

bool SimpleExporter::Export(QByteArray &out)
{
    const FontConfig* cfg = fontConfig();
    int height = metrics().height;

    // Font family
    out.append(cfg->family().toUtf8()).append(' ');
    // Font size
    out.append(QString::number(cfg->size()).toUtf8()).append(' ');
    // Line height
    out.append(QString::number(height).toUtf8()).append(' ');
    // Texture filename
    out.append(texFilename().toUtf8()).append('\n');
    // Number of symbols
    out.append(QString::number(symbols().size()).toUtf8()).append('\n');
    foreach(const Symbol& c , symbols()) {
        // id, x, y, width, height, xoffset, yoffset, xadvance
        out.append(QString::number(c.id).toUtf8()).append(' ');
        out.append(QString::number(c.placeX).toUtf8()).append(' ');
        out.append(QString::number(c.placeY).toUtf8()).append(' ');
        out.append(QString::number(c.placeW).toUtf8()).append(' ');
        out.append(QString::number(c.placeH).toUtf8()).append(' ');
        out.append(QString::number(c.offsetX).toUtf8()).append(' ');
        out.append(QString::number(height - c.offsetY).toUtf8()).append(' ');
        out.append(QString::number(c.advance).toUtf8()).append(' ');
        out.append('\n');
    }
    QByteArray kernings;
    int kerningsCount = 0;
    typedef QMap<uint,int>::ConstIterator Kerning;
    foreach(const Symbol& c , symbols()) {
        for ( Kerning k = c.kerning.begin();k!=c.kerning.end();k++) {
            // first, second, amount
            kernings.append(QString::number(c.id).toUtf8()).append(' ');
            kernings.append(QString::number(k.key()).toUtf8()).append(' ');
            kernings.append(QString::number(k.value()).toUtf8()).append(' ');
            kernings.append('\n');
            ++kerningsCount;
        }
    }
    // Number of kernings
    out.append(QString::number(kerningsCount).toUtf8()).append('\n');
    out.append(kernings);

    return true;
}

AbstractExporter* SimpleExporterFactoryFunc (QObject* parent) {
    return new SimpleExporter(parent);
}
