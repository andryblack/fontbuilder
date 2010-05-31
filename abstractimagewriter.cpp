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

#include "abstractimagewriter.h"
#include "layoutdata.h"
#include "layoutconfig.h"

#include <QPainter>
#include <QFileSystemWatcher>
#include <QTimer>
#include <QDebug>


AbstractImageWriter::AbstractImageWriter(QObject *parent ) : QObject(parent),m_watcher(0) {
    setExtension("img");
    setReloadSupport(false);
    m_reload_timer = 0;
}


void AbstractImageWriter::setData(const LayoutData* data,const LayoutConfig* config,const RendererData& rendered) {
    m_layout = data;
    m_layout_config = config;
    m_rendered = &rendered;
    m_tex_width = data->width();
    m_tex_height = data->height();
}

QImage AbstractImageWriter::buildImage() {
    QImage pixmap(layout()->width(),layout()->height(),QImage::Format_ARGB32);

    pixmap.fill(0);

    QPainter painter(&pixmap);
    foreach (const LayoutChar& c,layout()->placed())
        if (rendered()->chars.contains(c.symbol)) {
            const RenderedChar& rend = rendered()->chars[c.symbol];
            painter.drawImage(c.x + layoutConfig()->offsetLeft(),
                              c.y + layoutConfig()->offsetTop(),rend.img);
        }
    return pixmap;
}

bool AbstractImageWriter::Write(QFile& file) {
    if (Export(file)) {
       return true;
    }
    return false;
}

QImage* AbstractImageWriter::Read(QFile& file) {
    return reload(file);
}

void AbstractImageWriter::watch(const QString& file) {
    delete m_watcher;
    m_watcher = 0;
    if (m_reload_support) {
        m_watcher = new QFileSystemWatcher(this);
        m_watcher->addPath(file);
        connect(m_watcher,SIGNAL(fileChanged(QString)),this,SLOT(onFileChanged(QString)));
    }
}

void AbstractImageWriter::onFileChanged(const QString& fn) {
    m_reload_file = fn;
    if (m_reload_timer) {
        m_reload_timer->stop();
    } else {
        m_reload_timer = new QTimer(this);
        connect(m_reload_timer,SIGNAL(timeout()),this,SLOT(onReload()));
    }
    m_reload_timer->setSingleShot(true);
    m_reload_timer->setInterval(2000);
    m_reload_timer->start();

}

void AbstractImageWriter::onReload() {
    imageChanged(m_reload_file);
}

void AbstractImageWriter::forget() {
    if (m_watcher) {
        delete m_watcher;
        m_watcher = 0;
    }
    if (m_reload_timer) {
        delete m_reload_timer;
        m_reload_timer = 0;
    }
}
