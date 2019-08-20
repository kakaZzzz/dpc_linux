#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>

#include "custombutton.h"
#include "customkeywidget.h"
#include "customknobwidget.h"
#include "radilightwidget.h"
#include "keysetwidget.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    int                                        m_current_profile; // default 1
    DeviceComm*                  m_device_comm;
    DeviceDB*                         m_dev_db;
protected:

    //   init ui control
    void  initUI();

    //  set tab status
    void setTabStatus(int tab);

    tabButton*                       m_tab_customkey;
    tabButton*                       m_tab_customknob;
    tabButton*                       m_tab_light;
    tabButton*                       m_tab_config;
    int                                       m_current_tab;

    QLabel*                             m_label_area;

    CustomKeyWidget*         m_customkey_widget;    // key macro window
    CustomKnobWidget*      m_customknob_widget; // knob macro window
    RadiLightWidget*            m_radilight_widget; // light config
    KeySetwidget*                  m_keyset_widget; // keyboard config
private slots:
    void slot_click_customkey();
    void slot_click_customknob();
    void slot_click_light();
    void slot_click_config();

private:
    Ui::MainWindow *ui;

};

#endif // MAINWINDOW_H
