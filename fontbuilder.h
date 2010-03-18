/**
 * Copyright (C) 2010-2010, by Andrey AndryBlack Kunitsyn
 * (support.andryblack@gmail.com)
 */

#ifndef FONTBUILDER_H
#define FONTBUILDER_H

#include <QMainWindow>

namespace Ui {
    class FontBuilder;
}

struct FontRenderer;
class FontConfig;
class LayoutConfig;
class LayoutData;
class AbstractLayouter;
class LayouterFactory;

class FontBuilder : public QMainWindow {
    Q_OBJECT
public:
    FontBuilder(QWidget *parent = 0);
    ~FontBuilder();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::FontBuilder *ui;
    FontRenderer*   m_font_renderer;
    FontConfig*     m_font_config;
    LayoutConfig*   m_layout_config;
    LayoutData*     m_layout_data;
    AbstractLayouter* m_layouter;
    LayouterFactory*    m_layouter_factory;
public slots:

    void fontParametersChanged();
private slots:

private slots:
    void on_comboBoxLayouter_currentIndexChanged(QString );
    void on_layoutChanged();
    void on_renderedChanged();
};

#endif // FONTBUILDER_H
