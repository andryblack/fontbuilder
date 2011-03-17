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

#ifndef FONTBUILDER_H
#define FONTBUILDER_H

#include <QMainWindow>
#include <QSettings>

namespace Ui {
    class FontBuilder;
}

struct FontRenderer;
class FontConfig;
class LayoutConfig;
class LayoutData;
class AbstractLayouter;
class LayouterFactory;
class OutputConfig;
class ExporterFactory;
class AbstractExporter;
class ImageWriterFactory;
class AbstractImageWriter;


class FontBuilder : public QMainWindow {
    Q_OBJECT
public:
    FontBuilder(QWidget *parent = 0);
    ~FontBuilder();

protected:
    void changeEvent(QEvent *e);
    void closeEvent(QCloseEvent *event);
    void saveConfig(QSettings& config,const QString& name,const QObject* obj);
    void readConfig(QSettings& config,const QString& name,QObject* obj);

private:

    Ui::FontBuilder *ui;
    FontRenderer*   m_font_renderer;
    FontConfig*     m_font_config;
    LayoutConfig*   m_layout_config;
    LayoutData*     m_layout_data;
    AbstractLayouter* m_layouter;
    LayouterFactory*    m_layouter_factory;
    OutputConfig*   m_output_config;
    ExporterFactory* m_exporter_factory;
    ImageWriterFactory* m_image_writer_factory;
    AbstractImageWriter* m_image_writer;

    void setLayoutImage(const QImage& img);
public slots:

    void fontParametersChanged();

private slots:
    void on_pushButtonWriteFont_clicked();
    void on_comboBoxLayouter_currentIndexChanged(QString );
    void on_checkBoxDrawGrid_toggled(bool);
    void onLayoutChanged();
    void onRenderedChanged();
    void onFontNameChanged();
    void onExternalImageChanged(const QString& img);
    void onSpacingChanged();
    void on_comboBox_currentIndexChanged(int index);
};

#endif // FONTBUILDER_H
