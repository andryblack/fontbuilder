#include "charsselectwidget.h"

#include <QPaintEvent>
#include <QPainter>

static const int cell_size = 24;
static const int columns = 32;

CharsSelectWidget::CharsSelectWidget(QWidget *parent) :
    QWidget(parent) , m_codes_begin(0x0000),m_codes_end(0xFFFF)
{
    m_codes = 0;
    m_track_mouse = false;
    m_track_erase = false;
}


QSize CharsSelectWidget::sizeHint() const {
    return QSize(columns*cell_size, ((m_codes_end-m_codes_begin)/columns)*cell_size);
}


void CharsSelectWidget::setRange(uint begin,uint end) {
    m_codes_begin = begin;
    m_codes_end = end;
    adjustSize();
    update();
}

void CharsSelectWidget::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.fillRect(event->rect(),QBrush(Qt::white));
    Q_ASSERT(m_codes!=0);
    QRect redrawRect = event->rect();
    int beginRow = redrawRect.top()/cell_size;
    int endRow = redrawRect.bottom()/cell_size;
    int beginColumn = redrawRect.left()/cell_size;
    int endColumn = redrawRect.right()/cell_size;

    painter.setPen(QPen(Qt::gray));
    for (int row = beginRow; row <= endRow; ++row) {
        for (int column = beginColumn; (column <= endColumn ) && (column < columns); ++column) {
            uint key =  m_codes_begin+row*columns + column;
            if ( key <= m_codes_end) {
                if (m_codes->contains(key))
                    painter.fillRect(column*cell_size, row*cell_size, cell_size, cell_size,QBrush(Qt::lightGray));
                painter.drawRect(column*cell_size, row*cell_size, cell_size, cell_size);
            }
        }
    }

    QFontMetrics fontMetrics(painter.font());
     painter.setPen(QPen(Qt::black));
     for (int row = beginRow; row <= endRow; ++row) {

         for (int column = beginColumn; (column <= endColumn ) && (column < columns); ++column) {

             uint key = m_codes_begin+row*columns + column;
             if (key<=m_codes_end) {
                 painter.setClipRect(column*cell_size, row*cell_size, cell_size, cell_size);

                 painter.drawText(column*cell_size + (cell_size / 2) - fontMetrics.width(QChar(key))/2,
                                  row*cell_size + 4 + fontMetrics.ascent(),
                                  QString(QChar(key)));
             }
         }
     }
}


void CharsSelectWidget::mousePressEvent(QMouseEvent *event)
{
     if (event->button() == Qt::LeftButton) {
         m_select_last_code = m_select_begin_code = (event->y()/cell_size)*columns + event->x()/cell_size;
         if (QChar(m_select_begin_code).category() != QChar::NoCategory) {
             m_track_mouse = true;
             if (m_codes->contains(m_select_begin_code)) {
                 m_codes->erase(m_codes->find(m_select_begin_code));
                 m_track_erase = true;
             } else {
                 m_codes->insert(m_select_begin_code);
                 m_track_erase = false;
             }
         } else {
             m_track_mouse = false;
         }
         update();
     }
     else
         QWidget::mousePressEvent(event);
}


void CharsSelectWidget::mouseReleaseEvent(QMouseEvent *event) {
     if (event->button() == Qt::LeftButton)
        m_track_mouse = false;
     else
        QWidget::mouseReleaseEvent(event);
}

void CharsSelectWidget::mouseMoveEvent(QMouseEvent *event) {
    if (m_track_mouse) {
        uint code = (event->y()/cell_size)*columns + event->x()/cell_size;
        if (code!=m_select_last_code) {
            if (code!=m_select_begin_code) {
                uint from = qMin(m_select_begin_code,code);
                uint to = qMax(m_select_begin_code,code);
                for (uint c = from;c<=to;c++) {
                    if (m_track_erase) {
                        QSet<uint>::Iterator i=m_codes->find(c);
                        if ( i!=m_codes->end())
                            m_codes->erase(i);
                    } else {
                        m_codes->insert(c);
                    }
                }
            }
            m_select_last_code = code;
            update();
        }
    }
}
