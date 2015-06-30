/**
 * Copyright (c) 2010-2011 Andrey AndryBlack Kunitsyn
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
LuaExporter::LuaExporter(bool write_function,QObject *parent) :
    AbstractExporter(parent), m_write_function(write_function)
{
    setExtension("lua");
}
static QString charCode(uint code) {
    if (code=='\"') return QString().append('\'').append(code).append('\'');
    if (code=='\\') return QString("\"\\\\\"");
    return QString().append('\"').append(code).append('\"');
}

bool LuaExporter::Export(QByteArray& out) {
    QString res;
    if (m_write_function)
        res+="return {\n";
    const QString p(m_write_function ? "\t":"");
    res+=p+QString("file=\"")+texFilename()+QString(m_write_function ? "\",\n" : "\"\n");
    res+=p+QString("height=")+QString().number(metrics().height)+QString(m_write_function?",\n":"\n");
    res+=p+QString("description={\n");
    res+=p+QString("\tfamily=\"")+fontConfig()->family()+QString("\",\n");
    res+=p+QString("\tstyle=\"")+fontConfig()->style()+QString("\",\n");
    res+=p+QString("\tsize=")+QString().number(fontConfig()->size())+QString("\n");
    res+=p+QString(m_write_function?"},\n":"}\n");

    res+=p+QString("metrics={\n");
    res+=p+QString("\tascender=")+QString().number(metrics().ascender)+QString(",\n");
    res+=p+QString("\tdescender=")+QString().number(metrics().descender)+QString(",\n");
    res+=p+QString("\theight=")+QString().number(metrics().height)+QString("\n");
    res+=p+QString(m_write_function?"},\n":"}\n");

    res+=p+QString("texture={\n");
    res+=p+QString("\tfile=\"")+texFilename()+QString("\",\n");
    res+=p+QString("\twidth=")+QString().number(texWidth())+QString(",\n");
    res+=p+QString("\theight=")+QString().number(texHeight())+QString("\n");
    res+=p+QString(m_write_function?"},\n":"}\n");

    res+=p+QString("chars={\n");
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

        res+=p+QString("\t")+charDef+QString(",\n");
    }
    res+=p+QString(m_write_function?"},\n":"}\n");
    QString kernings;
    foreach (const Symbol& c , symbols()) {
        QString charDef="{from=";
        charDef+=charCode(c.id);
        charDef+=QString(",to=");
        typedef QMap<uint,int>::ConstIterator Kerning;
        for ( Kerning k = c.kerning.begin();k!=c.kerning.end();k++) {
            QString def = charDef;
            def+=charCode(k.key());
            def+=QString(",offset=")+QString().number(k.value())+QString("}");
            kernings+=p+QString("\t")+def+QString(",\n");
        }
    }
    if (kernings.length()>2) {
        res+=p+QString("kernings={\n");
        res+=kernings;
        res+=p+QString("}\n");
    }
    if (m_write_function)
        res+=QString("}\n");
    out = res.toUtf8();
    return true;
}


AbstractExporter* LuaTableExporterFactoryFunc (QObject* parent) {
    return new LuaExporter(false,parent);
}
AbstractExporter* LuaFunctionExporterFactoryFunc (QObject* parent) {
    return new LuaExporter(true,parent);
}
