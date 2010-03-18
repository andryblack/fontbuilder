#ifndef LAYOUTCONFIG_H
#define LAYOUTCONFIG_H

#include <QObject>

class LayoutConfig : public QObject
{
Q_OBJECT
public:
    explicit LayoutConfig(QObject *parent = 0);

    bool onePixelOffset() const { return m_one_pixel_offset;}
    void setOnePixelOffset(bool b);
    Q_PROPERTY( bool onePixelOffset READ onePixelOffset WRITE setOnePixelOffset );
private:
    bool    m_one_pixel_offset;
signals:
    void layoutConfigChanged();
public slots:

};

#endif // LAYOUTCONFIG_H
