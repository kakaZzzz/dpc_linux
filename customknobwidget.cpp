#include "customknobwidget.h"
#include "ui_customknobwidget.h"

CustomKnobWidget::CustomKnobWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CustomKnobWidget)
{
    ui->setupUi(this);
    //  init control ui
    initUI();
}

CustomKnobWidget::~CustomKnobWidget()
{
    delete ui;
    delete m_knob_single;
    delete m_knob_double;
    delete m_knob_forward;
    delete m_knob_backward;
    delete m_label_knob;
}

void CustomKnobWidget::slot_click_knob_single()
{

}

void CustomKnobWidget::slot_click_knob_double()
{

}

void CustomKnobWidget::slot_click_knob_forward()
{

}

void CustomKnobWidget::slot_click_knob_backward()
{

}

//  init control ui
void CustomKnobWidget::initUI()
{

    int xpos = 310 + (1135 - 310 -170 * 4 ) / 2;
    int ypos = 160;
    m_knob_single = new tabButton(":/image/button/img_knobbutton.png", this, "Single-Click");
    m_knob_single->setGeometry(xpos, ypos, 166, 50);
    m_knob_single->show();
    m_knob_double = new tabButton(":/image/button/img_knobbutton.png", this, "Double-Click");
    m_knob_double->setGeometry(xpos + 170, ypos, 166, 50);
    m_knob_double->show();
    m_knob_forward = new tabButton(":/image/button/img_knobbutton.png", this, "Forward");
    m_knob_forward->setGeometry(xpos + 170 * 2, ypos, 166, 50);
    m_knob_forward->setText("Forward");
    m_knob_forward->show();
    m_knob_backward = new tabButton(":/image/button/img_knobbutton.png", this, "Backward");
    m_knob_backward->setGeometry(xpos + 170 * 3, ypos, 166, 50);
    m_knob_backward->show();

    xpos = 310 + (1135 - 310) / 2 - 317;
    m_label_knob = new QLabel(this);
    m_label_knob->setStyleSheet("border-image:url(:/image/icon/icon_knob.png)");
    m_label_knob->setGeometry(xpos, ypos + 60, 634, 216);
    m_label_knob->show();

    connect(m_knob_single, SIGNAL(clicked()), this, SLOT(slot_click_knob_single()));
    connect(m_knob_double, SIGNAL(clicked()), this, SLOT(slot_click_knob_double()));
    connect(m_knob_forward, SIGNAL(clicked()), this, SLOT(slot_click_knob_forward()));
    connect(m_knob_backward, SIGNAL(clicked()), this, SLOT(slot_click_knob_backward()));
}
