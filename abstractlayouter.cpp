#include "abstractlayouter.h"
#include "layoutdata.h"
#include "layoutconfig.h"

AbstractLayouter::AbstractLayouter(QObject *parent) :
    QObject(parent)
{
    m_config = 0;
    m_data = 0;
}


void AbstractLayouter::setConfig(const LayoutConfig* config) {
    m_config = config;
    connect(m_config,SIGNAL(layoutConfigChanged()),this,SLOT(on_LayoutDataChanged()));
}

void AbstractLayouter::setData(LayoutData* data) {
    m_data = data;
}

void AbstractLayouter::on_ReplaceImages(const QVector<LayoutChar>& chars) {
    m_chars = chars;

    if (m_data!=0 && m_config!=0 ) {
        if (m_config->onePixelOffset()) {
            for( int i=0;i<m_chars.size();i++) {
                m_chars[i].w++;
                m_chars[i].h++;
            }
        }
        m_data->beginPlacing();
        PlaceImages();
        m_data->endPlacing();
    }
}

void AbstractLayouter::on_LayoutDataChanged() {
    if (m_data!=0 && m_config!=0 ) {
        m_data->beginPlacing();
        PlaceImages();
        m_data->endPlacing();
    }
}


void AbstractLayouter::resize(int w,int h) {
    if (m_config) {
        if (m_config->onePixelOffset())
        {
            w+=2;
            h+=2;
        }
    }
    if (m_data) {
        m_data->resize(w,h);
    }
}

int AbstractLayouter::width() const {
    int w = 0;
    if (m_data) {
        w = m_data->width();
    }
    if (m_config) {
        if (m_config->onePixelOffset())
            w-=2;
    }
    return w;
}
int AbstractLayouter::height() const {
    int h= 0;
    if (m_data) {
        h = m_data->width();
    }
    if (m_config) {
        if (m_config->onePixelOffset())
            h-=2;
    }
    return h;
}
void AbstractLayouter::place(const LayoutChar& c) {
    LayoutChar out = c;
    if (m_config) {
        if (m_config->onePixelOffset()) {
            out.x++;
            out.y++;
        }
    }
    if (m_data)
        m_data->placeChar(out);
}
