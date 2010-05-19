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

#include "targawriter.h"

#include "builtinimagewriter.h"
#include "layoutdata.h"
#include <QPixmap>
#include <QPainter>
#include "../layoutconfig.h"

TargaImageWriter::TargaImageWriter(QString ext,QObject *parent) :
    AbstractImageWriter(parent)
{
    setExtension(ext);
}


// byte-align structures
#if defined(_MSC_VER) ||  defined(__BORLANDC__) || defined (__BCPLUSPLUS__)
#	pragma pack( push, packing )
#	pragma pack( 1 )
#	define PACK_STRUCT
#elif defined( __GNUC__ )
#	define PACK_STRUCT	__attribute__((packed))
#else
#	define PACK_STRUCT
#endif

typedef unsigned char u8;
typedef char c8;
typedef unsigned short u16;
typedef unsigned int u32;

struct TGA_HEADER
{
        char idlength; //0: Size of Image-ID-Area
        char colourmaptype; //1: 0=no palette ; 1=palette present
        char datatypecode; //2: 0 - No IMage Date Included
        //   1 - Uncompressed Paletted Image
        //   2 - Uncompressed True Color
        //   3 - Uncompressed Black-White
        // 8+1 - RLE          Paletted Image
        // 8+2 - RLE          True Color
        // 8+3 - RLE          Black-White
        short int colourmaporigin; //3:
        short int colourmaplength; //5: Number of palette entries
        char colourmapdepth; //7: Bits per entry. Typicaly: 15,16,24,32
        short int x_origin; //8:
        short int y_origin; //10: Position coordinates on a display device
        short int width; //12:
        short int height; //14: Size of image in pixels
        char bitsperpixel; //16: Bits per pixel. Typicaly: 8,16,24,32
        char imagedescriptor; //17: 76-54-3210
        // NA-Orign-Alpha channel bits
}PACK_STRUCT;

// Default alignment
#if defined(_MSC_VER) ||  defined(__BORLANDC__) || defined (__BCPLUSPLUS__)
#	pragma pack( pop, packing )
#endif

#undef PACK_STRUCT


bool TargaImageWriter::Export(QFile& file) {
    QImage pixmap = buildImage();

    TGA_HEADER header;
    header.idlength = 0;
    header.colourmaptype = 0;
    header.datatypecode = 2;
    header.colourmaporigin = 0;
    header.colourmaplength = 0;
    header.colourmapdepth = 0;
    header.x_origin = 0;
    header.y_origin = 0;
    header.width = pixmap.width();
    header.height = pixmap.height();
    header.bitsperpixel = 32;
    header.imagedescriptor = 1 << 5;

    file.write((const char*)&header,18);
    for (int y=0;y<pixmap.height();y++) {
        /// @todo need endian control
        file.write((const char*)pixmap.scanLine(y),pixmap.width()*4);
    }



    return true;
}
