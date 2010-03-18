/**
 * Copyright (C) 2010-2010, by Andrey AndryBlack Kunitsyn
 * (support.andryblack@gmail.com)
 */

#ifndef COLORBUTTON_H
#define COLORBUTTON_H

#include <QWidget>
#include <QColor>
#include <QLabel>

class ColorButton : public QLabel
{
Q_OBJECT
public:
    explicit ColorButton(QWidget *parent = 0);
    Q_PROPERTY( QColor color READ color WRITE setColor );
    QColor color() const { return m_color;}
    void setColor(const QColor& c) { m_color = c;}
protected:
    QColor  m_color;
    void paintEvent(QPaintEvent *);
    void mouseReleaseEvent(QMouseEvent *ev);
signals:
    void colorChanged(QColor);
    void colorChanged();
public slots:

};

#endif // COLORBUTTON_H
