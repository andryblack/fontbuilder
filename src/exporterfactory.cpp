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

#include "exporterfactory.h"


extern AbstractExporter* GHLExporterFactoryFunc (QObject*);
extern AbstractExporter* ZFIExporterFactoryFunc (QObject* parent);
extern AbstractExporter* DivoExporterFactoryFunc (QObject*);
extern AbstractExporter* NGLExporterFactoryFunc (QObject*);
extern AbstractExporter* LuaTableExporterFactoryFunc (QObject*);
extern AbstractExporter* LuaFunctionExporterFactoryFunc (QObject*);
extern AbstractExporter* SparrowExporterFactoryFunc (QObject*);
extern AbstractExporter* SimpleExporterFactoryFunc (QObject*);
extern AbstractExporter* MyGUIExporterFactoryFunc (QObject*);
extern AbstractExporter* BMFontExporterFactoryFunc (QObject*);
extern AbstractExporter* AGEExporterFactoryFunc (QObject*);
extern AbstractExporter* JSONFontExporterFactoryFunc (QObject*);

ExporterFactory::ExporterFactory(QObject *parent) :
    QObject(parent)
{
    m_factorys["GHL"] = &GHLExporterFactoryFunc;
    m_factorys["ZenGL-zfi"] = &ZFIExporterFactoryFunc;
    m_factorys["Divo compatible - xml"] = &DivoExporterFactoryFunc;
    m_factorys["NGL"] = &NGLExporterFactoryFunc;
    m_factorys["Lua table"] = &LuaTableExporterFactoryFunc;
    m_factorys["Lua function"] = &LuaFunctionExporterFactoryFunc;
    m_factorys["Sparrow"] = &SparrowExporterFactoryFunc;
    m_factorys["Simple"] = &SimpleExporterFactoryFunc;
    m_factorys["MyGUI"] = &MyGUIExporterFactoryFunc;
    m_factorys["BMFont"] = &BMFontExporterFactoryFunc;
    m_factorys["AGE"] = &AGEExporterFactoryFunc;
    m_factorys["JSON"] = &JSONFontExporterFactoryFunc;
}


QStringList ExporterFactory::names() const {
    return m_factorys.keys();
}

AbstractExporter* ExporterFactory::build(const QString &name,QObject* parent) {
    if (m_factorys.contains(name)) {
        return m_factorys[name](parent);
    }
    return 0;
}
