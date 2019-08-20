#include "customkeydlg.h"
#include "ui_customkeydlg.h"

CustomKeyDlg::CustomKeyDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CustomKeyDlg)
{
    ui->setupUi(this);

    // init ui
   // initUI();
}

CustomKeyDlg::~CustomKeyDlg()
{
    delete ui;
    //delete m_keyboard_ctrl;
}

// init ui
//void CustomKeyDlg::initUI()
//{
    // create keyboard control
   // m_keyboard_ctrl = new QKeyboardCtrl(this);
   // m_keyboard_ctrl->setGeometry(100, 100, 698, 25.);
    //m_keyboard_ctrl->setKeyboardBkg();
    //m_keyboard_ctrl->setKeyboardMode(KBM_CUSTOMKEY);
    //m_keyboard_ctrl->show();
//}
