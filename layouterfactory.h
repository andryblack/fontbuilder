#ifndef LAYOUTERFACTORY_H
#define LAYOUTERFACTORY_H

#include <QObject>
#include <QStringList>
#include <QMap>
#include "abstractlayouter.h"


typedef AbstractLayouter* (*LayouterFactoryFunc) (QObject*);

class LayouterFactory : public QObject
{
Q_OBJECT
public:
    explicit LayouterFactory(QObject *parent = 0);
    AbstractLayouter* build(const QString& name,QObject *parent);
    QStringList names() const;
private:
    QMap<QString,LayouterFactoryFunc> m_factorys;
signals:

public slots:

};

#endif // LAYOUTERFACTORY_H
