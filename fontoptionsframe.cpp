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
    ui->checkBoxBold->setChecked(m_config->bold());
    ui->checkBoxItalic->setChecked(m_config->italic());
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

void FontOptionsFrame::on_checkBoxBold_toggled(bool checked)
{
    if (m_config) m_config->setBold(checked);
}

void FontOptionsFrame::on_checkBoxItalic_toggled(bool checked)
{
    if (m_config) m_config->setItalic(checked);
}
