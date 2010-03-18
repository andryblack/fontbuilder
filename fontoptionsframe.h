/**
 * Copyright (C) 2010-2010, by Andrey AndryBlack Kunitsyn
 * (support.andryblack@gmail.com)
 */

#ifndef FONTOPTIONSFRAME_H
#define FONTOPTIONSFRAME_H

#include <QFrame>

namespace Ui {
    class FontOptionsFrame;
}

class FontConfig;

class FontOptionsFrame : public QFrame {
    Q_OBJECT
public:
    FontOptionsFrame(QWidget *parent = 0);
    ~FontOptionsFrame();

    void setConfig(FontConfig* config);
protected:
    void changeEvent(QEvent *e);

private:
    Ui::FontOptionsFrame *ui;
    FontConfig* m_config;

private slots:
    void on_doubleSpinBoxHeight_valueChanged(double );
    void on_doubleSpinBoxWidth_valueChanged(double );
    void on_horizontalSliderItalic_valueChanged(int value);
    void on_horizontalSliderBold_valueChanged(int value);
    void on_checkBoxSmoothing_toggled(bool checked);
    void on_checkBoxMissingGlypths_toggled(bool checked);
    void on_checkBoxAutohinting_toggled(bool checked);
    void on_checkBoxAutohinting_clicked();
};

#endif // FONTOPTIONSFRAME_H
