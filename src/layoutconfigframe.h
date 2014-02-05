#ifndef LAYOUTCONFIGFRAME_H
#define LAYOUTCONFIGFRAME_H

#include <QFrame>

namespace Ui {
    class LayoutConfigFrame;
}

class LayoutConfig;

class LayoutConfigFrame : public QFrame {
    Q_OBJECT
public:
    LayoutConfigFrame(QWidget *parent = 0);
    ~LayoutConfigFrame();

    void setConfig(LayoutConfig* config);
protected:
    void changeEvent(QEvent *e);

private:
    Ui::LayoutConfigFrame *ui;
    LayoutConfig*   m_config;

private slots:
    void on_spinBoxRightOffset_valueChanged(int );
    void on_spinBoxBottomOffset_valueChanged(int );
    void on_spinBoxLeftOffset_valueChanged(int );
    void on_spinBoxTopOffset_valueChanged(int );
    void on_checkBoxPOT_toggled(bool checked);
    void on_spinBoxSizeIncrement_valueChanged(int );
    void on_checkBoxOnePixelOffset_toggled(bool checked);
};

#endif // LAYOUTCONFIGFRAME_H
