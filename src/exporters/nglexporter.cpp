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

#include "nglexporter.h"
#include "../fontconfig.h"
#include "../layoutdata.h"
#include <QDomDocument>

NGLExporter::NGLExporter(QObject *parent) :
    AbstractExporter(parent)
{
    setExtension("xml");
}

bool NGLExporter::Export(QByteArray& out) {
    QDomDocument doc;
    QDomElement root = doc.createElement("font");

    doc.appendChild(doc.createProcessingInstruction("xml","version=\"1.0\" encoding=\"utf-8\"" ));

    doc.appendChild(root);
    root.setAttribute("type","NGL");

    QDomElement descr = doc.createElement("description");
    descr.setAttribute("family",fontConfig()->family());
    descr.setAttribute("style",fontConfig()->style());
    descr.setAttribute("size",fontConfig()->size());
    root.appendChild(descr);

    QDomElement fmetrics = doc.createElement("metrics");
    fmetrics.setAttribute("ascender",metrics().ascender);
    fmetrics.setAttribute("descender",metrics().descender);
    fmetrics.setAttribute("height",metrics().height);
    root.appendChild(fmetrics);

    QDomElement tex = doc.createElement("texture");
    tex.setAttribute("width",texWidth());
    tex.setAttribute("height",texHeight());
    tex.setAttribute("file",texFilename());
    root.appendChild(tex);

    QDomElement chars = doc.createElement("chars");
    foreach (const Symbol& c , symbols()) {
        QDomElement ce = doc.createElement("char");
        ce.setAttribute("id",QString().append(c.id));
        ce.setAttribute("rect_x",c.placeX);
        ce.setAttribute("rect_y",c.placeY);
        ce.setAttribute("rect_w",c.placeW);
        ce.setAttribute("rect_h",c.placeH);
        ce.setAttribute("offset_x",c.offsetX);
        ce.setAttribute("offset_y",c.offsetY);
        ce.setAttribute("advance",c.advance);
        typedef QMap<uint,int>::ConstIterator Kerning;
        for ( Kerning k = c.kerning.begin();k!=c.kerning.end();k++) {
            QDomElement ke = doc.createElement("kerning");
            ke.setAttribute("id",QString().append(k.key()));
            ke.setAttribute("advance",k.value());
            ce.appendChild(ke);
        }

        chars.appendChild(ce);
    }
    root.appendChild(chars);
    out = doc.toByteArray(1);
    return true;
}


AbstractExporter* NGLExporterFactoryFunc (QObject* parent) {
    return new NGLExporter(parent);
}
