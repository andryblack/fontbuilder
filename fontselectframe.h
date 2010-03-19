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

#ifndef FONTSELECTFRAME_H
#define FONTSELECTFRAME_H

#include <QFrame>

#include <QMap>
#include <QVector>
#include <QByteArray>
#include <QPair>

struct FontDef {
    QString style;
    QString file;
    int face;
    bool fixedsize;
    QVector<QPair<int,int> > fixedsizes;
    FontDef() : style(),file(),face(0),fixedsize(false) {}
    FontDef(const QString& s,const QString& f,int num,bool fixedsize) : style(s),
        file(f),face(num),fixedsize(fixedsize) {}
};

class FontConfig;

typedef QVector<FontDef> FontStyles;
typedef QPair<QString,FontStyles> FontFamilsElement;
typedef QMap<QString,FontStyles> FontFamilys;

namespace Ui {
    class FontSelectFrame;
}

class FontSelectFrame : public QFrame {
    Q_OBJECT
public:
    FontSelectFrame(QWidget *parent);
    ~FontSelectFrame();

    void setConfig(FontConfig* config);
protected:
    void changeEvent(QEvent *e);

    void readFontSizes(const FontDef& def);
private:
    Ui::FontSelectFrame *ui;
    FontFamilys m_database;
    FontConfig* m_config;
signals:
private slots:
    void on_comboBoxSize_currentIndexChanged(QString );
    void on_comboBoxSize_editTextChanged(QString );
    void on_comboBoxStyle_currentIndexChanged(int index );
    void on_comboBoxFamily_currentIndexChanged(QString );
    void on_pushButtonChangeDir_clicked();

    void setFontsDirectory(QString dir);
};

#endif // FONTSELECTFRAME_H
