#ifndef CHARMAPDIALOG_H
#define CHARMAPDIALOG_H

#include <QDialog>
#include <QSet>

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
};

#endif // CHARMAPDIALOG_H
