/**
 * Copyright (c) 2010-2010 Andrey AndryBlack Kunitsyn
 * email:support.andryblack@gmail.com
 *
 * Report bugs and download new versions at http://code.google.com/p/fontbuilder
 *
 * This software is distributed under the MIT License.
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
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
    void on_comboBoxDPI_currentIndexChanged(QString );
    void on_spinBoxLineSpacing_valueChanged(int );
    void on_spinBoxCharSpacing_valueChanged(int );
    void on_doubleSpinBoxHeight_valueChanged(double );
    void on_doubleSpinBoxWidth_valueChanged(double );
    void on_horizontalSliderItalic_valueChanged(int value);
    void on_horizontalSliderBold_valueChanged(int value);
    void on_checkBoxSmoothing_toggled(bool checked);
    void on_checkBoxMissingGlypths_toggled(bool checked);
    void on_checkBoxAutohinting_toggled(bool checked);
    void on_comboBox_Hinting_currentIndexChanged(int index);
    void on_comboBoxAA_currentIndexChanged(int index);
};

#endif // FONTOPTIONSFRAME_H
