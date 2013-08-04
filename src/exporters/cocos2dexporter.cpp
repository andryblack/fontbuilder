#include "cocos2dexporter.h"
#include "../fontconfig.h"
#include <QtXml>

Cocos2dExporter::Cocos2dExporter(QObject *parent) :
    AbstractExporter(parent)
{
    setExtension("fnt");
}

bool Cocos2dExporter::Export(QByteArray& out) {
    QDomDocument doc;
    QDomElement root = doc.createElement("font");
    doc.appendChild(root);
    QDomElement info = doc.createElement("info");
    root.appendChild(info);
    info.setAttribute("face", fontConfig()->family());
    info.setAttribute("size", fontConfig()->size());
    QDomElement common = doc.createElement("common");
    root.appendChild(common);
    int height = metrics().height;
    common.setAttribute("lineHeight", height);
    QDomElement pages = doc.createElement("pages");
    root.appendChild(pages);
    QDomElement page = doc.createElement("page");
    pages.appendChild(page);
    page.setAttribute("id", "0");
    page.setAttribute("file", texFilename());
    QDomElement chars = doc.createElement("chars");
    root.appendChild(chars);
    chars.setAttribute("count", symbols().size());
    QDomElement kernings = doc.createElement("kernings");
    int kernNumber = 0;
    foreach(const Symbol& c , symbols()) {
        QDomElement ch = doc.createElement("char");
        ch.setAttribute("id", QString::number(c.id));
        ch.setAttribute("x", QString::number(c.placeX));
        ch.setAttribute("y", QString::number(c.placeY));
        ch.setAttribute("width", QString::number(c.placeW));
        ch.setAttribute("height", QString::number(c.placeH));
        ch.setAttribute("xoffset", QString::number(c.offsetX));
        ch.setAttribute("yoffset", QString::number(height - c.offsetY));
        ch.setAttribute("xadvance", QString::number(c.advance));
        ch.setAttribute("page", "0");
        ch.setAttribute("chnl", "0");
        ch.setAttribute("letter", c.id==32 ? "space" : QString().append(c.id));
        chars.appendChild(ch);
        typedef QMap<ushort,int>::ConstIterator Kerning;
        for ( Kerning k = c.kerning.begin();k!=c.kerning.end();k++) {
            QDomElement ker = doc.createElement("kerning");
            ker.setAttribute("first", QString::number(c.id));
            ker.setAttribute("second", QString::number(k.key()));
            ker.setAttribute("amount", k.value());
            kernings.appendChild(ker);
            kernNumber ++;
        }
    }
    kernings.setAttribute("count", QString::number(kernNumber));
    root.appendChild(kernings);

    out = doc.toByteArray(1);
    return true;
}

AbstractExporter* Cocos2dExporterFactoryFunc (QObject* parent) {
    return new Cocos2dExporter(parent);
}
