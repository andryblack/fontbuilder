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

#include "fontrenderer.h"
#include "fontconfig.h"

#include FT_OUTLINE_H

#include <QDir>
#include <QFile>
#include <QDebug>
#include <QRgb>
#include <QColor>

#include <math.h>

FontRenderer::FontRenderer(QObject *parent,const FontConfig* config) :
    QObject(parent), m_config(config)
{
    m_ft_library = 0;
    m_ft_face = 0;
    connect(config,SIGNAL(fileChanged()),this,SLOT(on_fontFileChanged()));
    connect(config,SIGNAL(faceIndexChanged()),this,SLOT(on_fontFaceIndexChanged()));
    connect(config,SIGNAL(sizeChanged()),this,SLOT(on_fontSizeChanged()));
    connect(config,SIGNAL(charactersChanged()),this,SLOT(on_fontCharactersChanged()));
    connect(config,SIGNAL(renderingOptionsChanged()),this,SLOT(on_fontOptionsChanged()));
    int error =  FT_Init_FreeType(&m_ft_library);
    if (error) {
        qDebug() << "FT_Init_FreeType error " << error;
        m_ft_library = 0;
    }
}


FontRenderer::~FontRenderer() {
    if (m_ft_face)
        FT_Done_Face(m_ft_face);
    if (m_ft_library)
        FT_Done_FreeType(m_ft_library);
}

void FontRenderer::rasterize() {
    clear_bitmaps();
    if (!m_ft_face) {
        return;
    }


    qDebug() << " begin rasterize_font ";


    if (m_config->italic()!=0) {
        FT_Matrix matrix;
        const float angle = (-M_PI*m_config->italic()) / 180.0f;
        matrix.xx = (FT_Fixed)( cos( angle ) * 0x10000L );
        matrix.xy = (FT_Fixed)(-sin( angle ) * 0x10000L );
        matrix.yx = (FT_Fixed)( sin( angle ) * 0x10000L );
        matrix.yy = (FT_Fixed)( cos( angle ) * 0x10000L );
        FT_Set_Transform(m_ft_face,&matrix,0);
    } else {
        FT_Set_Transform(m_ft_face,0,0);
    }


    /// fill metrics
    if (FT_IS_SCALABLE(m_ft_face)) {
        m_rendered.metrics.ascender = m_ft_face->size->metrics.ascender / 64;
        m_rendered.metrics.descender = m_ft_face->size->metrics.descender/ 64;
        m_rendered.metrics.height = m_ft_face->size->metrics.height/ 64;
    } else {
        m_rendered.metrics.ascender = m_ft_face->ascender;
        m_rendered.metrics.descender = m_ft_face->descender;
        m_rendered.metrics.height = m_ft_face->height;
    }



    const ushort* chars = m_config->characters().utf16();
    size_t amount = 0;
    while (chars[amount]!=0) amount++;
    int error = 0;
    for (size_t i=0;i<amount;i++) {
        int glyph_index = FT_Get_Char_Index( m_ft_face, chars[i] );
        if (glyph_index==0 && !m_config->renderMissing())
            continue;
        error = FT_Load_Glyph( m_ft_face, glyph_index,
                      FT_LOAD_DEFAULT |
                      /*FT_LOAD_NO_BITMAP |*/
                      (!m_config->antialiased() ?
                         ( FT_LOAD_MONOCHROME | FT_LOAD_TARGET_MONO) :
                         FT_LOAD_TARGET_NORMAL) |
                      (m_config->autohinting() ? FT_LOAD_FORCE_AUTOHINT : FT_LOAD_NO_AUTOHINT) );
        if ( error )
           continue;
        if (m_config->bold()!=0) {
            FT_Pos strength = m_config->size()*m_config->bold();
            if ( m_ft_face->glyph->format == FT_GLYPH_FORMAT_OUTLINE )
                FT_Outline_Embolden( &m_ft_face->glyph->outline, strength );
        }
        if (m_ft_face->glyph->format!=FT_GLYPH_FORMAT_BITMAP) {
            error = FT_Render_Glyph( m_ft_face->glyph,
               m_config->antialiased() ? FT_RENDER_MODE_NORMAL:FT_RENDER_MODE_MONO );
        }
        if ( error )
           continue;
        append_bitmap(chars[i]);
    }
    imagesChanged(m_chars);
    imagesChanged();
}


void FontRenderer::clear_bitmaps() {
       m_rendered.chars.clear();
       m_chars.clear();
}

void FontRenderer::append_bitmap(ushort symbol) {
    const FT_GlyphSlot  slot = m_ft_face->glyph;
    const FT_Bitmap* bm = &(slot->bitmap);
    int w = bm->width;
    int h = bm->rows;
    QImage img(w,h,QImage::Format_ARGB32);
    const uchar* src = bm->buffer;
    //QColor bg = m_config->bgColor();
    //QColor fg = m_config->fgColor();
    if (bm->pixel_mode==FT_PIXEL_MODE_GRAY) {
        for (int row=0;row<h;row++) {
            QRgb* dst = reinterpret_cast<QRgb*>(img.scanLine(row));
            for (int col=0;col<w;col++) {
                 {
                    uchar s = src[col];
                    *dst = qRgba(255,255,255,
                            s);
                }
                dst++;
            }
            src+=bm->pitch;
        }
    }else if (bm->pixel_mode==FT_PIXEL_MODE_MONO) {
        for (int row=0;row<h;row++) {
            QRgb* dst = reinterpret_cast<QRgb*>(img.scanLine(row));

            for (int col=0;col<w/8;col++) {
                uchar s = src[col];
                *dst++ = qRgba(255,255,255,(s&(1<<7))?255:0);
                *dst++ = qRgba(255,255,255,(s&(1<<6))?255:0);
                *dst++ = qRgba(255,255,255,(s&(1<<5))?255:0);
                *dst++ = qRgba(255,255,255,(s&(1<<4))?255:0);
                *dst++ = qRgba(255,255,255,(s&(1<<3))?255:0);
                *dst++ = qRgba(255,255,255,(s&(1<<2))?255:0);
                *dst++ = qRgba(255,255,255,(s&(1<<1))?255:0);
                *dst++ = qRgba(255,255,255,(s&(1<<0))?255:0);
            }
            {
                uchar s = src[w/8];
                int num = 7;
                switch (w%8) {
                case 7:  *dst++ = qRgba(255,255,255,(s&(1<<(num--)))?255:0);
                case 6:  *dst++ = qRgba(255,255,255,(s&(1<<(num--)))?255:0);
                case 5:  *dst++ = qRgba(255,255,255,(s&(1<<(num--)))?255:0);
                case 4:  *dst++ = qRgba(255,255,255,(s&(1<<(num--)))?255:0);
                case 3:  *dst++ = qRgba(255,255,255,(s&(1<<(num--)))?255:0);
                case 2:  *dst++ = qRgba(255,255,255,(s&(1<<(num--)))?255:0);
                case 1:  *dst++ = qRgba(255,255,255,(s&(1<<(num--)))?255:0);
                case 0:
                    break;
                }
            }

            src+=bm->pitch;
        }
    }

    m_rendered.chars[symbol]=RenderedChar(symbol,slot->bitmap_left,slot->bitmap_top,slot->advance.x/64,img);
    m_chars.push_back(LayoutChar(symbol,slot->bitmap_left,-slot->bitmap_top,w,h));

}

void FontRenderer::on_fontFileChanged() {
    QFile file(QDir(m_config->path()).filePath(m_config->filename()));
    if (file.open(QFile::ReadOnly)) {
        m_data = file.readAll();
        on_fontFaceIndexChanged();
    }
}

void FontRenderer::on_fontFaceIndexChanged() {
    if (m_ft_face) {
        FT_Done_Face(m_ft_face);
        m_ft_face = 0;
    }
    if (!m_ft_library) return;
    int error =  FT_New_Memory_Face(
            m_ft_library,
            reinterpret_cast<const FT_Byte*>(m_data.constData()),m_data.size(),
            m_config->faceIndex(),&m_ft_face);
    if (error) {
        qDebug() << "FT_New_Memory_Face error " << error;
    } else {
        error = FT_Select_Charmap(
                    m_ft_face,               /* target face object */
                    FT_ENCODING_UNICODE );
        if (error) {
            qDebug() << "FT_Select_CharMap error " << error;
        }
    }
}


void FontRenderer::on_fontSizeChanged() {
    if (!m_ft_face) return;
    bool fixedsize = (FT_FACE_FLAG_SCALABLE & m_ft_face->face_flags ) == 0;
    int size = m_config->size();
    if (fixedsize) {
        qDebug() << "fixed size not impemented";
    } else {
        int size_x = static_cast<int>(m_config->width()*size*64.0f/100.0f);
        int size_y = static_cast<int>(m_config->height()*size*64.0f/100.0f);
        int error = FT_Set_Char_Size(m_ft_face,
                                     FT_F26Dot6(size_x),
                                     FT_F26Dot6(size_y),96,96);
        //int error = FT_Set_Pixel_Sizes(m_ft_face,size_x/64,size_y/64);
        if (error) {
            qDebug() << "FT_Set_Char_Size error " << error;
        }
    }
    rasterize();
}

void FontRenderer::on_fontCharactersChanged() {
    rasterize();
}

void FontRenderer::on_fontOptionsChanged() {

    rasterize();
}



void FontRenderer::placeImage(QPainter& p,ushort symbol,int x,int y) {
    p.drawImage(x,y,m_rendered.chars[symbol].img);
}
