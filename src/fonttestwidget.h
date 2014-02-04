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

#ifndef FONTTESTWIDGET_H
#define FONTTESTWIDGET_H

#include <QWidget>

class LayoutData;
struct RendererData;
struct LayoutChar;
class FontConfig;

class FontTestWidget : public QWidget
{
Q_OBJECT
public:
    explicit FontTestWidget(QWidget *parent = 0);

    void setLayoutData(const LayoutData* data) { m_layout_data = data;}
    void setRendererData(const RendererData* data) { m_renderer_data = data;}
    void setFontConfig(const FontConfig* config) { m_font_config = config;}

    void setText(const QString& text);

    bool useKerning() const { return m_use_kerning;}
    void setUseKerning(bool use) { m_use_kerning=use;}

    enum Align {
        ALIGN_LEFT,
        ALIGN_CENTER,
        ALIGN_RIGHT,
    };

    void setAlign(Align a) { m_align = a;}

protected:
    virtual void paintEvent ( QPaintEvent * event );
    void calcBBox();
    int lineWidth(const uint* text) const;
signals:

public slots:
    void refresh();
    void setBGColor(QColor c);
private:
    QString m_text;
    const LayoutData*   m_layout_data;
    const LayoutChar*   layoutChar(uint c) const;
    const RendererData* m_renderer_data;
    const FontConfig*   m_font_config;
    int m_left;
    int m_width;
    int m_top;
    bool    m_use_kerning;
    Align   m_align;
    QColor  m_bg_color;
};

#endif // FONTTESTWIDGET_H
