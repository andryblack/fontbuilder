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

#ifndef FONTRENDERER_H
#define FONTRENDERER_H

#include <QObject>
#include <QByteArray>
#include <QPainter>

#include <ft2build.h>
#include FT_FREETYPE_H

#include "rendererdata.h"
#include "layoutchar.h"

class FontConfig;

class FontRenderer : public QObject
{
Q_OBJECT
public:
    explicit FontRenderer(QObject *parent , const FontConfig* config);
    ~FontRenderer();

    const QVector<LayoutChar>& rendered() const { return m_chars;}
    void placeImage(QPainter& p,ushort sybol,int x,int y);
    const RendererData& data() const { return m_images;}
private:
    const FontConfig* m_config;
    FT_Library m_ft_library;
    FT_Face m_ft_face;
    QByteArray  m_data;
    void rasterize();
    RendererData m_images;
    QVector<LayoutChar> m_chars;
    void clear_bitmaps();
    void append_bitmap(ushort symbol);
signals:
    void imagesChanged();
    void imagesChanged(const QVector<LayoutChar>&);
public slots:
private slots:
    void on_fontFileChanged();
    void on_fontFaceIndexChanged();
    void on_fontSizeChanged();
    void on_fontCharactersChanged();
    void on_fontOptionsChanged();
};

#endif // FONTRENDERER_H
