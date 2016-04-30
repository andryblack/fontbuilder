#include "ageexporter.h"
#include "../fontconfig.h"
#include "../layoutdata.h"

struct AGEHeader
{
    char header[4];
    unsigned count;
    float height;
};
static const char* AGEsig = "AGEF";

template<typename T>
void append(QByteArray& out, T val)
{
    out.append((char*)&val, sizeof(T));
}



AGEExporter::AGEExporter(QObject* parent)
    : AbstractExporter(parent)
{
    setExtension("agefnt");
}

bool AGEExporter::sortSymbols(const Symbol& a, const Symbol& b)
{
    return a.id < b.id;
}

bool AGEExporter::Export(QByteArray& out)
{
    QVector<Symbol> list = symbols();
    qSort(list.begin(), list.end(), sortSymbols);

    unsigned charsCount = list.size();
    unsigned maxHeight = 0;

    foreach(const Symbol& c, list)
    {
        maxHeight = std::max<float>(maxHeight, c.placeH);
    }

    AGEHeader header;
    memcpy(header.header, AGEsig, sizeof(header.header));
    header.count = charsCount;
    header.height = maxHeight;
    append(out, header);

    foreach(const Symbol& c, list)
    {
        append(out, (unsigned)c.id);
        append(out, (float)c.placeX);
        append(out, (float)c.placeY);
        append(out, (float)(c.placeX + c.placeW));
        append(out, (float)(c.placeY + c.placeH));
        append(out, (float)c.offsetX);
        append(out, (float)(maxHeight - c.offsetY));
        append(out, (float)c.advance);
    }

    return true;
}

AbstractExporter* AGEExporterFactoryFunc(QObject* parent)
{
    return new AGEExporter(parent);
}
