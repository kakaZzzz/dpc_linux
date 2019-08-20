#ifndef RADILIGHTWIDGET_H
#define RADILIGHTWIDGET_H

#include <QWidget>
#include <QListWidgetItem>
#include "qkeyboardctrl.h"
#include "devicecomm.h"
#include "devicedb.h"

namespace Ui {
class RadiLightWidget;
}

class RadiLightWidget : public QWidget
{
    Q_OBJECT

public:
    explicit RadiLightWidget(QWidget *parent = 0, DeviceComm *dev_comm = NULL, DeviceDB *dev_db = NULL);
    ~RadiLightWidget();

protected:

     //  init control ui
    void initUI();

    QKeyboardCtrl*          m_keyboard_ctrl;
    DeviceComm*             m_dev_comm;
    DeviceDB*                    m_dev_db;

    int                                  m_current_mode;
    int                                  m_current_profile;

private slots:
    void on_listWidget_light_clicked(const QModelIndex &index);

    void on_horizontalSlider_brightness_valueChanged(int value);

    void on_horizontalSlider_speed_valueChanged(int value);

    void on_button_custom_clicked();

    void on_checkBox_custom_clicked();

    void on_checkBox_select_all_clicked();

    void on_checkBox_top_side_led_clicked();

    void on_checkBox_left_side_led_clicked();

    void on_checkBox_right_side_led_clicked();

    void on_checkBox_bottom_side_led_clicked();

    void on_checkBox_wasd_clicked();

    void on_checkBox_arrows_clicked();

    void on_checkBox_number_clicked();

    void on_checkBox_functions_clicked();

    void on_button_reset_all_leds_clicked();

private:
    Ui::RadiLightWidget *ui;

    // get light mode by list index
    int getLightModeByIndex(int index);
    // get list index by light mode
    int getIndexByLightMode(int mode);
    // set backlight mode
    void setBackLightMode(int light_mode);
};

#endif // RADILIGHTWIDGET_H
