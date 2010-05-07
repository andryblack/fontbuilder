/**
 * Copyright (C) 2010-2010, by Andrey AndryBlack Kunitsyn
 * (support.andryblack@gmail.com)
 */

#ifndef GHLEXPORTER_H
#define GHLEXPORTER_H

#include "../abstractexporter.h"

class GHLExporter : public AbstractExporter
{
Q_OBJECT
public:
    explicit GHLExporter(QObject *parent = 0);
protected:
    virtual bool Export(QByteArray& out);
signals:

public slots:

};

#endif // GHLEXPORTER_H
