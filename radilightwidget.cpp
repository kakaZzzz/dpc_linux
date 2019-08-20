#include "radilightwidget.h"
#include "ui_radilightwidget.h"

#include <QDebug>
#include <QColorDialog>

RadiLightWidget::RadiLightWidget(QWidget *parent, DeviceComm *dev_comm, DeviceDB *dev_db) :
    QWidget(parent),
    ui(new Ui::RadiLightWidget)
{
    ui->setupUi(this);

    m_dev_comm = dev_comm;
    m_dev_db = dev_db;
    m_current_mode = 0;
    m_current_profile = 1; // default 1
    //  init control ui
    initUI();
}

RadiLightWidget::~RadiLightWidget()
{
    delete ui;
    delete m_keyboard_ctrl;
}

void RadiLightWidget::on_listWidget_light_clicked(const QModelIndex &index)
{
    int light_mode = getLightModeByIndex(index.row());

    m_dev_db->setSelectMode(m_current_profile, light_mode);
    setBackLightMode(light_mode);
}

void RadiLightWidget::on_horizontalSlider_brightness_valueChanged(int value)
{
    RadiData data;
    bool result = m_dev_db->queryRadiInfo(m_current_profile, m_current_mode, data);
    if (result == false)
        return;

    data.rgb_brightness = value;

    result = m_dev_db->modifyRadiRGBData(data);
    if (result)
    {
        uint8_t  kb_data[8] = {0};
        hid_getRadiData(data, kb_data);
        m_dev_comm->setDeviceData(kb_data, 8);
    }
}

void RadiLightWidget::on_horizontalSlider_speed_valueChanged(int value)
{
    RadiData data;
    bool result = m_dev_db->queryRadiInfo(m_current_profile, m_current_mode, data);
    if (result == false)
        return;

    data.rgb_speed = value;

    result = m_dev_db->modifyRadiRGBData(data);
    if (result)
    {
        uint8_t  kb_data[8] = {0};
        hid_getRadiData(data, kb_data);
        m_dev_comm->setDeviceData(kb_data, 8);
    }
}

void RadiLightWidget::on_button_custom_clicked()
{
    RadiData data;
    bool result = m_dev_db->queryRadiInfo(m_current_profile, m_current_mode, data);
    if (result == false)
        return;

    QColor color = QColorDialog::getColor(QColor(data.r_value, data.g_value, data.b_value, 255),
                                          this, "Color Select");

    data.r_value = color.red();
    data.g_value = color.green();
    data.b_value = color.blue();

    if (data.r_value == 0 && data.g_value==0 && data.b_value == 0)
        return ;

    result = m_dev_db->modifyRadiRGBData(data);
    if (result)
    {
        uint8_t  kb_data[8] = {0};
        hid_getRadiData(data, kb_data);
        m_dev_comm->setDeviceData(kb_data, 8);

        QString style_sheet;
        style_sheet.sprintf("QPushButton{background-color: rgba(%d, %d, %d, 255)}",
                            data.r_value, data.g_value, data.b_value);
        ui->button_custom->setStyleSheet(style_sheet);

        if (m_current_mode == 12)
        {
            m_keyboard_ctrl->setCheckKeyColor(color);

            QVector<KEY_INFO*> vecKeys = m_keyboard_ctrl->getKeyItems();

            int key_count = vecKeys.size();
            for (int i = 0; i < key_count; i++)
            {
                KEY_INFO* key_info = vecKeys.at(i);
                if (key_info == NULL)
                    continue;

                RGBData rgb_data;
                rgb_data.radi_id         = data.radi_id;
                rgb_data.key_value   = key_info->key_value;
                rgb_data.r_value        = key_info->key_color.red();
                rgb_data.g_value       = key_info->key_color.green();
                rgb_data.b_value       = key_info->key_color.blue();

                m_dev_db->addKeyRGBData(rgb_data);
            }

            QVector<RGBData*> vec_data;
            m_dev_db->queryKeysRGBData(data.radi_id, vec_data);
            uint8_t kb_data[408] = {0};
            hid_getKeyRGBData(vec_data, 1, kb_data);
            m_dev_comm->setDeviceDatas(kb_data, 408);

            int data_count = vec_data.size();
            for (int i = 0; i < data_count; i++)
            {
                RGBData* rgb_data = vec_data.at(i);
                if (rgb_data == NULL)
                    continue;

                delete rgb_data;
                rgb_data = NULL;
            }
            vec_data.clear();
        }
        else
        {
            m_keyboard_ctrl->setLightColor(color);
        }
    }
}

void RadiLightWidget::on_checkBox_custom_clicked()
{
    bool check = ui->checkBox_custom->checkState();

    RadiData data;
    bool result = m_dev_db->queryRadiInfo(m_current_profile, m_current_mode, data);
    if (result == false)
        return;

    data.rgb_mode = check == true ? 1 : 0;
    ui->button_custom->setEnabled(data.rgb_mode == 1 ? true : false);

    result = m_dev_db->modifyRadiRGBData(data);
    if (result)
    {
        uint8_t  kb_data[8] = {0};
        hid_getRadiData(data, kb_data);
        m_dev_comm->setDeviceData(kb_data, 8);
    }
}

void RadiLightWidget::on_checkBox_select_all_clicked()
{
    bool check = ui->checkBox_select_all->checkState();
    m_keyboard_ctrl->setAllKeyCheck(check);

     ui->checkBox_left_side_led->setChecked(check);
     ui->checkBox_right_side_led->setChecked(check);
     ui->checkBox_top_side_led->setChecked(check);
     ui->checkBox_bottom_side_led->setChecked(check);
     ui->checkBox_wasd->setChecked(check);
     ui->checkBox_arrows->setChecked(check);
     ui->checkBox_functions->setChecked(check);
     ui->checkBox_number->setChecked(check);

     m_keyboard_ctrl->update();
}

void RadiLightWidget::on_checkBox_top_side_led_clicked()
{
    bool check = ui->checkBox_top_side_led->checkState();
    m_keyboard_ctrl->setKeyCheck(601, check);
    m_keyboard_ctrl->update();
}

void RadiLightWidget::on_checkBox_left_side_led_clicked()
{
    bool check = ui->checkBox_left_side_led->checkState();
    m_keyboard_ctrl->setKeyCheck(600, check);
    m_keyboard_ctrl->update();
}

void RadiLightWidget::on_checkBox_right_side_led_clicked()
{
    bool check = ui->checkBox_right_side_led->checkState();
    m_keyboard_ctrl->setKeyCheck(602, check);
    m_keyboard_ctrl->update();
}

void RadiLightWidget::on_checkBox_bottom_side_led_clicked()
{
    bool check = ui->checkBox_bottom_side_led->checkState();
    m_keyboard_ctrl->setKeyCheck(603, check);
    m_keyboard_ctrl->update();
}

void RadiLightWidget::on_checkBox_wasd_clicked()
{
    bool check = ui->checkBox_wasd->checkState();
    m_keyboard_ctrl->setKeyCheck(0x1A, check);
    m_keyboard_ctrl->setKeyCheck(0x04, check);
    m_keyboard_ctrl->setKeyCheck(0x16, check);
    m_keyboard_ctrl->setKeyCheck(0x07, check);
    m_keyboard_ctrl->update();
}

void RadiLightWidget::on_checkBox_arrows_clicked()
{
    bool check = ui->checkBox_arrows->checkState();
    m_keyboard_ctrl->setKeyCheck(0x50, check);
    m_keyboard_ctrl->setKeyCheck(0x4F, check);
    m_keyboard_ctrl->setKeyCheck(0x52, check);
    m_keyboard_ctrl->setKeyCheck(0x51, check);
    m_keyboard_ctrl->update();
}

void RadiLightWidget::on_checkBox_number_clicked()
{
    bool check = ui->checkBox_number->checkState();

    for (int i = 0x1E; i <= 0x27; i++)
        m_keyboard_ctrl->setKeyCheck(i, check);

    m_keyboard_ctrl->update();
}

void RadiLightWidget::on_checkBox_functions_clicked()
{
    bool check = ui->checkBox_functions->checkState();
    for (int i = 0x3A; i <= 0x45; i++)
        m_keyboard_ctrl->setKeyCheck(i, check);

    m_keyboard_ctrl->update();
}

void RadiLightWidget::on_button_reset_all_leds_clicked()
{
    RadiData data;
    bool result = m_dev_db->queryRadiInfo(m_current_profile, m_current_mode, data);
    if (result == false)
        return;

    result = m_dev_db->deleteKeyRGBData(data.radi_id);
    if (result)
    {
        QVector<RGBData*> vec_data;
        m_dev_db->queryKeysRGBData(data.radi_id, vec_data);
        uint8_t kb_data[408] = {0};
        hid_getKeyRGBData(vec_data, 1, kb_data);
        m_dev_comm->setDeviceDatas(kb_data, 408);

        int data_count = vec_data.size();
        for (int i = 0; i < data_count; i++)
        {
            RGBData* rgb_data = vec_data.at(i);
            if (rgb_data == NULL)
                continue;

            delete rgb_data;
            rgb_data = NULL;
        }
        vec_data.clear();

        m_keyboard_ctrl->setAllKeysColor(QColor(0, 0,0,255));
    }
}

//  init control ui
void RadiLightWidget::initUI()
{
    //  load list data
    ui->listWidget_light->setViewMode(QListView::IconMode);
    ui->listWidget_light->setViewMode(QListView::ListMode);

    QListWidgetItem *item = new QListWidgetItem;
    item->setText("Static");
    item->setIcon(QIcon(":/image/icon/icon_light_static.png"));
    ui->listWidget_light->addItem(item);
    item = new QListWidgetItem;
    item->setText("Spectrum");
    item->setIcon(QIcon(":/image/icon/icon_light_spectrum.png"));
    ui->listWidget_light->addItem(item);
    item = new QListWidgetItem;
    item->setText("Rainbow");
    item->setIcon(QIcon(":/image/icon/icon_light_rainbow.png"));
    ui->listWidget_light->addItem(item);
    item = new QListWidgetItem;
    item->setText("Power Gauge");
    item->setIcon(QIcon(":/image/icon/icon_light_powergauge.png"));
    ui->listWidget_light->addItem(item);
    item = new QListWidgetItem;
    item->setText("Breathing");
    item->setIcon(QIcon(":/image/icon/icon_light_breathing.png"));
    ui->listWidget_light->addItem(item);
    item = new QListWidgetItem;
    item->setText("Twinkling Stars");
    item->setIcon(QIcon(":/image/icon/icon_light_twinklingstars.png"));
    ui->listWidget_light->addItem(item);
    item = new QListWidgetItem;
    item->setText("Reactive");
    item->setIcon(QIcon(":/image/icon/icon_light_reactive.png"));
    ui->listWidget_light->addItem(item);
    item = new QListWidgetItem;
    item->setText("Marquee");
    item->setIcon(QIcon(":/image/icon/icon_light_marquee.png"));
    ui->listWidget_light->addItem(item);
    item = new QListWidgetItem;
    item->setText("Aurora");
    item->setIcon(QIcon(":/image/icon/icon_light_aurora.png"));
    ui->listWidget_light->addItem(item);
    item = new QListWidgetItem;
    item->setText("Custom");
    item->setIcon(QIcon(":/image/icon/icon_light_custom.png"));
    ui->listWidget_light->addItem(item);

    // keyboard control
    m_keyboard_ctrl = new QKeyboardCtrl(this);
    m_keyboard_ctrl->setGeometry(340, 160, 698, 256);
    m_keyboard_ctrl->setKeyboardBkg(":/image/keyboard/img_keyboard_87.png");
    m_keyboard_ctrl->setKeyboardMode(KBM_LIGHT_NONE);
    m_keyboard_ctrl->show();;

    int select_mode = m_dev_db->getSelectMode(m_current_profile);
    ui->listWidget_light->setCurrentRow(getIndexByLightMode(select_mode));
    setBackLightMode(select_mode);
}

// get light mode by list index
int RadiLightWidget::getLightModeByIndex(int index)
{
    int light_mode = 1;
    switch (index) {
    case 0:         light_mode = 1;     break;  // Static
    case 1:         light_mode = 2;     break;  // Spectrum
    case 2:         light_mode = 3;     break;  // Rainbow
    case 3:         light_mode = 4;     break;  // Power Gauge
    case 4:         light_mode = 5;     break;  // Breathing
    case 5:         light_mode = 6;     break;  // Twinkling Stars
    case 6:         light_mode = 7;     break;  // Reactive
    case 7:         light_mode = 8;     break;  // Marquee
    case 8:         light_mode = 9;     break;  // Aurora
    case 9:         light_mode = 12;     break;  // Custom
    default:
        break;
    }
    return light_mode;
}

// get list index by light mode
int RadiLightWidget::getIndexByLightMode(int mode)
{
    int list_index = 1;
    switch (mode) {
    case 1:         list_index = 0;     break;  // Static
    case 2:         list_index = 1;     break;  // Spectrum
    case 3:         list_index = 2;     break;  // Rainbow
    case 4:         list_index = 3;     break;  // Power Gauge
    case 5:         list_index = 4;     break;  // Breathing
    case 6:         list_index = 5;     break;  // Twinkling Stars
    case 7:         list_index = 6;     break;  // Reactive
    case 8:         list_index = 7;     break;  // Marquee
    case 9:         list_index = 8;     break;  // Aurora
    case 12:         list_index = 9;     break;  // Custom
    default:
        break;
    }
    return list_index;
}

// set backlight mode
void RadiLightWidget::setBackLightMode(int light_mode)
{
    if (m_current_mode == light_mode)
        return ;

    RadiData data;
    bool result = m_dev_db->queryRadiInfo(m_current_profile, light_mode, data);
    if (result == false)
        return;

    if (light_mode == 12)
        m_keyboard_ctrl->setKeyboardMode(KBM_LIGHT_CUSTOM);
    else
        m_keyboard_ctrl->setKeyboardMode(KBM_LIGHT_STATIC);

    m_current_mode = light_mode;

    ui->frame_key_check->setVisible(false);

    uint8_t  kb_data[8] = {0};
    hid_getRadiData(data, kb_data);
    m_dev_comm->setDeviceData(kb_data, 8);

    if (light_mode == 1 || light_mode == 12)
    {
        ui->horizontalSlider_brightness->setValue(data.rgb_brightness);
        ui->horizontalSlider_speed->setValue(0);
        ui->horizontalSlider_speed->setEnabled(false);

        ui->button_custom->setVisible(true);
        ui->label_randomcolor->setVisible(true);
        ui->checkBox_custom->setVisible(true);

        QString style_sheet;
        style_sheet.sprintf("QPushButton{background-color: rgba(%d, %d, %d, 255)}",
                            data.r_value, data.g_value, data.b_value);
        ui->button_custom->setStyleSheet(style_sheet);

        ui->checkBox_custom->setChecked(data.rgb_mode == 1 ? true : false);

        if (light_mode == 12)
        {
            ui->frame_key_check->setVisible(true);
            ui->checkBox_custom->setVisible(false);
            ui->button_custom->setEnabled(true );

            QVector<RGBData*> vec_data;
            m_dev_db->queryKeysRGBData(data.radi_id, vec_data);
            uint8_t kb_data[408] = {0};
            hid_getKeyRGBData(vec_data, 1, kb_data);
            m_dev_comm->setDeviceDatas(kb_data, 408);

            int data_count = vec_data.size();
            for (int i = 0; i < data_count; i++)
            {
                RGBData* rgb_data = vec_data.at(i);
                if (rgb_data == NULL)
                    continue;

                QColor color(rgb_data->r_value, rgb_data->g_value, rgb_data->b_value, 255);
                m_keyboard_ctrl->setKeyColor(rgb_data->key_value, color);

                delete rgb_data;
                rgb_data = NULL;
            }
            vec_data.clear();
        }
        else
        {
            QColor color(data.r_value, data.g_value, data.b_value, 255);
            m_keyboard_ctrl->setLightColor(color);
            ui->button_custom->setEnabled(data.rgb_mode == 1 ? true : false);
        }
    }
    else if (light_mode == 2 || light_mode == 4 || light_mode == 8)
    {
        ui->horizontalSlider_brightness->setValue(data.rgb_brightness);
        ui->horizontalSlider_speed->setValue(data.rgb_speed);
        ui->horizontalSlider_speed->setEnabled(true);

        ui->button_custom->setVisible(false);
        ui->label_randomcolor->setVisible(false);
        ui->checkBox_custom->setVisible(false);

        QColor color(255, 225, 0, 255);
        m_keyboard_ctrl->setLightColor(color);
    }
    else if (light_mode == 3)
    {
        ui->horizontalSlider_brightness->setValue(data.rgb_brightness);
        ui->horizontalSlider_speed->setValue(data.rgb_speed);
        ui->horizontalSlider_speed->setEnabled(true);

        ui->button_custom->setVisible(false);
        ui->label_randomcolor->setVisible(false);
        ui->checkBox_custom->setVisible(false);

        QColor color(255, 225, 0, 255);
        m_keyboard_ctrl->setLightColor(color);
    }
    else if (light_mode == 5 || light_mode == 6 || light_mode == 7 || light_mode == 9)
    {
        ui->horizontalSlider_brightness->setValue(data.rgb_brightness);
        ui->horizontalSlider_speed->setValue(data.rgb_speed);
        ui->horizontalSlider_speed->setEnabled(true);

        ui->button_custom->setVisible(true);
        ui->label_randomcolor->setVisible(true);
        ui->checkBox_custom->setVisible(true);

        QString style_sheet;
        style_sheet.sprintf("QPushButton{background-color: rgba(%d, %d, %d, 255)}",
                            data.r_value, data.g_value, data.b_value);
        ui->button_custom->setStyleSheet(style_sheet);

        QColor color(data.r_value, data.g_value, data.b_value, 255);
        m_keyboard_ctrl->setLightColor(color);

        ui->checkBox_custom->setChecked(data.rgb_mode == 1 ? true : false);
        ui->button_custom->setEnabled(data.rgb_mode == 1 ? true : false);
    }
}
