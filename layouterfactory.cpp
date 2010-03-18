#include "layouterfactory.h"


extern AbstractLayouter* LineLayouterFactoryFunc (QObject*);
extern AbstractLayouter* BoxLayouterFactoryFunc (QObject*);

LayouterFactory::LayouterFactory(QObject *parent) :
    QObject(parent)
{
    m_factorys["Line layout"] = &LineLayouterFactoryFunc;
    m_factorys["Box layout"] = &BoxLayouterFactoryFunc;
}


QStringList LayouterFactory::names() const {
    return m_factorys.keys();
}

AbstractLayouter* LayouterFactory::build(const QString &name,QObject* parent) {
    if (m_factorys.contains(name)) {
        return m_factorys[name](parent);
    }
    return 0;
}
