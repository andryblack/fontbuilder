/**
 * Copyright (C) 2010-2010, by Andrey AndryBlack Kunitsyn
 * (support.andryblack@gmail.com)
 */

#ifndef BOXLAYOUTER_H
#define BOXLAYOUTER_H

#include "../abstractlayouter.h"

class BoxLayouter : public AbstractLayouter
{
Q_OBJECT
public:
    explicit BoxLayouter(QObject *parent = 0);

    virtual void PlaceImages();
signals:

public slots:

};

#endif // BOXLAYOUTER_H
