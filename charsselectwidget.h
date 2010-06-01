#ifndef CHARSSELECTWIDGET_H
#define CHARSSELECTWIDGET_H

#include <QWidget>
#include <QSet>

class CharsSelectWidget : public QWidget
{
Q_OBJECT
public:
    explicit CharsSelectWidget(QWidget *parent = 0);

    void setRange(uint begin,uint end);
    void setCodes(QSet<uint>* codes) { m_codes=codes;}
protected:
    virtual void paintEvent(QPaintEvent *);
    virtual void mousePressEvent(QMouseEvent *);
    virtual void mouseReleaseEvent(QMouseEvent *);
    virtual void mouseMoveEvent(QMouseEvent *);
    virtual QSize sizeHint() const ;
signals:

public slots:

private:
    uint    m_codes_begin;
    uint    m_codes_end;
    uint    m_select_begin_code;
    uint    m_select_last_code;
    QSet<uint>* m_codes;

    bool m_track_mouse;
    bool m_track_erase;
};

#endif // CHARSSELECTWIDGET_H
