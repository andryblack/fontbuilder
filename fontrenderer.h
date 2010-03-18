/**
 * Copyright (C) 2010-2010, by Andrey AndryBlack Kunitsyn
 * (support.andryblack@gmail.com)
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
