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

#include "fontselectframe.h"
#include "ui_fontselectframe.h"
#include <QDebug>
#include <QDir>
#include <QDesktopServices>
#include <QFileDialog>
#include <QProgressDialog>
#include <QDesktopServices>

#include "fontconfig.h"


#include <ft2build.h>
#include FT_FREETYPE_H
#undef __FTERRORS_H__
static const char* get_error_descr(FT_Error err) {
#define FT_ERRORDEF( e, v, s )  case e: return s;
#define FT_ERROR_START_LIST     switch (err) {
#define FT_ERROR_END_LIST      }
#include FT_ERRORS_H
    return "unknown";
}


FontSelectFrame::FontSelectFrame(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::FontSelectFrame)
{
    ui->setupUi(this);




    m_config = 0;

}


FontSelectFrame::~FontSelectFrame()
{
    delete ui;


}


void FontSelectFrame::changeEvent(QEvent *e)
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

void FontSelectFrame::setConfig(FontConfig* config) {
    m_config = 0;
    if (config) {
        bool b = config->blockSignals(true);
        if (!config->path().isEmpty())
            setFontsDirectory(config->path());
        if (!config->filename().isEmpty())
            selectFile(config->filename(),config->faceIndex());
        else if (!m_database.isEmpty()) {
            const FontDef& def = m_database.constBegin()->front();
            selectFile(def.file,def.face);
            config->setFilename(def.file);
        }
        if (config->size()==0)
            config->setSize(ui->comboBoxSize->itemText(0).toInt());
        if (config->size())
            selectSize(config->size());

        config->setFamily(ui->comboBoxFamily->itemText(ui->comboBoxFamily->currentIndex()));
        config->setStyle(ui->comboBoxStyle->itemText(ui->comboBoxStyle->currentIndex()));

        config->blockSignals(b);
        m_config = config;
    }

}

void FontSelectFrame::setFontsDirectory(QString dir_name) {

    if (m_config) m_config->setPath(dir_name);

    m_database.clear();



    ui->lineEditFontsDir->setText(dir_name);

    FT_Library library = 0;

    int error = FT_Init_FreeType(&library);
    if (error) {
        qDebug() << "FT_Open_Library error " << error;
        return;
    }


    QDir dir(dir_name);
    QStringList files = dir.entryList(
            QStringList()
            << "*.ttf"
            << "*.pcf"
            << "*.pcf.gz"
            << "*.otf"
            << "*.fon"
            << "*.FON",
            QDir::Files | QDir::Readable
            );
    QProgressDialog* progress = 0;
    if (!files.isEmpty()) {
        progress = new QProgressDialog(
                tr("Scanning directory.."),
                tr("Cancel"),
                0,files.size(),this);
        progress->setCancelButton(0);
        progress->setWindowModality(Qt::WindowModal);
        //progress->show();
    }
    int progress_val = 0;
    foreach (QString file_name, files) {
        //qDebug() << "found font file : " << file_name;
        QFile file(dir.filePath(file_name));
        if (file.open(QFile::ReadOnly)) {
            QByteArray bytes = file.readAll();
            const FT_Byte* data = reinterpret_cast<const FT_Byte* >(bytes.data());
            FT_Face face;
            int error =  FT_New_Memory_Face(library,
                                            data,bytes.size(),-1,&face);
            if (error==0) {
                int faces_num = face->num_faces;
                FT_Done_Face(face);
                for (int face_n = 0;face_n<faces_num;face_n++) {
                    error =  FT_New_Memory_Face(library,
                                                data,bytes.size(),face_n,&face);
                    /// skip font if load error
                    if (error!=0) {
                         qDebug() << "failed read font " << file_name << " " << face_n << " " << get_error_descr(error);
                        continue;
                    }

                    QString family = face->family_name;
                    //qDebug() << "face " << family << " "
                    //        << face->style_name;
                    /// skip font if not have family
                    if (family.isEmpty()) continue;

                    bool fixedsizes = (FT_FACE_FLAG_SCALABLE & face->face_flags ) == 0;
                    m_database[face->family_name].push_back(
                            FontDef(face->style_name,
                                    file_name,
                                    face_n,
                                    fixedsizes));
                    if (fixedsizes) {
                        for (int i=0;i<face->num_fixed_sizes;i++) {
                            m_database[family].back().fixedsizes.push_back(
                                    QPair<int,int>(
                                            face->available_sizes[i].width,
                                            face->available_sizes[i].height));
                        }
                        qDebug() << " fixed sizes " << m_database[family].back().fixedsizes;

                    }

                    FT_Done_Face(face);

                }
            } else {
                qDebug() << "failed read font " << file_name << " " << get_error_descr(error);
            }

        }

        progress_val++;
        progress->setValue(progress_val);
    }
    FT_Done_FreeType(library);

    /// fill combo
    ui->comboBoxFamily->clear();
    foreach (QString str, m_database.keys()) {
        ui->comboBoxFamily->addItem(str);
    }
    ui->comboBoxFamily->setCurrentIndex(0);
}

void FontSelectFrame::on_pushButtonChangeDir_clicked()
{
    QString dir = QFileDialog::getExistingDirectory(
            this,tr("Select fonts directory"),
            ui->lineEditFontsDir->text());
    if (!dir.isEmpty()) {
        if (m_config) m_config->setPath(dir);
        setFontsDirectory(dir);
    }
}

void FontSelectFrame::selectFile(const QString& file,int face) {
    foreach (const QString& name, m_database.keys()) {
        int id = 0;
        const FontStyles &fs(m_database[name]);
        foreach (const FontDef &fd, fs) {
            if (fd.file == file &&
                fd.face == face) {
                bool b = ui->comboBoxStyle->blockSignals(true);
                bool block = ui->comboBoxSize->blockSignals(true);

                for (int i=0;i<ui->comboBoxFamily->count();i++)
                    if (ui->comboBoxFamily->itemText(i)==name) {
                        ui->comboBoxFamily->setCurrentIndex(i);
                        break;
                    }


                for (int i=0;i<ui->comboBoxStyle->count();i++)
                    if (ui->comboBoxStyle->itemData(i).toInt()==id) {
                        ui->comboBoxStyle->setCurrentIndex(i);
                        on_comboBoxStyle_currentIndexChanged(i);
                        break;
                    }
                ui->comboBoxSize->blockSignals(block);
                ui->comboBoxStyle->blockSignals(b);
            }
            id++;
        }
    }
}

void FontSelectFrame::selectSize(int size) {
    QString ss = QString().number(size);
    for (int i=0;i<ui->comboBoxSize->count();i++) {
        if (ss==ui->comboBoxSize->itemText(i)) {
            ui->comboBoxSize->setCurrentIndex(i);
            return;
        }
    }
    ui->comboBoxSize->setEditText(QString().number(size));
}

void FontSelectFrame::on_comboBoxFamily_currentIndexChanged(QString family)
{
    if (family.isEmpty()) return;
    if (m_config)
        m_config->setFamily(family);
    ui->comboBoxStyle->clear();
    int item_no = 0;
    foreach (const FontDef& def ,m_database[family]) {
        ui->comboBoxStyle->addItem(def.style,item_no);
        item_no++;
    }
    ui->comboBoxStyle->setEnabled(item_no>1);
}

void FontSelectFrame::on_comboBoxStyle_currentIndexChanged(int index )
{
    if (index<0)
        return;

    int item_no = ui->comboBoxStyle->itemData(index).toInt();
    QString family = ui->comboBoxFamily->currentText();

    if (item_no>=0 && item_no<m_database[family].size()) {
        ui->label_FileName->setText(
            QString(tr("File"))+" : " + m_database[family][item_no].file
            );
        if (m_config) {
            m_config->setFilename(m_database[family][item_no].file);
            m_config->setFaceIndex(m_database[family][item_no].face);
            m_config->setStyle(m_database[family][item_no].style);
        }
        readFontSizes(m_database[family][item_no]);
    }
}





void FontSelectFrame::readFontSizes(const FontDef& def) {
    int index = ui->comboBoxSize->currentIndex();
    bool block = ui->comboBoxSize->blockSignals(true);
    ui->comboBoxSize->clear();
    if (def.fixedsize) {
        typedef QPair<int,int> Pair;
        foreach (Pair size , def.fixedsizes) {
            ui->comboBoxSize->addItem(
                    QString().number(size.first)+"x"+
                    QString().number(size.second));
        }
        ui->comboBoxSize->setEnabled(def.fixedsizes.size()>1);
        ui->comboBoxSize->setEditable(false);
    } else {
        static const int sizes[] = {5,8,10,12,14,17,20,24,32,48,65};
        for (size_t i=0;i<sizeof(sizes)/sizeof(sizes[0]);i++)
            ui->comboBoxSize->addItem(QString().number(
                    sizes[i]));
        ui->comboBoxSize->setEditable(true);
    }
    if (index>=0 )
        ui->comboBoxSize->setCurrentIndex(index);
    ui->comboBoxSize->blockSignals(block);
    on_comboBoxSize_currentIndexChanged(ui->comboBoxSize->currentText());
}


void FontSelectFrame::on_comboBoxSize_editTextChanged(QString size_str)
{
    Q_UNUSED(size_str);
    /*
    bool ok = false;
    int size = size_str.toInt(&ok);
    if (!ok) {
        ui->comboBoxSize->setCurrentIndex(0);
        return;
    }
    if (m_config) {
        m_config->setSize(size);
    }*/
}

void FontSelectFrame::on_comboBoxSize_currentIndexChanged(QString size_str)
{
    bool ok = false;
    int size = size_str.toInt(&ok);
    if (!ok) {
        //ui->comboBoxSize->setCurrentIndex(0);
        return;
    }
    if (m_config) {
        m_config->setSize(size);
    }
}

void FontSelectFrame::on_pushButtonDefault_clicked()
{
    setFontsDirectory(FontConfig::defaultFontsPath());
}

void FontSelectFrame::on_pushButtonDefault_pressed()
{

}
