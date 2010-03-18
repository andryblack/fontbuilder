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

    bool potImage() const { return m_pot_image;}
    void setPotImage(bool b);
    Q_PROPERTY( bool potImage READ potImage WRITE setPotImage );

    void setOffsetLeft(int v);
    void setOffsetTop(int v);
    void setOffsetRight(int v);
    void setOffsetBottom(int v);

    int offsetLeft() const { return m_offset_left;}
    int offsetTop() const { return m_offset_top;}
    int offsetRight() const { return m_offset_right;}
    int offsetBottom() const { return m_offset_bottom;}

    Q_PROPERTY( int offsetLeft READ offsetLeft WRITE setOffsetLeft );
    Q_PROPERTY( int offsetTop READ offsetTop WRITE setOffsetTop );
    Q_PROPERTY( int offsetRight READ offsetRight WRITE setOffsetRight );
    Q_PROPERTY( int offsetBottom READ offsetBottom WRITE setOffsetBottom );
private:
    bool    m_one_pixel_offset;
    bool    m_pot_image;
    int     m_offset_left;
    int     m_offset_top;
    int     m_offset_right;
    int     m_offset_bottom;
signals:
    void layoutConfigChanged();
public slots:

};

#endif // LAYOUTCONFIG_H
