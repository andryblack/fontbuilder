/**
 * Copyright (C) 2010-2010, by Andrey AndryBlack Kunitsyn
 * (support.andryblack@gmail.com)
 */

#include "ghlexporter.h"
#include "../fontconfig.h"
#include "../layoutdata.h"
#include <QDomDocument>

GHLExporter::GHLExporter(QObject *parent) :
    AbstractExporter(parent)
{
    setExtension("xml");
}

bool GHLExporter::Export(QByteArray& out) {
    QDomDocument doc("font");
    QDomElement root = doc.createElement("font");
    doc.appendChild(root);

    QDomElement descr = doc.createElement("description");
    descr.setAttribute("family",font_config()->family());
    descr.setAttribute("style",font_config()->style());
    descr.setAttribute("size",font_config()->size());
    root.appendChild(descr);

    QDomElement chars = doc.createElement("chars");
    foreach (const Symbol& c , symbols()) {
        QDomElement ce = doc.createElement("char");
        ce.setAttribute("id",QString().append(c.id));
        char buf[64];
        ::snprintf(buf,63,"%d %d %d %d",c.place_x,c.place_y,c.place_w,c.place_h);
        ce.setAttribute("rect",buf);
        ::snprintf(buf,63,"%d %d",c.offset_x,c.offset_y);
        ce.setAttribute("offset",buf);
        ce.setAttribute("advance",c.advance);
        chars.appendChild(ce);
    }
    root.appendChild(chars);
    out = doc.toByteArray(1);
    return true;
}


AbstractExporter* GHLExporterFactoryFunc (QObject* parent) {
    return new GHLExporter(parent);
}
