/**
 * Copyright (C) 2010-2010, by Andrey AndryBlack Kunitsyn
 * (support.andryblack@gmail.com)
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


    if (m_config->italic()) {
        FT_Matrix matrix;
        const float angle = -10 * M_PI / 180.0f;
        matrix.xx = (FT_Fixed)( cos( angle ) * 0x10000L );
        matrix.xy = (FT_Fixed)(-sin( angle ) * 0x10000L );
        matrix.yx = (FT_Fixed)( sin( angle ) * 0x10000L );
        matrix.yy = (FT_Fixed)( cos( angle ) * 0x10000L );
        FT_Set_Transform(m_ft_face,&matrix,0);
    } else {
        FT_Set_Transform(m_ft_face,0,0);
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
                      FT_LOAD_NO_BITMAP |
                      (m_config->antialiased() ? FT_LOAD_TARGET_MONO : FT_LOAD_TARGET_NORMAL) |
                      (m_config->autohinting() ? FT_LOAD_FORCE_AUTOHINT : 0) );
        if ( error )
           continue;
        if (m_config->bold()) {
            FT_Pos strength = m_config->size()*4;
            if ( m_ft_face->glyph->format == FT_GLYPH_FORMAT_OUTLINE )
                FT_Outline_Embolden( &m_ft_face->glyph->outline, strength );
        }
        error = FT_Render_Glyph( m_ft_face->glyph,
               m_config->antialiased() ? FT_RENDER_MODE_NORMAL:FT_RENDER_MODE_MONO );
        if ( error )
           continue;
        append_bitmap(chars[i]);
    }
    imagesChanged(m_chars);
    imagesChanged();
}


void FontRenderer::clear_bitmaps() {
       m_images.clear();
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
            if (int d=w%8) {
                uchar s = src[w/8];
                switch (d) {
                case 7:  *dst++ = qRgba(255,255,255,(s&(1<<7))?255:0);
                case 6:  *dst++ = qRgba(255,255,255,(s&(1<<6))?255:0);
                case 5:  *dst++ = qRgba(255,255,255,(s&(1<<5))?255:0);
                case 4:  *dst++ = qRgba(255,255,255,(s&(1<<4))?255:0);
                case 3:  *dst++ = qRgba(255,255,255,(s&(1<<3))?255:0);
                case 2:  *dst++ = qRgba(255,255,255,(s&(1<<2))?255:0);
                case 1:  *dst++ = qRgba(255,255,255,(s&(1<<1))?255:0);
                }
            }

            src+=bm->pitch;
        }
    }

    m_images[symbol]=RenderedChar(symbol,slot->bitmap_left,slot->bitmap_top,slot->advance.x/64,img);
    m_chars.push_back(LayoutChar(symbol,w,h));

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
        int error = FT_Set_Char_Size(m_ft_face,
                                     0,
                                     size*64,0,0);
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
    p.drawImage(x,y,m_images[symbol].img);
}
