#include "zfiexporter.h"
#include "../fontconfig.h"
#include "../layoutdata.h"

ZFIExporter::ZFIExporter(QObject *parent) :
    AbstractExporter(parent)
{
    setExtension("zfi");
}

bool ZFIExporter::Export(QByteArray& out) {
  unsigned short Pages = 1;
  unsigned short Chars = 0;
  int MaxHeight = 0;
  int MaxShiftY = 0;
  int PageWidth = texWidth();
  int PageHeight = texHeight();
  unsigned char Padding[4] = { 0, 0, 0, 0 };
  zglTCharDesc CharDesc;

  foreach ( const Symbol& c, symbols() )
  {
    if ( c.placeH > MaxHeight )
      MaxHeight = c.placeH;
    if ( c.placeH - c.offsetY > MaxShiftY )
      MaxShiftY = c.placeH - c.offsetY;

    Chars++;
  }

  out.append( "ZGL_FONT_INFO", 13 );
  out.append( (char*)&Pages, 2 );
  out.append( (char*)&Chars, 2 );
  out.append( (char*)&MaxHeight, 4 );
  out.append( (char*)&MaxShiftY, 4 );
  out.append( (char*)&Padding, 4 );

  foreach ( const Symbol& c, symbols() )
  {
    int id = c.id;
    float u = 1.f / PageWidth, v = 1.f / PageHeight;
    out.append( (char*)&id, 4 );

    CharDesc.Page = 0;
    CharDesc.Width = c.placeW;
    CharDesc.Height = c.placeH;
    CharDesc.ShiftX = c.offsetX;
    CharDesc.ShiftY = c.placeH - c.offsetY;
    CharDesc.ShiftP = c.advance;

    CharDesc.TexCoords[ 0 ].X = (float)u * c.placeX;
    CharDesc.TexCoords[ 0 ].Y = 1 - (float)v * c.placeY;
    CharDesc.TexCoords[ 1 ].X = (float)u * ( c.placeX + c.placeW );
    CharDesc.TexCoords[ 1 ].Y = 1 - (float)v * c.placeY;
    CharDesc.TexCoords[ 2 ].X = (float)u * ( c.placeX + c.placeW );
    CharDesc.TexCoords[ 2 ].Y = 1 - (float)v * ( c.placeY + c.placeH );
    CharDesc.TexCoords[ 3 ].X = (float)u * c.placeX;
    CharDesc.TexCoords[ 3 ].Y = 1 - (float)v * ( c.placeY + c.placeH );

    out.append( (char*)&CharDesc.Page, 4 );
    out.append( (char*)&CharDesc.Width, 1 );
    out.append( (char*)&CharDesc.Height, 1 );
    out.append( (char*)&CharDesc.ShiftX, 4 );
    out.append( (char*)&CharDesc.ShiftY, 4 );
    out.append( (char*)&CharDesc.ShiftP, 4 );
    out.append( (char*)&CharDesc.TexCoords, sizeof( zglTPoint2D ) * 4 );
  }

  return true;
}


AbstractExporter* ZFIExporterFactoryFunc (QObject* parent) {
    return new ZFIExporter(parent);
}
