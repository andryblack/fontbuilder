/**
 * Copyright (C) 2010-2010, by Andrey AndryBlack Kunitsyn
 * (support.andryblack@gmail.com)
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
    ui->checkBoxAutohinting->setChecked(m_config->autohinting());
    ui->checkBoxMissingGlypths->setChecked(m_config->renderMissing());
    ui->checkBoxSmoothing->setChecked(m_config->antialiased());
    ui->horizontalSliderBold->setValue(m_config->bold());
    ui->horizontalSliderItalic->setValue(m_config->italic());
    ui->doubleSpinBoxWidth->setValue(m_config->width());
    ui->doubleSpinBoxHeight->setValue(m_config->height());
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
