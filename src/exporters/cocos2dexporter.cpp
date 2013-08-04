#include "cocos2dexporter.h"
#include "../fontconfig.h"

Cocos2dExporter::Cocos2dExporter(QObject *parent) :
    AbstractExporter(parent)
{
    setExtension("fnt");
}

bool Cocos2dExporter::Export(QByteArray& out) {
    QString res = "info ";
    res += QString("face=\"") + fontConfig()->family() +  QString("\" ");
    res += QString("size=") + QString().number(metrics().height) + QString(" bold=") + QString().number(fontConfig()->size()) + QString(" italic=0 charset="" unicode=0 stretchH=100 smooth=1 aa=1 padding=0,0,0,0 spacing=2,2\n");
    res += QString("common lineHeight=") + QString().number(metrics().height) + QString(" base=29 scaleW=") + QString().number(texWidth()) + QString(" scaleH=") + QString().number(texWidth()) + QString(" pages=1 packed=0\n");
    res += QString("page id=0 file=\"") + texFilename() + QString("\"\n");
    res += QString("chars count=") + QString().number(symbols().size()) + QString("\n");

    foreach(const Symbol& c , symbols())
    {
        res += QString("char id=") + QString().number(c.id) + QString(" x=") + QString().number(c.placeX) + QString(" y=") + QString().number(c.placeY);
        res += QString(" width=") + QString().number(c.placeW) + QString(" height=") + QString().number(c.placeH);
        res += QString(" xoffset=") + QString().number(c.offsetX) + QString(" yoffset=") + QString().number(c.offsetY);
        res += QString(" xadvance=") + QString().number(c.advance) + QString(" page=0 chnl=0 ");

        if(c.id==32)
        {
            res += QString("letter=\"space\"");
        }
        else
        {
            res += QString("letter=\"" + QString().append(c.id) + "\"");
        }

        res += QString("\n");
    }

    out = res.toUtf8();
    return true;
}

AbstractExporter* Cocos2dExporterFactoryFunc (QObject* parent) {
    return new Cocos2dExporter(parent);
}
