#ifndef BOXLAYOUTEROPTIMIZED_H
#define BOXLAYOUTEROPTIMIZED_H

#include "boxlayouter.h"

class BoxLayouterOptimized : public BoxLayouter
{
public:
    BoxLayouterOptimized(QObject *parent);

private:
    static bool SortCharsByHeight(const LayoutChar &a, const LayoutChar &b);
    void OptimizeLayout(QVector<LayoutChar> &chars);
};

#endif // BOXLAYOUTEROPTIMIZED_H
