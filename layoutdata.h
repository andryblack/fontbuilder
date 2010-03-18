#ifndef LAYOUTDATA_H
#define LAYOUTDATA_H

#include <QObject>
#include <QVector>

#include "layoutchar.h"

class LayoutData : public QObject
{
Q_OBJECT
public:
    explicit LayoutData(QObject *parent = 0);
    int width() const { return m_width;}
    int height() const { return m_height;}
    Q_PROPERTY( int width READ width );
    Q_PROPERTY( int height READ height );
    void resize(int w,int h);
    void beginPlacing();
    void placeChar(const LayoutChar& c);
    void endPlacing();

    const QVector<LayoutChar>& placed() const { return m_placed;}
private:
    int m_width;
    int m_height;
    QVector<LayoutChar> m_placed;
signals:
    void layoutChanged();
public slots:

};

#endif // LAYOUTDATA_H
