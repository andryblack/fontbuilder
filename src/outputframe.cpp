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

#include "outputframe.h"
#include "ui_outputframe.h"

#include "outputconfig.h"

#include <QFileDialog>
#include <QImage>
#include <QImageWriter>


OutputFrame::OutputFrame(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::OutputFrame)
{
    m_config = 0;
    ui->setupUi(this);
    /*foreach( QByteArray format , QImageWriter::supportedImageFormats()) {
        QString name = format;
        ui->comboBoxImageFormat->addItem(name,format);
    }*/
    ui->widgetGridColor->setColor(QColor(255,0,255,255));
}

OutputFrame::~OutputFrame()
{
    delete ui;
}

void OutputFrame::changeEvent(QEvent *e)
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

void OutputFrame::setConfig(OutputConfig* config) {
    m_config = config;
    if (config) {
        ui->lineEditPath->setText(config->path());
        connect(config,SIGNAL(imageNameChanged(QString)),this,SLOT(onImageNameChanged(QString)));
        onImageNameChanged(config->imageName());
        connect(config,SIGNAL(descriptionNameChanged(QString)),this,SLOT(onDescriptionNameChanged(QString)));
        onDescriptionNameChanged(config->descriptionName());
        for (int i=0;i<ui->comboBoxImageFormat->count();i++)
            if (ui->comboBoxImageFormat->itemText(i)==config->imageFormat())
                ui->comboBoxImageFormat->setCurrentIndex(i);
        ui->groupBoxImage->setChecked(config->writeImage());
        if (ui->groupBoxDescription->isEnabled())
            ui->groupBoxDescription->setChecked(config->writeDescription());
        else
            config->setWriteDescription(false);

        for (int i=0;i<ui->comboBoxDescriptionType->count();i++)
            if (ui->comboBoxDescriptionType->itemText(i)==config->descriptionFormat())
                ui->comboBoxDescriptionType->setCurrentIndex(i);
        config->setDescriptionFormat(ui->comboBoxDescriptionType->currentText());
        ui->checkBoxGenerateX2->setChecked(config->generateX2());
    }
}

void OutputFrame::on_pushButtonSelectPath_clicked()
{
    QString dir = QFileDialog::getExistingDirectory(
            this,tr("Select output directory"),
            ui->lineEditPath->text());
    if (!dir.isEmpty()) {
        if (m_config) m_config->setPath(dir);
        ui->lineEditPath->setText(dir);
    }
}

void OutputFrame::onImageNameChanged(const QString& s) {
    ui->lineEditImageFilename->setText(s);
}

void OutputFrame::onDescriptionNameChanged(const QString& s) {
    ui->lineEditDescriptionFilename->setText(s);
}

void OutputFrame::on_lineEditImageFilename_editingFinished()
{
    if (m_config) m_config->setImageName(ui->lineEditImageFilename->text());
}

void OutputFrame::on_lineEditDescriptionFilename_editingFinished()
{
    if (m_config) m_config->setDescriptionName(ui->lineEditDescriptionFilename->text());
}

void OutputFrame::on_comboBoxImageFormat_currentIndexChanged(QString name)
{
    if (m_config) m_config->setImageFormat(name);
}

void OutputFrame::on_groupBoxImage_toggled(bool checked)
{
    if (m_config) m_config->setWriteImage(checked);
}

void OutputFrame::on_groupBoxDescription_toggled(bool checked)
{
    if (m_config) m_config->setWriteDescription(checked);
}

void OutputFrame::on_checkBoxDrawGrid_toggled(bool checked)
{
    ui->widgetGridColor->setEnabled(checked);
}

void OutputFrame::setExporters(const QStringList& exporters) {
    bool bs = ui->comboBoxDescriptionType->blockSignals(true);
    ui->comboBoxDescriptionType->clear();
    ui->comboBoxDescriptionType->addItems(exporters);
    ui->comboBoxDescriptionType->blockSignals(bs);
}

void OutputFrame::setImageWriters(const QStringList& writers) {
    bool bs = ui->comboBoxImageFormat->blockSignals(true);
    ui->comboBoxImageFormat->clear();
    ui->comboBoxImageFormat->addItems(writers);
    ui->comboBoxImageFormat->blockSignals(bs);
}


void OutputFrame::on_comboBoxDescriptionType_currentIndexChanged(QString name)
{
    if (m_config) m_config->setDescriptionFormat(name);
}

void OutputFrame::on_checkBoxGenerateX2_stateChanged(int arg1)
{
    if (m_config) m_config->setGenerateX2(arg1==Qt::Checked);
}
