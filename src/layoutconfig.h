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

#ifndef LAYOUTCONFIG_H
#define LAYOUTCONFIG_H

#include <QObject>

class LayoutConfig : public QObject
{
Q_OBJECT
public:
    explicit LayoutConfig(QObject *parent = 0);

    bool onePixelOffset() const { return m_one_pixel_offset;}
    void setOnePixelOffset(bool b);
    Q_PROPERTY( bool onePixelOffset READ onePixelOffset WRITE setOnePixelOffset );

    bool potImage() const { return m_pot_image;}
    void setPotImage(bool b);
    Q_PROPERTY( bool potImage READ potImage WRITE setPotImage );

    int sizeIncrement() const { return m_size_increment;}
    void setSizeIncrement(int v);
    Q_PROPERTY( int sizeIncrement READ sizeIncrement WRITE setSizeIncrement);

    void setOffsetLeft(int v);
    void setOffsetTop(int v);
    void setOffsetRight(int v);
    void setOffsetBottom(int v);

    int offsetLeft() const { return m_offset_left;}
    int offsetTop() const { return m_offset_top;}
    int offsetRight() const { return m_offset_right;}
    int offsetBottom() const { return m_offset_bottom;}

    Q_PROPERTY( int offsetLeft READ offsetLeft WRITE setOffsetLeft );
    Q_PROPERTY( int offsetTop READ offsetTop WRITE setOffsetTop );
    Q_PROPERTY( int offsetRight READ offsetRight WRITE setOffsetRight );
    Q_PROPERTY( int offsetBottom READ offsetBottom WRITE setOffsetBottom );


    const QString& layouter() const { return m_layouter;}
    void setLayouter(const QString& layouter) { m_layouter=layouter;}
    Q_PROPERTY( QString layouter READ layouter WRITE setLayouter );
private:
    QString m_layouter;
    bool    m_one_pixel_offset;
    bool    m_pot_image;
    int     m_size_increment;
    int     m_offset_left;
    int     m_offset_top;
    int     m_offset_right;
    int     m_offset_bottom;
signals:
    void layoutConfigChanged();

public slots:

};

#endif // LAYOUTCONFIG_H
