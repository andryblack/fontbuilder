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

#include "charmapdialog.h"
#include "ui_charmapdialog.h"

CharMapDialog::CharMapDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CharMapDialog)
{
    ui->setupUi(this);
    ui->widget->setCodes(&m_codes);

    const struct {
        QString name;
        uint begin;
        uint end;
    } ranges[] = {
        {"C0 Controls and Basic Latin",         0x0000,0x007F },
        {"C1 Controls and Latin-1 Supplement",  0x0080,0x01FF },
        {"Latin Extended-A",                    0x0100,0x017F },
        {"Latin Extended-B",                    0x0180,0x024F },
        {"Greek and Coptic",                    0x0370,0x03FF },
        {"Cyrillic",                            0x0400,0x04FF },
        {"Cyrillic Supplementary",              0x0500,0x052F },
        {"Armenian",                            0x0530,0x058F },
        {"Hebrew",                              0x0590,0x05FF },
        {"Arabic",                              0x0600,0x06FF },
        {"Syriac",                              0x0700,0x074F },
        {"Thaana",                              0x0780,0x07BF },
        {"Devanagari",                          0x0900,0x097F },
        {"Bengali",                             0x0980,0x09FF },
        {"Gurmukhi",                            0x0A00,0x0A7F },
        {"Gujarati",                            0x0A80,0x0AFF },
        {"Oriya",                               0x0B00,0x0B7F },
        {"Tamil",                               0x0B80,0x0BFF },
        {"Telugu",                              0x0C00,0x0C7F },
        {"Kannada",                             0x0C80,0x0CFF },
        {"Malayalam",                           0x0D00,0x0D7F },
        {"Sinhala",                             0x0D80,0x0DFF },
        {"Thai",                                0x0E00,0x0E7F },
        {"Lao",                                 0x0E80,0x0EFF },
        {"Tibetan",                             0x0F00,0x0FFF },
        {"Myanmar",                             0x1000,0x109F },
        {"Georgian",                            0x10A0,0x10FF },
        {"Hangul Jamo",                         0x1100,0x11FF },
        {"Ethiopic",                            0x1200,0x137F },
        {"Cherokee",                            0x13A0,0x13FF },
        {"Ogham",                               0x1680,0x169F },
        {"Runic",                               0x16A0,0x16FF },
        {"Tagalog",                             0x1700,0x171F },
        {"Hanunoo",                             0x1720,0x173F },
        {"Buhid",                               0x1740,0x175F },
        {"Tagbanwa",                            0x1760,0x177F },
        {"Khmer",                               0x1780,0x17FF },
        {"Mongolian",                           0x1800,0x18AF },
        {"Limbu",                               0x1900,0x194F },
        {"Tai Le",                              0x1950,0x197F },
        {"Khmer Symbols",                       0x19E0,0x19FF },
        {"Phonetic Extensions",                 0x1D00,0x1D7F },
        {"Latin Extended Additional",           0x1E00,0x1EFF },
        {"Greek Extended",                      0x1F00,0x1FFF },
        {"General Punctuation",                 0x2000,0x206F },
        {"Superscripts and Subscripts",         0x2070,0x209F },
        {"Currency Symbols",                    0x20A0,0x20CF },
        {"Combining Diacritical Marks for Symbols", 0x20D0,0x20FF },
        {"Letterlike Symbols",                  0x2100,0x214F },
        {"Number Forms",                        0x2150,0x218F },
        {"Arrows",                              0x2190,0x21FF },
        {"Mathematical Operators",              0x2200,0x22FF },
        {"Miscellaneous Technical",             0x2300,0x23FF },
        {"Control Pictures",                    0x2400,0x243F },
        {"Optical Character Recognition",       0x2440,0x245F },
        {"Enclosed Alphanumerics",              0x2460,0x24FF },
        {"Box Drawing",                         0x2500,0x257F },
        {"Block Elements",                      0x2580,0x259F },
        {"Geometric Shapes",                    0x25A0,0x25FF },
        {"Miscellaneous Symbols",               0x2600,0x26FF },
        {"Dingbats",                            0x2700,0x27BF },
        {"Alphabetic Presentation Forms",       0xFB00,0xFB4F },
        {"Arabic Presentation Forms-A",         0xFB50,0xFDFF },
    };

    for (size_t i=0;i<sizeof(ranges)/sizeof(ranges[0]);i++) {
        QListWidgetItem* item = new QListWidgetItem(ranges[i].name,ui->listWidget);
        uint begin = ranges[i].begin;
        uint end = ranges[i].end;
        bool have = false;

        item->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
        item->setCheckState(have ? Qt::Checked : Qt::Unchecked);
        item->setData(Qt::UserRole+1,begin);
        item->setData(Qt::UserRole+2,end);
    }

    connect(ui->widget,SIGNAL(codesChanged(uint,bool)),this,SLOT(onCharsChanged(uint,bool)));
}

CharMapDialog::~CharMapDialog()
{
    delete ui;
}

void CharMapDialog::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void CharMapDialog::setChars(const QString& string) {
    m_codes.clear();
    const ushort* codes = string.utf16();
    while (*codes) {
        m_codes.insert(*codes);
        onCharsChanged(*codes,true);
        codes++;
    }

}

QString CharMapDialog::getCharacters() const {
    QString str;
    foreach( uint code , m_codes) {
        str.append(QString().fromUcs4(&code,1));
    }
    return str;
}

void CharMapDialog::onCharsChanged(uint code,bool add) {
    for (int row=0 ; row<ui->listWidget->count();row++) {
        QListWidgetItem* item = ui->listWidget->item(row);
        uint begin = item->data(Qt::UserRole+1).toInt();
        uint end = item->data(Qt::UserRole+2).toInt();
        if (code>=begin && code<=end) {
            bool block = ui->listWidget->blockSignals(true);
            if (add) {
                item->setCheckState(Qt::Checked);
            } else {
                bool have = false;
                foreach (uint c, m_codes ) {
                    if (c>=begin && c<=end) {
                        have = true;
                        break;
                    }
                }
                item->setCheckState(have ? Qt::Checked : Qt::Unchecked );
            }
            ui->listWidget->blockSignals(block);
        }
    }
}

void CharMapDialog::on_listWidget_currentItemChanged(QListWidgetItem* current, QListWidgetItem* previous)
{
    Q_UNUSED(previous);
    uint begin = current->data(Qt::UserRole+1).toInt();
    uint end = current->data(Qt::UserRole+2).toInt();
    ui->widget->setRange(begin,end);
}

void CharMapDialog::on_listWidget_itemChanged(QListWidgetItem* item)
{
    bool checked = item->checkState() == Qt::Checked;
    uint begin = item->data(Qt::UserRole+1).toInt();
    uint end = item->data(Qt::UserRole+2).toInt();
    if (checked) {
        for (uint i=begin;i<=end;i++) {
            m_codes.insert(i);
        }
    } else {
        for (uint i=begin;i<=end;i++) {
            QSet<uint>::Iterator it = m_codes.find(i);
            if (it!=m_codes.end())
                m_codes.erase(it);
        }
    }
    ui->widget->update();
}
