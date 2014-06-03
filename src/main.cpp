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

#include <Qt>
#if (QT_VERSION >= QT_VERSION_CHECK(5, 0, 0))
#include <QApplication>
#include <QCommandLineParser>
#else
#include <QtGui/QApplication>
#endif
#include <QCoreApplication>
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QSettings>
#include <QObject>
#include <QDebug>
#include "fontbuilder.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QCoreApplication::setOrganizationName("AndryBlack");
    QCoreApplication::setOrganizationDomain("andryblack.com");
    QCoreApplication::setApplicationName("FontBuilder");
    QCoreApplication::setApplicationVersion("0.7");

    QCommandLineParser parser;
    parser.setApplicationDescription("Test");
    parser.addHelpOption();
    parser.addVersionOption();
    parser.addPositionalArgument("config", QCoreApplication::translate("main","config file"));
    parser.process(a);

    const QStringList args = parser.positionalArguments();

    FontBuilder w;

    if (args.count() > 0)
    {
        QString configFile = args.at(0);
        QFile file(configFile);
        file.open(QIODevice::ReadOnly | QIODevice::Text);
        QByteArray rawData =  file.readAll();

        QJsonDocument document(QJsonDocument::fromJson(rawData));
        QJsonObject config = document.object();
        file.close();

        QSettings settings;
        for(QJsonObject::const_iterator iter=config.begin(); iter!= config.end(); iter++)
        {
            settings.beginGroup(iter.key());

            QJsonObject node = iter.value().toObject();
            for(QJsonObject::const_iterator niter= node.begin(); niter!=node.end(); niter++)
            {
                settings.setValue(niter.key(),niter.value().toVariant());
            }

            settings.endGroup();
        }
        w.reloadConfig(settings);
        return 0;
    }else
    {
        w.show();
    }

    return a.exec();
}
