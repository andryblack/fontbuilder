/**
 * Copyright (C) 2010-2010, by Andrey AndryBlack Kunitsyn
 * (support.andryblack@gmail.com)
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
    ui->label_Image->setPixmap(pixmap);
}
