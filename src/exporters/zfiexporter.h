#ifndef ZFIEXPORTER_H
#define ZFIEXPORTER_H

#include "../abstractexporter.h"

typedef struct
{
  float X;
  float Y;
} zglTPoint2D;

typedef struct
{
  unsigned short Page;
  unsigned char Width;
  unsigned char Height;
  int ShiftX;
  int ShiftY;
  int ShiftP;
  zglTPoint2D TexCoords[4];
} zglTCharDesc;

class ZFIExporter : public AbstractExporter
{
Q_OBJECT
public:
    explicit ZFIExporter(QObject *parent = 0);
protected:
    virtual bool Export(QByteArray& out);
signals:

public slots:

};

#endif // ZFIEXPORTER_H
