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

#ifndef CHARMAPDIALOG_H
#define CHARMAPDIALOG_H

#include <QDialog>
#include <QSet>
#include <QListWidget>
#include <QListWidgetItem>
#include <QCheckBox>

namespace Ui {
    class CharMapDialog;
}

class CharMapDialog : public QDialog {
    Q_OBJECT
public:
    CharMapDialog(QWidget *parent = 0);
    ~CharMapDialog();

    void setChars(const QString& string);
    QString getCharacters() const;
protected:
    void changeEvent(QEvent *e);



private:
    Ui::CharMapDialog *ui;
    QSet<uint>  m_codes;

private slots:
    void on_listWidget_itemChanged(QListWidgetItem* item);
    void on_listWidget_currentItemChanged(QListWidgetItem* current, QListWidgetItem* previous);
    void onCharsChanged(uint code,bool add);
};

#endif // CHARMAPDIALOG_H
