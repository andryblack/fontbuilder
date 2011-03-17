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

#ifndef FONTDRAWWIDGET_H
#define FONTDRAWWIDGET_H

#include <QWidget>
#include <QPixmap>

#include "layoutdata.h"
#include "rendererdata.h"
#include "layoutconfig.h"

class FontDrawWidget : public QWidget
{
    Q_OBJECT
public:
    explicit FontDrawWidget(QWidget *parent = 0);

    void setImage(const QImage& image);
    void setScale(float s);
    void setDrawGrid(bool draw);

    void setLayoutData(const LayoutData* layoutData) { m_layout_data = layoutData;}
    void setRendererData(const RendererData* rendererData) { m_renderer_data = rendererData;}
    void setLayoutConfig(const LayoutConfig* layoutConfig) { m_layout_config = layoutConfig;}

    void paintEvent(QPaintEvent *);
private:
    float   m_scale;
    bool    m_draw_grid;
    QImage  m_image;
    const LayoutData*   m_layout_data;
    const RendererData* m_renderer_data;
    const LayoutConfig* m_layout_config;
signals:

public slots:

};

#endif // FONTDRAWWIDGET_H
