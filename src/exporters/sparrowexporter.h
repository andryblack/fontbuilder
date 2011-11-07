// Exporter for Sparrow Framework
// http://www.sparrow-framework.org/

#ifndef SPARROWEXPORTER_H
#define SPARROWEXPORTER_H

#include "../abstractexporter.h"

class SparrowExporter : public AbstractExporter
{
    Q_OBJECT
public:
    explicit SparrowExporter(QObject *parent = 0);

    virtual bool Export(QByteArray& out);
signals:

public slots:

};

#endif // SPARROWEXPORTER_H
