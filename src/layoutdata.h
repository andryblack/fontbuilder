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

#ifndef LAYOUTDATA_H
#define LAYOUTDATA_H


#include "layoutchar.h"

#include <QObject>
#include <QVector>
#include <QImage>

class LayoutData : public QObject
{
Q_OBJECT
public:
    explicit LayoutData(QObject *parent = 0);
    ~LayoutData();

    int width() const { return m_width;}
    int height() const { return m_height;}
    Q_PROPERTY( int width READ width );
    Q_PROPERTY( int height READ height );
    void resize(int w,int h);
    void beginPlacing();
    void placeChar(const LayoutChar& c);
    void endPlacing();

    const QVector<LayoutChar>& placed() const { return m_placed;}
    void setImage(const QImage& image) { m_image = image;}
    const QImage& image() const { return m_image;}
private:
    int m_width;
    int m_height;
    QVector<LayoutChar> m_placed;
    QImage    m_image;
signals:
    void layoutChanged();
public slots:

};

#endif // LAYOUTDATA_H
