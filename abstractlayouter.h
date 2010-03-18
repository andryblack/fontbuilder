#ifndef ABSTRACTLAYOUTER_H
#define ABSTRACTLAYOUTER_H

#include <QObject>
#include <QVector>
#include "layoutchar.h"

class LayoutConfig;
class LayoutData;



class AbstractLayouter : public QObject
{
Q_OBJECT
public:
    explicit AbstractLayouter(QObject *parent );
    void setConfig(const LayoutConfig*);
    void setData(LayoutData* data);
private:
    const LayoutConfig*   m_config;
    LayoutData* m_data;
    QVector<LayoutChar>    m_chars;
protected:
    void resize(int w,int h);
    int width() const;
    int height() const;
    void place(const LayoutChar&);
    virtual void PlaceImages(const QVector<LayoutChar>& chars) = 0;
protected slots:
    void on_LayoutDataChanged();
signals:

public slots:
    void on_ReplaceImages(const QVector<LayoutChar>& chars);
};

#endif // ABSTRACTLAYOUTER_H
