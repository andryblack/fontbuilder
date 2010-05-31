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


#ifndef ABSTRACTEXPORTER_H
#define ABSTRACTEXPORTER_H

#include <QObject>
#include <QByteArray>
#include <QDir>
#include <QVector>
#include "rendererdata.h"

class FontConfig;
class LayoutConfig;
class LayoutData;

class AbstractExporter : public QObject
{
Q_OBJECT
public:
    explicit AbstractExporter(QObject *parent );

    const QString& getErrorString() const { return m_error_string;}
    const QString& getExtension() const { return m_extension;}

    bool Write(QByteArray& out);

    void setFontConfig(const FontConfig* config,const LayoutConfig* layout) { m_font_config = config;m_layout_config=layout;}
    void setData(const LayoutData* data,const RendererData& rendered);
private:
    QString m_error_string;
    QString m_extension;
    QString m_filename;
    int m_tex_width;
    int m_tex_height;
    const FontConfig* m_font_config;
    const LayoutConfig* m_layout_config;
    RenderedMetrics m_metrics;
protected:
    struct Symbol {
        unsigned short id;
        int place_x;
        int place_y;
        int place_w;
        int place_h;
        int offset_x;
        int offset_y;
        int advance;
    };

    const FontConfig* fontConfig() const { return m_font_config;}
    const LayoutConfig* layoutConfig() const { return m_layout_config;}
    const QVector<Symbol>& symbols() const { return m_symbols;}
    void setExtension(const QString& extension) { m_extension = extension;}
    void setErrorMessage(const QString& str) { m_error_string=str; }
    int texWidth() const { return m_tex_width;}
    int texHeight() const { return m_tex_height;}
    const RenderedMetrics& metrics() const { return m_metrics;}
    virtual bool Export(QByteArray& out) = 0;
private:
     QVector<Symbol> m_symbols;
};


#endif // ABSTRACTEXPORTER_H
