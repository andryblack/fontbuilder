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

#include "fontbuilder.h"
#include "ui_fontbuilder.h"
#include <QDebug>
#include <QPainter>
#include <QPixmap>
#include "fontconfig.h"
#include "fontrenderer.h"
#include "layoutconfig.h"
#include "layoutdata.h"
#include "layouterfactory.h"



FontBuilder::FontBuilder(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FontBuilder)
{
    ui->setupUi(this);
    m_font_config = new FontConfig(this);
    m_font_renderer = new FontRenderer(this,m_font_config);

    connect(m_font_renderer,SIGNAL(imagesChanged()),this,SLOT(on_renderedChanged()));

    m_layout_config = new LayoutConfig(this);
    m_layout_data = new LayoutData(this);

    connect(m_layout_data,SIGNAL(layoutChanged()),this,SLOT(on_layoutChanged()));

    m_layouter = 0;
    m_layouter_factory = new LayouterFactory(this);

    ui->comboBoxLayouter->clear();
    ui->comboBoxLayouter->addItems(m_layouter_factory->names());




    ui->frameFontSelect->setConfig(m_font_config);
    ui->frameCharacters->setConfig(m_font_config);
    ui->frameFontOptions->setConfig(m_font_config);
    ui->frameLayoutConfig->setConfig(m_layout_config);

}

FontBuilder::~FontBuilder()
{
    delete ui;
}

void FontBuilder::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void FontBuilder::fontParametersChanged() {
    qDebug("font parameters changed");
}

void FontBuilder::on_comboBoxLayouter_currentIndexChanged(QString name)
{
    if (m_layouter) {
        delete m_layouter;
        m_layouter = 0;
    }
    m_layouter = m_layouter_factory->build(name,this);
    if (m_layouter) {
        m_layouter->setConfig(m_layout_config);
        m_layouter->setData(m_layout_data);
        connect(m_font_renderer,SIGNAL(imagesChanged(QVector<LayoutChar>)),
                m_layouter,SLOT(on_ReplaceImages(QVector<LayoutChar>)));
        m_layouter->on_ReplaceImages(m_font_renderer->rendered());
    }
}

void FontBuilder::on_renderedChanged() {

}

void FontBuilder::on_layoutChanged() {
    QPixmap pixmap(m_layout_data->width(),m_layout_data->height());
    pixmap.fill(QColor(0,0,0,255));
    QPainter painter(&pixmap);
    foreach (const LayoutChar& c,m_layout_data->placed())
        m_font_renderer->placeImage(painter,c.symbol,
                                    c.x + m_layout_config->offsetLeft(),
                                    c.y + m_layout_config->offsetTop()
                                    );
    if (m_layout_config->drawGrid()) {
        painter.setPen(QColor(255,0,255,255));
        if (m_layout_config->onePixelOffset())
            foreach (const LayoutChar& c,m_layout_data->placed()) {
                painter.drawRect(c.x-1,c.y-1,c.w,c.h);
            }
        else
            foreach (const LayoutChar& c,m_layout_data->placed()) {
                painter.drawRect(c.x,c.y,c.w-1,c.h-1);
            }
    }
    ui->label_Image->setPixmap(pixmap);
    ui->groupBoxPreview->setTitle(
            QString().number(m_layout_data->width()) + "x" +
            QString().number(m_layout_data->height())
            );
}
