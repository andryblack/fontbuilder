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

#ifndef ABSTRACTIMAGEWRITER_H
#define ABSTRACTIMAGEWRITER_H




#include <QObject>
#include <QFile>
#include <QVector>
#include <QImage>
#include "rendererdata.h"

class LayoutData;
class LayoutConfig;

class QFileSystemWatcher;
class QTimer;

class AbstractImageWriter : public QObject
{
Q_OBJECT
public:
    explicit AbstractImageWriter(QObject *parent );

    const QString& errorString() const { return m_error_string;}
    const QString& extension() const { return m_extension;}

    bool Write(QFile& file);
    QImage* Read(QFile& file);

    void setData(const LayoutData* data,const LayoutConfig* config,const RendererData& rendered);

    void forget();
    void watch(const QString& file);
signals:
    void imageChanged(const QString& file);
private:
    QString m_error_string;
    QString m_extension;
    int m_tex_width;
    int m_tex_height;
    const RendererData* m_rendered;
    const LayoutData* m_layout;
    const LayoutConfig* m_layout_config;
    QFileSystemWatcher* m_watcher;
    bool m_reload_support;
    QTimer* m_reload_timer;
    QString m_reload_file;
protected:
    void setExtension(const QString& extension) { m_extension = extension;}
    void setReloadSupport(bool support) { m_reload_support = support;}
    void setErrorMessage(const QString& str) { m_error_string=str; }
    int texWidth() const { return m_tex_width;}
    int texHeight() const { return m_tex_height;}
    const RendererData* rendered() const { return m_rendered;}
    const LayoutData* layout() const { return m_layout;}
    const LayoutConfig* layoutConfig() const { return m_layout_config;}
    virtual bool Export(QFile& file) = 0;
    virtual QImage* reload( QFile& file) { Q_UNUSED(file);return 0;}
    QImage buildImage();
protected slots:
    void onFileChanged(const QString& fn);
    void onReload();
private:
};


#endif // ABSTRACTIMAGEWRITER_H
