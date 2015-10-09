/**
 * Copyright (c) 2010-2015 Andrey AndryBlack Kunitsyn
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

#include "myguiexporter.h"
#include "../fontconfig.h"
#include "../layoutdata.h"
#include "../layoutconfig.h"
#include <QDomDocument>
#include FT_TRUETYPE_TABLES_H

MyGUIExporter::MyGUIExporter(QObject *parent) : AbstractExporter(parent)
{
    setExtension("xml");
}

static void appendProperty(QDomDocument& doc,QDomElement& el,QString name,QString value) {
    QDomElement p = doc.createElement("Property");
    p.setAttribute("key",name);
    p.setAttribute("value",value);
    el.appendChild(p);
}

bool MyGUIExporter::Export(QByteArray& out) {
    QDomDocument doc;
    doc.appendChild(doc.createProcessingInstruction("xml","version=\"1.0\" encoding=\"utf-8\"" ));

    QDomElement root = doc.createElement("MyGUI");

    float iscale = 1.0f / scale();
    float scale = iscale;

    int ascender = metrics().ascender * scale;
    int descender = metrics().descender * scale;

    TT_OS2* os2 = (TT_OS2*)FT_Get_Sfnt_Table(face(), ft_sfnt_os2);

    if (os2)
    {
        int v =  os2->usWinAscent * face()->size->metrics.y_ppem * scale / face()->units_per_EM;
        if (ascender < v)
           ascender = v;
        v = os2->usWinDescent * face()->size->metrics.y_ppem * scale / face()->units_per_EM;
        if (descender < v)
           descender = v;
        v = os2->sTypoAscender * face()->size->metrics.y_ppem * scale / face()->units_per_EM;
        if (ascender < v)
           ascender = v;
        v = -os2->sTypoDescender * face()->size->metrics.y_ppem * scale / face()->units_per_EM;
        if (descender < v)
            descender = v;
    }

    doc.appendChild(root);
    root.setAttribute("type","Resource");
    root.setAttribute("version","1.0");

    QDomElement descr = doc.createElement("Resource");
    descr.setAttribute("type","ResourceManualFont");
    descr.setAttribute("name",fontConfig()->family()+"-"
                       +fontConfig()->style()+"-"+QString("%1").arg(fontConfig()->size()));
    appendProperty(doc,descr,"Source",texFilename());
    appendProperty(doc,descr,"SourceSize",QString("%1 %2").arg(texWidth()* scale).arg(texHeight()* scale));
    appendProperty(doc,descr,"DefaultHeight",QString("%1").arg(ascender+descender));

    QDomElement chars = doc.createElement("Codes");
    foreach (const Symbol& c , symbols()) {
        QDomElement ce = doc.createElement("Code");
        ce.setAttribute("index",QString("%1").arg(c.id));
        char buf[64];
        ::snprintf(buf,63,"%d %d %d %d",c.placeX,c.placeY,c.placeW,c.placeH);
        ce.setAttribute("coord",buf);
        ::snprintf(buf,63,"%f %f",c.offsetX * scale,ascender-c.offsetY * scale);
        ce.setAttribute("bearing",buf);
        ce.setAttribute("advance",c.advance* scale-c.offsetX* scale);
        if (scale!=1.0f) {
            ::snprintf(buf,63,"%f %f",c.placeW * scale,c.placeH * scale);
            ce.setAttribute("size",buf);
        }
//        typedef QMap<uint,int>::ConstIterator Kerning;
//        for ( Kerning k = c.kerning.begin();k!=c.kerning.end();k++) {
//            QDomElement ke = doc.createElement("kerning");
//            ke.setAttribute("id",QString().append(k.key()));
//            ke.setAttribute("advance",k.value());
//            ce.appendChild(ke);
//        }

        chars.appendChild(ce);
    }
    descr.appendChild(chars);
    root.appendChild(descr);
    out = doc.toByteArray(1);
    return true;
}


AbstractExporter* MyGUIExporterFactoryFunc (QObject* parent) {
    return new MyGUIExporter(parent);
}
