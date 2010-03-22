#include "layoutconfigframe.h"
#include "ui_layoutconfigframe.h"
#include "layoutconfig.h"

LayoutConfigFrame::LayoutConfigFrame(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::LayoutConfigFrame)
{
    ui->setupUi(this);
    m_config = 0;
}

LayoutConfigFrame::~LayoutConfigFrame()
{
    delete ui;
}

void LayoutConfigFrame::setConfig(LayoutConfig* config) {
    m_config = config;
    if (config) {
        ui->checkBoxOnePixelOffset->setChecked(config->onePixelOffset());
        ui->checkBoxPOT->setChecked(config->potImage());
        ui->spinBoxLeftOffset->setValue(config->offsetLeft());
        ui->spinBoxTopOffset->setValue(config->offsetTop());
        ui->spinBoxRightOffset->setValue(config->offsetRight());
        ui->spinBoxBottomOffset->setValue(config->offsetBottom());
        ui->checkBoxDrawGrid->setChecked(config->drawGrid());
    }
}

void LayoutConfigFrame::changeEvent(QEvent *e)
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

void LayoutConfigFrame::on_checkBoxOnePixelOffset_toggled(bool checked)
{
    if (m_config) m_config->setOnePixelOffset(checked);
}

void LayoutConfigFrame::on_checkBoxPOT_toggled(bool checked)
{
    if (m_config) m_config->setPotImage(checked);
}

void LayoutConfigFrame::on_spinBoxTopOffset_valueChanged(int value)
{
    if (m_config) m_config->setOffsetTop(value);
}

void LayoutConfigFrame::on_spinBoxLeftOffset_valueChanged(int value)
{
    if (m_config) m_config->setOffsetLeft(value);
}

void LayoutConfigFrame::on_spinBoxBottomOffset_valueChanged(int value)
{
    if (m_config) m_config->setOffsetBottom(value);
}

void LayoutConfigFrame::on_spinBoxRightOffset_valueChanged(int value)
{
    if (m_config) m_config->setOffsetRight(value);
}

void LayoutConfigFrame::on_checkBoxDrawGrid_toggled(bool checked)
{
    if (m_config) m_config->setDrawGrid(checked);
}
