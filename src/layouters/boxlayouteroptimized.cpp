#include "boxlayouteroptimized.h"

BoxLayouterOptimized::BoxLayouterOptimized(QObject *parent)
    : BoxLayouter(parent)
{
}

bool BoxLayouterOptimized::SortCharsByHeight(const LayoutChar &a, const LayoutChar &b)
{
    if (a.h + a.y > b.h + b.y)
        return false;
    else if (a.h + a.y == b.h + b.y)
    {
        if (a.w > b.w)
            return false;
        else if (a.w == b.w)
        {
            if (a.y > b.y)
                return false;
            else if (a.y == b.y)
            {
                if (a.symbol > b.symbol)
                    return false;
            }
        }
    }
    return true;
}

void BoxLayouterOptimized::OptimizeLayout(QVector<LayoutChar> &chars)
{
    qSort(chars.begin(), chars.end(), SortCharsByHeight);
}


AbstractLayouter* BoxLayouterOptimizedFactoryFunc (QObject* parent) {
    return new BoxLayouterOptimized(parent);
}
