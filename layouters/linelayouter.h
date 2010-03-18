#ifndef LINELAYOUTER_H
#define LINELAYOUTER_H

#include "../abstractlayouter.h"

class LineLayouter : public AbstractLayouter
{
Q_OBJECT
public:
    explicit LineLayouter(QObject *parent = 0);

protected:
    virtual void PlaceImages();
signals:

public slots:

};

#endif // LINELAYOUTER_H
