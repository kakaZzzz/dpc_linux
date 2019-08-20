#ifndef CUSTOMKNOBWIDGET_H
#define CUSTOMKNOBWIDGET_H

#include <QWidget>
#include <QLabel>

#include "custombutton.h"

namespace Ui {
class CustomKnobWidget;
}

class CustomKnobWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CustomKnobWidget(QWidget *parent = 0);
    ~CustomKnobWidget();

protected:

     //  init control ui
    void initUI();

    tabButton*                       m_knob_single;
    tabButton*                       m_knob_double;
    tabButton*                       m_knob_forward;
    tabButton*                       m_knob_backward;

    QLabel*                            m_label_knob;

private slots:
    void slot_click_knob_single();
    void slot_click_knob_double();
    void slot_click_knob_forward();
    void slot_click_knob_backward();

private:
    Ui::CustomKnobWidget *ui;
};

#endif // CUSTOMKNOBWIDGET_H
