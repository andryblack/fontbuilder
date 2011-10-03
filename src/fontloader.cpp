#include "fontloader.h"

#include <QFile>
#include <QDomDocument>
#include <QDebug>

FontLoader::FontLoader(QObject *parent) :
    QObject(parent)
{
}


bool FontLoader::Load(QString filename) {

    QDomDocument doc;
    QFile f;
    f.setFileName(filename);
    QString error;
    if (!f.open(QFile::ReadOnly | QFile::Text)) {
        qDebug() << "Error opening font fike " << filename;
        return false;
    }
    if (!doc.setContent(&f,&error)) {
        qDebug() << "Error loading font " << filename << " " << error;
        return false;
    }

    QDomElement root = doc.firstChildElement("font");
    if (root.isNull()) return false;

    QDomElement chars = doc.firstChildElement("chars");

    return false;
}
