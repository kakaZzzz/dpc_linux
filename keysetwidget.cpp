#include "keysetwidget.h"
#include "ui_keysetwidget.h"

#include "mainwindow.h"
#include "devicecomm.h"
#include "devicedb.h"

KeySetwidget::KeySetwidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::KeySetwidget)
{
    ui->setupUi(this);

    //  init control ui
    initUI();
}

KeySetwidget::~KeySetwidget()
{
    delete ui;
    delete m_keyboard_ctrl;
}

void KeySetwidget::on_radioButton_125_clicked()
{
    setReportRate(8);
}

void KeySetwidget::on_radioButton_250_clicked()
{
    setReportRate(4);
}

void KeySetwidget::on_radioButton_500_clicked()
{
    setReportRate(2);
}

void KeySetwidget::on_radioButton_1000_clicked()
{
    setReportRate(1);
}

void KeySetwidget::on_checkBox_usb_mode_clicked()
{
    DeviceDB*  dev_db = ((MainWindow*)this->parent())->m_dev_db;
    int current_profile = ((MainWindow*)this->parent())->m_current_profile;

    bool check = ui->checkBox_usb_mode->checkState();

    if (check)
    {
        ui->spinBox_usb_mode->setValue(300);
        dev_db->updateConfigData(current_profile, "delay_usbwiresleep", "300");
    }
    else
    {
        ui->spinBox_usb_mode->setValue(0);
        dev_db->updateConfigData(current_profile, "delay_usbwiresleep", "0");
    }

    setKeyboardSleepTime(false);
}

void KeySetwidget::on_spinBox_usb_mode_valueChanged(int arg1)
{
    DeviceDB*  dev_db = ((MainWindow*)this->parent())->m_dev_db;
    int current_profile = ((MainWindow*)this->parent())->m_current_profile;

    if (arg1 == 0)
    {
        dev_db->updateConfigData(current_profile, "delay_usbwiresleep", "0");
        ui->checkBox_usb_mode->setChecked(false);
    }
    else
    {
        QString value = QString::number(arg1);
        dev_db->updateConfigData(current_profile, "delay_usbwiresleep", value);
        ui->checkBox_usb_mode->setChecked(true);
    }

    setKeyboardSleepTime(false);
}

void KeySetwidget::on_checkBox_backlight_clicked()
{
    DeviceDB*  dev_db = ((MainWindow*)this->parent())->m_dev_db;
    int current_profile = ((MainWindow*)this->parent())->m_current_profile;

    bool check = ui->checkBox_backlight->checkState();

    if (check)
    {
        ui->spinBox_backlight->setValue(120);
        dev_db->updateConfigData(current_profile, "delay_closelight", "120");
    }
    else
    {
        ui->spinBox_backlight->setValue(0);
        dev_db->updateConfigData(current_profile, "delay_closelight", "0");
    }

    setKeyboardSleepTime(true);
}

void KeySetwidget::on_spinBox_backlight_valueChanged(int arg1)
{
    DeviceDB*  dev_db = ((MainWindow*)this->parent())->m_dev_db;
    int current_profile = ((MainWindow*)this->parent())->m_current_profile;

    if (arg1 == 0)
    {
        dev_db->updateConfigData(current_profile, "delay_closelight", "0");
        ui->checkBox_backlight->setChecked(false);
    }
    else
    {
        QString value = QString::number(arg1);
        dev_db->updateConfigData(current_profile, "delay_closelight", value);
        ui->checkBox_backlight->setChecked(true);
    }

    setKeyboardSleepTime(true);
}

void KeySetwidget::on_checkBox_wireless_clicked()
{
    DeviceDB*  dev_db = ((MainWindow*)this->parent())->m_dev_db;
    int current_profile = ((MainWindow*)this->parent())->m_current_profile;

    bool check = ui->checkBox_wireless->checkState();

    if (check)
    {
        ui->spinBox_bluetooth->setValue(180);
        dev_db->updateConfigData(current_profile, "delay_wirelesssleep", "180");
    }
    else
    {
        ui->spinBox_bluetooth->setValue(0);
        dev_db->updateConfigData(current_profile, "delay_wirelesssleep", "0");
    }

    setKeyboardSleepTime(true);
}

void KeySetwidget::on_spinBox_bluetooth_valueChanged(int arg1)
{
    DeviceDB*  dev_db = ((MainWindow*)this->parent())->m_dev_db;
    int current_profile = ((MainWindow*)this->parent())->m_current_profile;

    if (arg1 == 0)
    {
        dev_db->updateConfigData(current_profile, "delay_wirelesssleep", "0");
        ui->checkBox_wireless->setChecked(false);
    }
    else
    {
        QString value = QString::number(arg1);
        dev_db->updateConfigData(current_profile, "delay_wirelesssleep", value);
        ui->checkBox_wireless->setChecked(true);
    }

    setKeyboardSleepTime(true);
}

void KeySetwidget::on_reset_keyboard_clicked()
{
    DeviceComm*  dev_comm = ((MainWindow*)this->parent())->m_device_comm;

    uint8_t kb_data[8] = {0};
    hid_getResetKeyboard(kb_data);
    dev_comm->setDeviceData(kb_data, 8);
}

//  init control ui
void KeySetwidget::initUI()
{
    m_keyboard_ctrl = new QKeyboardCtrl(this);
    m_keyboard_ctrl->setGeometry(340, 160, 698, 256);
    m_keyboard_ctrl->setKeyboardBkg(":/image/keyboard/img_keyboard_87.png");
    m_keyboard_ctrl->setKeyboardMode(KBM_LIGHT_NONE);
    m_keyboard_ctrl->show();

    // load config data
    loadConfigData();
}

// load config data
void KeySetwidget::loadConfigData()
{
    DeviceDB*  dev_db = ((MainWindow*)this->parent())->m_dev_db;
    int current_profile = ((MainWindow*)this->parent())->m_current_profile;

    QString  value;
    dev_db->readConfigData(current_profile, "report_rate", value);
    if (value == "1")
        ui->radioButton_1000->setChecked(true);
    else if (value == "2")
        ui->radioButton_500->setChecked(true);
    else if (value == "4")
        ui->radioButton_250->setChecked(true);
    else if (value == "8")
        ui->radioButton_125->setChecked(true);

    // set report rate
    setReportRate(value.toInt(), false);

    dev_db->readConfigData(current_profile, "delay_usbwiresleep", value);
    if (value == "0")
        ui->checkBox_usb_mode->setChecked(false);
    else
        ui->checkBox_usb_mode->setChecked(true);
    ui->spinBox_usb_mode->setValue(value.toInt());

    dev_db->readConfigData(current_profile, "delay_closelight", value);
    if (value == "0")
        ui->checkBox_backlight->setChecked(false);
    else
        ui->checkBox_backlight->setChecked(true);
    ui->spinBox_backlight->setValue(value.toInt());

    dev_db->readConfigData(current_profile, "delay_wirelesssleep", value);
    if (value == "0")
        ui->checkBox_wireless->setChecked(false);
    else
        ui->checkBox_wireless->setChecked(true);
    ui->spinBox_bluetooth->setValue(value.toInt());

    // usb-mode
    setKeyboardSleepTime(false);
    // wireless-mode
    setKeyboardSleepTime(true);
}

// set keyboard report rate
void KeySetwidget::setReportRate(int value, bool update_db)
{
    if (update_db)
    {
        DeviceDB*  dev_db = ((MainWindow*)this->parent())->m_dev_db;
        int current_profile = ((MainWindow*)this->parent())->m_current_profile;

        QString value_ = QString::number(value);
        dev_db->updateConfigData(current_profile, "report_rate", value_);
    }
    DeviceComm*  dev_comm = ((MainWindow*)this->parent())->m_device_comm;

    uint8_t kb_data[8] = {0};
    hid_getKeyboardReportRate(value, kb_data);
    dev_comm->setDeviceData(kb_data, 8);
}

// set sleep time
void KeySetwidget::setKeyboardSleepTime(bool wireless_mode)
{
    DeviceComm*  dev_comm = ((MainWindow*)this->parent())->m_device_comm;

    if (wireless_mode)
    {
        int backlight_time = ui->spinBox_usb_mode->value();
        int wireless_time = ui->spinBox_bluetooth->value();

        uint8_t kb_data[8] = {0};
        hid_getWirelessModeSleepTime(backlight_time, wireless_time, kb_data);
        dev_comm->setDeviceData(kb_data, 8);
    }
    else
    {
        int time = ui->spinBox_usb_mode->value();

        uint8_t kb_data[8] = {0};
        hid_getUSBModeSleepTime(time, kb_data);
        dev_comm->setDeviceData(kb_data, 8);
    }
}

