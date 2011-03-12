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

#include "luaexporter.h"
#include "../fontconfig.h"
#include "../layoutdata.h"

#include <QString>
LuaExporter::LuaExporter(QObject *parent) :
    AbstractExporter(parent)
{
    setExtension("lua");
}
static QString charCode(uint code) {
    if (code=='\"') return QString().append('\'').append(code).append('\'');
    if (code=='\\') return QString("\"\\\\\"");
    return QString().append('\"').append(code).append('\"');
}

bool LuaExporter::Export(QByteArray& out) {
    QString res = "return {\n";
    res+=QString("\tfile=\"")+texFilename()+QString("\",\n");
    res+=QString("\theight=")+QString().number(metrics().height)+QString(",\n");
    res+=QString("\tdescription={\n");
    res+=QString("\t\tfamily=\"")+fontConfig()->family()+QString("\",\n");
    res+=QString("\t\tstyle=\"")+fontConfig()->style()+QString("\",\n");
    res+=QString("\t\tsize=")+QString().number(fontConfig()->size())+QString("\n");
    res+=QString("\t},\n");

    res+=QString("\tmetrics={\n");
    res+=QString("\t\tascender=")+QString().number(metrics().ascender)+QString(",\n");
    res+=QString("\t\tdescender=")+QString().number(metrics().descender)+QString(",\n");
    res+=QString("\t\theight=")+QString().number(metrics().height)+QString("\n");
    res+=QString("\t},\n");

    res+=QString("\ttexture={\n");
    res+=QString("\t\tfile=\"")+texFilename()+QString("\",\n");
    res+=QString("\t\twidth=")+QString().number(texWidth())+QString(",\n");
    res+=QString("\t\theight=")+QString().number(texHeight())+QString("\n");
    res+=QString("\t},\n");

    res+=QString("\tchars={\n");
    foreach (const Symbol& c , symbols()) {
        QString charDef="{char=";
        charDef+=charCode(c.id);
        charDef+=QString(",");
        charDef+=QString("width=")+QString().number(c.advance)+QString(",");
        charDef+=QString("x=")+QString().number(c.placeX)+QString(",");
        charDef+=QString("y=")+QString().number(c.placeY)+QString(",");
        charDef+=QString("w=")+QString().number(c.placeW)+QString(",");
        charDef+=QString("h=")+QString().number(c.placeH)+QString(",");

        charDef+=QString("ox=")+QString().number(c.offsetX)+QString(",");
        charDef+=QString("oy=")+QString().number(c.offsetY)+QString("}");

        res+=QString("\t\t")+charDef+QString(",\n");
    }
    res+=QString("\t},\n");
    QString kernings;
    foreach (const Symbol& c , symbols()) {
        QString charDef="{from=";
        charDef+=charCode(c.id);
        charDef+=QString(",to=");
        typedef QMap<ushort,int>::ConstIterator Kerning;
        for ( Kerning k = c.kerning.begin();k!=c.kerning.end();k++) {
            QString def = charDef;
            def+=charCode(k.key());
            def+=QString(",offset=")+QString().number(k.value())+QString("}");
            kernings+=QString("\t\t")+def+QString(",\n");
        }
    }
    if (kernings.length()>2) {
        res+=QString("\tkernings={\n");
        res+=kernings;
        res+=QString("\t}\n");
    }
    res+=QString("}\n");
    out = res.toUtf8();
    return true;
}


AbstractExporter* LuaExporterFactoryFunc (QObject* parent) {
    return new LuaExporter(parent);
}
