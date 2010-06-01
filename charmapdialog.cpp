#include "charmapdialog.h"
#include "ui_charmapdialog.h"

CharMapDialog::CharMapDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CharMapDialog)
{
    ui->setupUi(this);
    ui->widget->setCodes(&m_codes);
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
