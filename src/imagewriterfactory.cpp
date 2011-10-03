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

#include "imagewriterfactory.h"
#include "image/builtinimagewriter.h"
#include "image/targawriter.h"

static AbstractImageWriter* PNG_img_writer(QObject* parent) {
    return new BuiltinImageWriter("png","PNG",parent);
}
static AbstractImageWriter* png_img_writer(QObject* parent) {
    return new BuiltinImageWriter("png","png",parent);
}

static AbstractImageWriter* TGA_img_writer(QObject* parent) {
    return new TargaImageWriter("TGA",parent);
}
static AbstractImageWriter* tga_img_writer(QObject* parent) {
    return new TargaImageWriter("tga",parent);
}

ImageWriterFactory::ImageWriterFactory(QObject *parent) :
    QObject(parent)
{
    m_factorys["png"] = &png_img_writer;
    m_factorys["PNG"] = &PNG_img_writer;
    m_factorys["tga"] = &tga_img_writer;
    m_factorys["TGA"] = &TGA_img_writer;
}

QStringList ImageWriterFactory::names() const {
    return m_factorys.keys();
}

AbstractImageWriter* ImageWriterFactory::build(const QString &name,QObject* parent) {
    if (m_factorys.contains(name)) {
        return m_factorys[name](parent);
    }
    return 0;
}
