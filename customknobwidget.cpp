#include "customknobwidget.h"
#include "ui_customknobwidget.h"

#include <QDebug>
#include <QMessageBox>

#include "mainwindow.h"
#include "devicecomm.h"
#include "devicedb.h"
#include "qtkeyboardkey.h"

CustomKnobWidget::CustomKnobWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CustomKnobWidget)
{
    ui->setupUi(this);

    m_cur_key_value = 0;
    m_macro_type = 0;
    m_macro_value = 0;
    m_macro_desc = "";

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

    clearTreeList();
}

void CustomKnobWidget::slot_click_knob_single()
{
    m_cur_key_value = 500;
    // get knob macro
    getMacrodata();
}

void CustomKnobWidget::slot_click_knob_double()
{
    m_cur_key_value = 501;
    // get knob macro
    getMacrodata();
}

void CustomKnobWidget::slot_click_knob_forward()
{
    m_cur_key_value = 502;
    // get knob macro
    getMacrodata();
}

void CustomKnobWidget::slot_click_knob_backward()
{
    m_cur_key_value = 503;
    // get knob macro
    getMacrodata();
}

void CustomKnobWidget::on_treeWidget_knob_itemPressed(QTreeWidgetItem *item, int column)
{
    m_macro_desc = item->text(column);
    int level = item->data(0, 5).toInt();
    if (level == 0) // parent
    {
        m_macro_type = item->data(0, 6).toInt();
        m_macro_value = 0;

        if (m_macro_type == KEY_REDEFINEVALUE)
            ui->frame_key->show();
        else
            ui->frame_key->hide();
    }
    else if (level == 1) // child
    {
        QTreeWidgetItem* parent_item = item->parent();
        if (parent_item)
        {
            m_macro_type = parent_item->data(0, 6).toInt();
            m_macro_value = item->data(0, 6).toInt();
        }
    }
}

void CustomKnobWidget::on_pushButton_save_clicked()
{
    if (m_cur_key_value <= 0)
    {
        QMessageBox::warning(this, "Key Assignment", "Select keyboard button");
        return;
    }

    DeviceDB*  dev_db = ((MainWindow*)this->parent())->m_dev_db;
    int current_profile = ((MainWindow*)this->parent())->m_current_profile;

    KeyData data = {0};
    data.profile = current_profile;
    data.key_value = m_cur_key_value;
    data.macro_type = m_macro_type;
    data.macro_name = m_macro_desc;

    if (m_macro_type == KEY_REALVALUE)
        data.macro_value = 0;
    else if (m_macro_type == KEY_DISABLE)
        data.macro_value = 1;
    else if (m_macro_type == KEY_REDEFINEVALUE)
    {
       int key_index  = ui->comboBox_newkey->currentIndex();
       data.macro_value = ui->comboBox_newkey->itemData(key_index).toInt();
       QString key_name = ui->comboBox_newkey->itemText(key_index);

       int syskey1_index  = ui->comboBox_syskey1->currentIndex();
       data.macro_value1 = ui->comboBox_syskey1->itemData(syskey1_index).toInt();
       QString syskey1_name = ui->comboBox_syskey1->itemText(syskey1_index);

       int syskey2_index  = ui->comboBox_syskey2->currentIndex();
       data.macro_value2 = ui->comboBox_syskey2->itemData(syskey2_index).toInt();
       QString syskey2_name = ui->comboBox_syskey2->itemText(syskey2_index);

       if (key_index == 0)
           return;

       if (syskey1_index != 0 &&  syskey1_index != 0)
           data.macro_name = syskey1_name + "+" + syskey2_name + "+" + key_name;
       else if (syskey1_index == 0 && syskey2_index == 0)
           data.macro_name = key_name;
       else if (syskey1_index != 0 && syskey2_index == 0)
           data.macro_name = syskey1_name + "+" + "+" + key_name;
    }
    else if (m_macro_type == KEY_MOUSE)
    {
        if (m_macro_value == KEY_MOUSE_LEFT)
            data.macro_value = 0xA5;
        else if (m_macro_value == KEY_MOUSE_MIDDLE)
            data.macro_value = 0xA7;
        else if (m_macro_value == KEY_MOUSE_RIGHT)
            data.macro_value = 0xA6;
        else if (m_macro_value == KEY_MOUSE_SCROLLUP)
            data.macro_value = 0xA8;
        else if (m_macro_value == KEY_MOUSE_SCROLLDOWN)
            data.macro_value = 0xA8;
        else if (m_macro_value == KEY_MOUSE_BUTTON4)
            data.macro_value = 0xA9;
        else if (m_macro_value == KEY_MOUSE_BUTTON5)
            data.macro_value = 0xAA;
    }
    else if (m_macro_type == KEY_MULTIMEDIA)
    {
        if (m_macro_value == KEY_MEDIA_PLAYPAUSE)
            data.macro_value = 0xF2;
        else if (m_macro_value == KEY_MEDIA_STOP)
            data.macro_value = 0xF4;
        else if (m_macro_value == KEY_MEDIA_PREVIOUS)
            data.macro_value = 0xF1;
        else if (m_macro_value == KEY_MEDIA_NEXT)
            data.macro_value = 0xF3;
        else if (m_macro_value == KEY_MEDIA_VOL_SILENT)
            data.macro_value = 0xEA;
        else if (m_macro_value == KEY_MEDIA_VOL_UP)
            data.macro_value = 0xE8;
        else if (m_macro_value == KEY_MEDIA_VOL_DOWN)
            data.macro_value = 0xE9;
    }
    else if (m_macro_type == KEY_LINUX)
    {
        if (m_macro_value == KEY_LINUX_TERMINAL)
        {
            data.macro_value1 = 0xE0;
            data.macro_value2 = 0xE2;
            data.macro_value = 0x17;
        }
        else if (m_macro_value == KEY_LINUX_COPY)
        {
            data.macro_value1 = 0xE0;
            data.macro_value = 0x06;
        }
        else if (m_macro_value == KEY_LINUX_PASTE)
        {
            data.macro_value1 = 0xE0;
            data.macro_value = 0x19;
        }
        else if (m_macro_value == KEY_LINUX_CUT)
        {
            data.macro_value1 = 0xE0;
            data.macro_value = 0x1B;
        }
    }

    bool result = dev_db->addKeyProfile(data);
    if (result)
    {
         // show effect in keyboard control
        bool check = true;
        if (data.macro_type == KEY_REALVALUE)
            check = false;

        if (m_cur_key_value == 500)
            m_knob_single->setTabCheck(check);
        else if (m_cur_key_value == 501)
            m_knob_double->setTabCheck(check);
        else if (m_cur_key_value == 502)
            m_knob_forward->setTabCheck(check);
        else if (m_cur_key_value == 503)
            m_knob_backward->setTabCheck(check);

        DeviceComm*  dev_comm = ((MainWindow*)this->parent())->m_device_comm;
        int kb_layout = dev_comm->getKeyboardLayout();
        // write data to keyboard
        uint8_t kb_data[256] = {0}; //  data length is 256
        if (data.macro_type == KEY_REALVALUE)
        {
            hid_keyDefaultValue(m_cur_key_value, kb_layout, kb_data);
        }
        else if (data.macro_type == KEY_DISABLE)
        {
            hid_disablekeyValue(m_cur_key_value, kb_layout, kb_data);
        }
        else if (data.macro_type == KEY_REDEFINEVALUE)
        {
             hid_combokeyData(m_cur_key_value, data.macro_value1, data.macro_value2, data.macro_value, kb_layout, kb_data);
        }
        else if (data.macro_type == KEY_MOUSE)
        {
            hid_combokeyData(m_cur_key_value, 0, 0, data.macro_value, kb_layout, kb_data);
             //hid_keyRemapData(m_cur_key_value, data.macro_value, kb_layout, kb_data);
        }
        else if (data.macro_type == KEY_MULTIMEDIA)
        {
            hid_keyRemapData(m_cur_key_value, data.macro_value, kb_layout, kb_data);
        }
        else if (data.macro_type == KEY_LINUX)
        {
            hid_combokeyData(m_cur_key_value, data.macro_value1, data.macro_value2, data.macro_value, kb_layout, kb_data);
        }
        dev_comm->setDeviceDatas(kb_data, 256);
    }
    else
    {
        if (m_cur_key_value == 500)
            m_knob_single->setTabCheck(false);
        else if (m_cur_key_value == 501)
            m_knob_double->setTabCheck(false);
        else if (m_cur_key_value == 502)
            m_knob_forward->setTabCheck(false);
        else if (m_cur_key_value == 503)
            m_knob_backward->setTabCheck(false);
    }
}

void CustomKnobWidget::on_pushButton_cancel_clicked()
{
    if (m_cur_key_value <= 0)
    {
        QMessageBox::warning(this, "Key Assignment", "Select keyboard button");
        return;
    }

    DeviceDB*  dev_db = ((MainWindow*)this->parent())->m_dev_db;
    int current_profile = ((MainWindow*)this->parent())->m_current_profile;

    KeyData data = {0};
    data.profile = current_profile;
    data.key_value = m_cur_key_value;
    data.macro_type = KEY_REALVALUE;

    bool result = dev_db->addKeyProfile(data);
    if (result)
    {
        DeviceComm*  dev_comm = ((MainWindow*)this->parent())->m_device_comm;
        int kb_layout = dev_comm->getKeyboardLayout();
        // write data to keyboard
        uint8_t kb_data[256] = {0}; //  data length is 256
        if (data.macro_type == KEY_REALVALUE)
        {
            hid_keyDefaultValue(m_cur_key_value, kb_layout, kb_data);
        }

        dev_comm->setDeviceDatas(kb_data, 256);
    }

    if (m_cur_key_value == 500)
        m_knob_single->setTabCheck(false);
    else if (m_cur_key_value == 501)
        m_knob_double->setTabCheck(false);
    else if (m_cur_key_value == 502)
        m_knob_forward->setTabCheck(false);
    else if (m_cur_key_value == 503)
        m_knob_backward->setTabCheck(false);
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

    QTreeWidgetItem *item = new QTreeWidgetItem;
    item->setText(0, "Default");
    item->setIcon(0, QIcon(":/image/icon/icon_custom_default.png"));
    item->setData(0, 5, 0);
    item->setData(0, 6, KEY_REALVALUE);
    ui->treeWidget_knob->addTopLevelItem(item);
    item = new QTreeWidgetItem;
    item->setText(0, "Disable");
    item->setIcon(0, QIcon(":/image/icon/icon_custom_disable.png"));
    item->setData(0, 5, 0);
    item->setData(0, 6, KEY_DISABLE);
    ui->treeWidget_knob->addTopLevelItem(item);
    item = new QTreeWidgetItem;
    item->setText(0, "Keyboard function");
    item->setIcon(0, QIcon(":/image/icon/icon_custom_keyboard.png"));
    item->setData(0, 5, 0);
    item->setData(0, 6, KEY_REDEFINEVALUE);
    ui->treeWidget_knob->addTopLevelItem(item);

    item = new QTreeWidgetItem;
    item->setText(0, "Mouse function");
    item->setIcon(0, QIcon(":/image/icon/icon_custom_mouse.png"));
    item->setData(0, 5, 0);
    item->setData(0, 6, KEY_MOUSE);
    ui->treeWidget_knob->addTopLevelItem(item);

    QTreeWidgetItem *child_item = new QTreeWidgetItem;
    child_item->setText(0, "Left Click");
    child_item->setData(0, 5, 1);
    child_item->setData(0, 6, KEY_MOUSE_LEFT);
    item->addChild(child_item);
    child_item = new QTreeWidgetItem;
    child_item->setText(0, "Middle Click");
    child_item->setData(0, 5, 1);
    child_item->setData(0, 6, KEY_MOUSE_MIDDLE);
    item->addChild(child_item);
    child_item = new QTreeWidgetItem;
    child_item->setText(0, "Right Click");
    child_item->setData(0, 5, 1);
    child_item->setData(0, 6, KEY_MOUSE_RIGHT);
    item->addChild(child_item);
    //child_item = new QTreeWidgetItem;
    //child_item->setText(0, "Double Click");
    //child_item->setData(0, 5, 1);
    //child_item->setData(0, 6, KEY_MOUSE_DBLEFT);
    //item->addChild(child_item);
    child_item = new QTreeWidgetItem;
    child_item->setText(0, "Scroll Up");
    child_item->setData(0, 5, 1);
    child_item->setData(0, 6, KEY_MOUSE_SCROLLUP);
    item->addChild(child_item);
    child_item = new QTreeWidgetItem;
    child_item->setText(0, "Scroll Down");
    child_item->setData(0, 5, 1);
    child_item->setData(0, 6, KEY_MOUSE_SCROLLDOWN);
    item->addChild(child_item);
    child_item = new QTreeWidgetItem;
    child_item->setText(0, "Mouse Button 4");
    child_item->setData(0, 5, 1);
    child_item->setData(0, 6, KEY_MOUSE_BUTTON4);
    item->addChild(child_item);
    child_item = new QTreeWidgetItem;
    child_item->setText(0, "Mouse Button 5");
    child_item->setData(0, 5, 1);
    child_item->setData(0, 6, KEY_MOUSE_BUTTON5);
    item->addChild(child_item);

    item = new QTreeWidgetItem;
    item->setText(0, "Multi-media");
    item->setIcon(0, QIcon(":/image/icon/icon_custom_multimedia.png"));
    item->setData(0, 5, 0);
    item->setData(0, 6, KEY_MULTIMEDIA);
    ui->treeWidget_knob->addTopLevelItem(item);
    child_item = new QTreeWidgetItem;
    child_item->setText(0, "Play/Pause");
    child_item->setData(0, 5, 1);
    child_item->setData(0, 6, KEY_MEDIA_PLAYPAUSE);
    item->addChild(child_item);
    child_item = new QTreeWidgetItem;
    child_item->setText(0, "Stop");
    child_item->setData(0, 5, 1);
    child_item->setData(0, 6, KEY_MEDIA_STOP);
    item->addChild(child_item);
    child_item = new QTreeWidgetItem;
    child_item->setText(0, "Prev");
    child_item->setData(0, 5, 1);
    child_item->setData(0, 6, KEY_MEDIA_PREVIOUS);
    item->addChild(child_item);
    child_item = new QTreeWidgetItem;
    child_item->setText(0, "Next");
    child_item->setData(0, 5, 1);
    child_item->setData(0, 6, KEY_MEDIA_NEXT);
    item->addChild(child_item);
    child_item = new QTreeWidgetItem;
    child_item->setText(0, "Volume +");
    child_item->setData(0, 5, 1);
    child_item->setData(0, 6, KEY_MEDIA_VOL_UP);
    item->addChild(child_item);
    child_item = new QTreeWidgetItem;
    child_item->setText(0, "Volume -");
    child_item->setData(0, 5, 1);
    child_item->setData(0, 6, KEY_MEDIA_VOL_UP);
    item->addChild(child_item);
    child_item = new QTreeWidgetItem;
    child_item->setText(0, "Mute");
    child_item->setData(0, 5, 1);
    child_item->setData(0, 6, KEY_MEDIA_VOL_SILENT);
    item->addChild(child_item);
    item = new QTreeWidgetItem;
    item->setText(0, "Linux shortcuts");
    item->setIcon(0, QIcon(":/image/icon/icon_custom_linux.png"));
    item->setData(0, 5, 0);
    item->setData(0, 6, KEY_LINUX);
    ui->treeWidget_knob->addTopLevelItem(item);
    child_item = new QTreeWidgetItem;
    child_item->setText(0, "Terminal");
    child_item->setData(0, 5, 1);
    child_item->setData(0, 6, KEY_LINUX_TERMINAL);
    item->addChild(child_item);
    child_item = new QTreeWidgetItem;
    child_item->setText(0, "Copy");
    child_item->setData(0, 5, 1);
    child_item->setData(0, 6, KEY_LINUX_COPY);
    item->addChild(child_item);
    child_item = new QTreeWidgetItem;
    child_item->setText(0, "Paste");
    child_item->setData(0, 5, 1);
    child_item->setData(0, 6, KEY_LINUX_PASTE);
    item->addChild(child_item);
    child_item = new QTreeWidgetItem;
    child_item->setText(0, "Cut");
    child_item->setData(0, 5, 1);
    child_item->setData(0, 6, KEY_LINUX_CUT);
    item->addChild(child_item);
    ui->frame_key->hide();

    // combox
   QVector<KeyInfo> vecdata;
   QtKeyBoardKey::getSysKeyList(vecdata);
   for (int i = 0; i < vecdata.size(); i++)
   {
       KeyInfo  key_info = vecdata.at(i);
       ui->comboBox_syskey1->addItem(key_info.ket_text, key_info.key_value);
       ui->comboBox_syskey2->addItem(key_info.ket_text, key_info.key_value);
   }
   vecdata.clear();
   QtKeyBoardKey::getAllKeyList(vecdata);
   for (int i = 0; i < vecdata.size(); i++)
   {
       KeyInfo  key_info = vecdata.at(i);
       ui->comboBox_newkey->addItem(key_info.ket_text, key_info.key_value);
   }

    connect(m_knob_single, SIGNAL(clicked()), this, SLOT(slot_click_knob_single()));
    connect(m_knob_double, SIGNAL(clicked()), this, SLOT(slot_click_knob_double()));
    connect(m_knob_forward, SIGNAL(clicked()), this, SLOT(slot_click_knob_forward()));
    connect(m_knob_backward, SIGNAL(clicked()), this, SLOT(slot_click_knob_backward()));

    //  load db data
    loadDBdata();
}

//  load db data
void CustomKnobWidget::loadDBdata()
{
    DeviceDB*  dev_db = ((MainWindow*)this->parent())->m_dev_db;
    int current_profile = ((MainWindow*)this->parent())->m_current_profile;

    QVector<KeyData*> vecData;
    dev_db->queryKeyProfileInfo(current_profile, vecData);
    int count = vecData.size();
    for (int i = 0; i < count; i++)
    {
        KeyData* data = vecData.at(i);
        if (data == NULL)
            continue;

        if (data->key_value == 500)
            m_knob_single->setTabCheck(true);
        else if (data->key_value == 501)
            m_knob_double->setTabCheck(true);
        else if (data->key_value == 502)
            m_knob_forward->setTabCheck(true);
        else if (data->key_value == 503)
            m_knob_backward->setTabCheck(true);
    }
}

// update macro data
void CustomKnobWidget::updataMacroData()
{

}

// get knob macro
void CustomKnobWidget::getMacrodata()
{
    ui->label_key_function->setText("Keyboard");

    QString key_name;
    if (m_cur_key_value == 500)
        key_name = "Single-Click";
    else if (m_cur_key_value == 501)
        key_name = "Double-Click";
    else if (m_cur_key_value == 502)
        key_name = "Forward";
    else if (m_cur_key_value == 503)
        key_name = "Backward";

    ui->label_key_name->setText(key_name);
    ui->label_key_macro->setText(key_name);


    DeviceDB*  dev_db = ((MainWindow*)this->parent())->m_dev_db;
    int current_profile = ((MainWindow*)this->parent())->m_current_profile;

    KeyData data;
    bool result = dev_db->queryKeyProfileInfo(current_profile, m_cur_key_value,  data);
    if (result)
    {
        if (data.macro_type == KEY_REALVALUE)
        {
            ui->label_key_function->setText("Keyboard");
            ui->label_key_macro->setText(key_name);
        }
        else if  (data.macro_type == KEY_DISABLE)
        {
            ui->label_key_function->setText("Disable");
            ui->label_key_macro->setText("Disable");
        }
        else if  (data.macro_type == KEY_REDEFINEVALUE)
        {
            ui->label_key_function->setText("Keyboard function");
            ui->label_key_macro->setText(data.macro_name);
        }
        else if  (data.macro_type == KEY_MACRO)
        {
            ui->label_key_function->setText("Macro");
            ui->label_key_macro->setText(data.macro_name);
        }
        else if  (data.macro_type == KEY_MOUSE)
        {
            ui->label_key_function->setText("Mouse function");
            ui->label_key_macro->setText(data.macro_name);
        }
        else if  (data.macro_type == KEY_MULTIMEDIA)
        {
            ui->label_key_function->setText("Multi-media");
            ui->label_key_macro->setText(data.macro_name);
        }
        else if  (data.macro_type == KEY_LINUX)
        {
            ui->label_key_function->setText("Linux shortcuts");
            ui->label_key_macro->setText(data.macro_name);
        }
    }
}

void CustomKnobWidget::clearTreeList()
{
    int data_count = m_vec_tree.size();
    for (int i = 0; i < data_count; i++)
    {
        QTreeWidgetItem* item = m_vec_tree.at(i);
        if (item)
        {
            delete item;
            item = NULL;
        }
    }
    m_vec_tree.clear();
}
