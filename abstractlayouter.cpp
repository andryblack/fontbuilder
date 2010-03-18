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
        m_data->beginPlacing();
        on_LayoutDataChanged();
        m_data->endPlacing();
    }
}

void AbstractLayouter::on_LayoutDataChanged() {
    if (m_data!=0 && m_config!=0 ) {
        QVector<LayoutChar> chars = m_chars;
        {
            for( int i=0;i<m_chars.size();i++) {
                if (m_config->onePixelOffset()) {
                    chars[i].w++;
                    chars[i].h++;
                }
                chars[i].w+=m_config->offsetLeft()+m_config->offsetRight();
                chars[i].h+=m_config->offsetTop()+m_config->offsetBottom();
            }
        }
        m_data->beginPlacing();
        PlaceImages(chars);
        m_data->endPlacing();
    }
}

static const int nextpot(unsigned int val) {
    val--;
    val = (val >> 1) | val;
    val = (val >> 2) | val;
    val = (val >> 4) | val;
    val = (val >> 8) | val;
    val = (val >> 16) | val;
    val++;
    return val;
}

void AbstractLayouter::resize(int w,int h) {
    if (m_config) {
        if (m_config->onePixelOffset())
        {
            w+=2;
            h+=2;
        }
        if (m_config->potImage()) {
            w = nextpot(w);
            h = nextpot(h);
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
