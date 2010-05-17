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
    root.setAttribute("type","GHL");

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
