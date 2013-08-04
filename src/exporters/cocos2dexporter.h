// Exporter for Cocos 2D Framework

#ifndef COCOS2DEXPORTER_H
#define COCOS2DEXPORTER_H

#include "../abstractexporter.h"

class Cocos2dExporter : public AbstractExporter
{
    Q_OBJECT
public:
    explicit Cocos2dExporter(QObject *parent = 0);

    virtual bool Export(QByteArray& out);
signals:

public slots:

};

#endif // COCOS2DEXPORTER_H
