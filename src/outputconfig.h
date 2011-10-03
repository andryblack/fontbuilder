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

#ifndef OUTPUTCONFIG_H
#define OUTPUTCONFIG_H

#include <QObject>
#include <QImage>

class OutputConfig : public QObject
{
Q_OBJECT
public:
    explicit OutputConfig(QObject *parent = 0);

    const QString& path() const { return m_path;}
    void setPath(const QString& path) { m_path=path;}
    Q_PROPERTY(QString path READ path WRITE setPath);

    const QString& imageName() const { return m_image_name;}
    void setImageName(const QString& name);
    Q_PROPERTY(QString imageName READ imageName WRITE setImageName);

    const QString& imageFormat() const { return m_image_format;}
    void setImageFormat(const QString& format) { m_image_format=format;}
    Q_PROPERTY(QString imageFormat READ imageFormat WRITE setImageFormat);

    const QString& descriptionName() const { return m_description_name;}
    void setDescriptionName(const QString& name);
    Q_PROPERTY(QString descriptionName READ descriptionName WRITE setDescriptionName);

    const QString& descriptionFormat() const { return m_description_format;}
    void setDescriptionFormat(const QString& format) { m_description_format=format;}
    Q_PROPERTY(QString descriptionFormat READ descriptionFormat WRITE setDescriptionFormat);

    bool writeImage() const { return m_write_image;}
    void setWriteImage(bool write) { m_write_image = write;}
    Q_PROPERTY(bool writeImage READ writeImage WRITE setWriteImage );

    bool writeDescription() const { return m_write_description;}
    void setWriteDescription(bool write) { m_write_description = write;}
    Q_PROPERTY(bool writeDescription READ writeDescription WRITE setWriteDescription );
private:
    QString m_path;
    bool    m_write_image;
    QString m_image_name;
    QString m_image_format;
    bool    m_write_description;
    QString m_description_name;
    QString m_description_format;
signals:
    void imageNameChanged(const QString&);
    void descriptionNameChanged(const QString&);
public slots:

};

#endif // OUTPUTCONFIG_H
