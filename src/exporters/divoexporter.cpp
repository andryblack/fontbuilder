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

#include "divoexporter.h"
#include "../fontconfig.h"
#include <QtXml>

DivoExporter::DivoExporter(QObject *parent) :
    AbstractExporter(parent)
{
    setExtension("xml");
}


bool DivoExporter::Export(QByteArray& out) {
    QDomDocument doc;
    doc.appendChild(doc.createProcessingInstruction("xml","version=\"1.0\" encoding=\"utf-8\"" ));
    QDomElement root = doc.createElement("Font");
    doc.appendChild(root);

    root.setAttribute("family",fontConfig()->family());
    root.setAttribute("style",fontConfig()->style());
    root.setAttribute("size",fontConfig()->size());
    root.setAttribute("height",metrics().height);

    int offset = metrics().ascender;

    foreach (const Symbol& c , symbols()) {
        QDomElement ce = doc.createElement("Char");
        ce.setAttribute("code",QString().append(c.id));
        char buf[64];
        ::snprintf(buf,63,"%d %d %d %d",c.placeX,c.placeY,c.placeW,c.placeH);
        ce.setAttribute("rect",buf);
        ::snprintf(buf,63,"%d %d",c.offsetX,offset-c.offsetY);
        ce.setAttribute("offset",buf);
        ce.setAttribute("width",c.advance);
        typedef QMap<uint,int>::ConstIterator Kerning;
        for ( Kerning k = c.kerning.begin();k!=c.kerning.end();k++) {
            QDomElement ke = doc.createElement("Kerning");
            ke.setAttribute("id",QString().append(k.key()));
            ke.setAttribute("advance",k.value());
            ce.appendChild(ke);
        }
        root.appendChild(ce);
    }
    out = doc.toByteArray(1);
    return true;
}


AbstractExporter* DivoExporterFactoryFunc (QObject* parent) {
    return new DivoExporter(parent);
}
