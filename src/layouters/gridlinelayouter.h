#ifndef GRIDLINELAYOUTER_H
#define GRIDLINELAYOUTER_H

#include "gridlayouter.h"

class GridLineLayouter : public GridLayouter
{
public:
    GridLineLayouter(QObject *parent);

    // GridLayouter interface
protected:
    void calculateSize(int maxW, int maxH, size_t count);
};

#endif // GRIDLINELAYOUTER_H
