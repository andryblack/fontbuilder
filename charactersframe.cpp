/**
 * Copyright (C) 2010-2010, by Andrey AndryBlack Kunitsyn
 * (support.andryblack@gmail.com)
 */

#include "charactersframe.h"
#include "ui_charactersframe.h"
#include <QFileDialog>
#include "fontconfig.h"

CharactersFrame::CharactersFrame(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::CharactersFrame)
{
    ui->setupUi(this);
    m_config = 0;
}

CharactersFrame::~CharactersFrame()
{
    delete ui;
}

void CharactersFrame::changeEvent(QEvent *e)
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

void CharactersFrame::on_pushButtonImport_clicked()
{
    QString file = QFileDialog::getOpenFileName(this,tr("Select file"),
                                                QString(),
                                                tr("Text file(*.txt)"));
    if (!file.isEmpty()) {
        QFile f(file);
        if (f.open(QFile::ReadOnly | QFile::Text)) {
            QByteArray data = f.readAll();
            QString text = QString::fromUtf8(data.constData(),data.size());
            ui->plainTextEdit->setPlainText(text);
        }
    }
}

void CharactersFrame::on_pushButtonExport_clicked()
{
    QString file = QFileDialog::getSaveFileName(this,tr("Select file"),
                                                QString(),
                                                tr("Text file(*.txt)"));
    if (!file.isEmpty()) {
        QFile f(file);
        if (f.open(QFile::WriteOnly | QFile::Text)) {
            QByteArray data =
                ui->plainTextEdit->document()->toPlainText().toUtf8();
            f.write(data);
        }
    }
}


QString CharactersFrame::getCharacters() const {
    return ui->plainTextEdit->document()->toPlainText();
}

void CharactersFrame::on_plainTextEdit_textChanged()
{
    if (m_config) {
        m_config->setCharacters(getCharacters());
    }
}

void CharactersFrame::setConfig(FontConfig* config) {
    m_config = config;
    ui->plainTextEdit->setPlainText(config->characters());
}
