#ifndef KEYSETWIDGET_H
#define KEYSETWIDGET_H

#include <QWidget>
#include "qkeyboardctrl.h"

namespace Ui {
class KeySetwidget;
}

class KeySetwidget : public QWidget
{
    Q_OBJECT

public:
    explicit KeySetwidget(QWidget *parent = 0);
    ~KeySetwidget();

protected:

     //  init control ui
    void initUI();
    // load config data
    void loadConfigData();
    // set keyboard report rate
    void setReportRate(int value, bool update_db = true);
    // set sleep time
    void setKeyboardSleepTime(bool wireless_mode = true);

    QKeyboardCtrl*          m_keyboard_ctrl;

private slots:
    void on_radioButton_125_clicked();

    void on_radioButton_250_clicked();

    void on_radioButton_500_clicked();

    void on_radioButton_1000_clicked();

    void on_checkBox_usb_mode_clicked();

    void on_spinBox_usb_mode_valueChanged(int arg1);

    void on_checkBox_backlight_clicked();

    void on_spinBox_backlight_valueChanged(int arg1);

    void on_checkBox_wireless_clicked();

    void on_spinBox_bluetooth_valueChanged(int arg1);

    void on_reset_keyboard_clicked();
private:
    Ui::KeySetwidget *ui;
};

#endif // KEYSETWIDGET_H
