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
