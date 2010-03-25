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

OutputFrame::OutputFrame(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::OutputFrame)
{
    ui->setupUi(this);
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
    }
}

void OutputFrame::on_pushButtonSelectPath_clicked()
{
    QString dir = QFileDialog::getExistingDirectory(
            this,tr("Select fonts directory"),
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
