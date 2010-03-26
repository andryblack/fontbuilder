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

#include "fontoptionsframe.h"
#include "ui_fontoptionsframe.h"
#include "fontconfig.h"

FontOptionsFrame::FontOptionsFrame(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::FontOptionsFrame)
{
    ui->setupUi(this);
    m_config = 0;
}

FontOptionsFrame::~FontOptionsFrame()
{
    delete ui;
}

void FontOptionsFrame::changeEvent(QEvent *e)
{
    QFrame::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void FontOptionsFrame::setConfig(FontConfig *config) {
    m_config = config;
    if (config) {
        ui->checkBoxAutohinting->setChecked(m_config->autohinting());
        ui->checkBoxMissingGlypths->setChecked(m_config->renderMissing());
        ui->checkBoxSmoothing->setChecked(m_config->antialiased());
        ui->horizontalSliderBold->setValue(m_config->bold());
        ui->horizontalSliderItalic->setValue(m_config->italic());
        ui->doubleSpinBoxWidth->setValue(m_config->width());
        ui->doubleSpinBoxHeight->setValue(m_config->height());


    }
}

void FontOptionsFrame::on_checkBoxAutohinting_clicked()
{

}

void FontOptionsFrame::on_checkBoxAutohinting_toggled(bool checked)
{
    if (m_config) m_config->setAutohinting(checked);
}

void FontOptionsFrame::on_checkBoxMissingGlypths_toggled(bool checked)
{
    if (m_config) m_config->setRenderMissing(checked);
}

void FontOptionsFrame::on_checkBoxSmoothing_toggled(bool checked)
{
    if (m_config) m_config->setAntialiased(checked);
}



void FontOptionsFrame::on_horizontalSliderBold_valueChanged(int value)
{
     if (m_config) m_config->setBold(value);
     ui->labelBold->setText(QString().number(value));
}

void FontOptionsFrame::on_horizontalSliderItalic_valueChanged(int value)
{
    if (m_config) m_config->setItalic(value);
    ui->labelItalic->setText(QString().number(value));
}

void FontOptionsFrame::on_doubleSpinBoxWidth_valueChanged(double value)
{
    if (m_config) m_config->setWidth(value);
}

void FontOptionsFrame::on_doubleSpinBoxHeight_valueChanged(double value)
{
    if (m_config) m_config->setHeight(value);
}