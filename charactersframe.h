/**
 * Copyright (C) 2010-2010, by Andrey AndryBlack Kunitsyn
 * (support.andryblack@gmail.com)
 */

#ifndef CHARACTERSFRAME_H
#define CHARACTERSFRAME_H

#include <QFrame>

namespace Ui {
    class CharactersFrame;
}

class FontConfig;

class CharactersFrame : public QFrame {
    Q_OBJECT
public:
    CharactersFrame(QWidget *parent = 0);
    ~CharactersFrame();

    void setConfig(FontConfig* config);
protected:
    void changeEvent(QEvent *e);
    QString getCharacters() const;
private:
    Ui::CharactersFrame *ui;
    FontConfig* m_config;
signals:

private slots:
    void on_plainTextEdit_textChanged();
    void on_pushButtonExport_clicked();
    void on_pushButtonImport_clicked();
};

#endif // CHARACTERSFRAME_H
