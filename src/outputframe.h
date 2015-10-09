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

#ifndef OUTPUTFRAME_H
#define OUTPUTFRAME_H

#include <QFrame>

namespace Ui {
    class OutputFrame;
}

class OutputConfig;

class OutputFrame : public QFrame {
    Q_OBJECT
public:
    OutputFrame(QWidget *parent = 0);
    ~OutputFrame();

    void setExporters(const QStringList& exporters);
    void setImageWriters(const QStringList& writers);
    void setConfig(OutputConfig* config);

protected:
    void changeEvent(QEvent *e);

private:
    Ui::OutputFrame *ui;
    OutputConfig*   m_config;

private slots:
    void on_comboBoxDescriptionType_currentIndexChanged(QString );
    void on_checkBoxDrawGrid_toggled(bool checked);
    void on_groupBoxDescription_toggled(bool );
    void on_groupBoxImage_toggled(bool );
    void on_comboBoxImageFormat_currentIndexChanged(QString );
    void onImageNameChanged(const QString& s);
    void onDescriptionNameChanged(const QString& s);
    void on_lineEditImageFilename_editingFinished( );
    void on_lineEditDescriptionFilename_editingFinished( );
    void on_pushButtonSelectPath_clicked();

    void on_checkBoxGenerateX2_stateChanged(int arg1);
};

#endif // OUTPUTFRAME_H
