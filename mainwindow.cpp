#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //   init ui control
    initUI();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete m_customkey_widget;
    delete m_customknob_widget;
    delete m_radilight_widget;
    delete m_keyset_widget;

    delete m_tab_customkey;
    delete m_tab_customknob;
    delete m_tab_light;
    delete m_tab_config;
    delete m_label_area;

    delete m_device_comm;
    delete m_dev_db;
}

//   init ui control
void  MainWindow::initUI()
{
    m_current_profile = 1;

    MainWindow::m_device_comm = new DeviceComm();
    QString device_name = MainWindow::m_device_comm->enumerateDevice();
    setWindowTitle(device_name);

    MainWindow::m_dev_db = new DeviceDB();
    MainWindow::m_dev_db->writeRadiData(1);

    m_current_tab = 1;
    // control
    m_tab_customkey = new tabButton(":/image/button/icon_menu_customkey.png", this);
    m_tab_customkey->setGeometry(1, 20, 44, 44);
    m_tab_customkey->setTabCheck(true);
    m_tab_customkey->show();
    m_tab_customknob = new tabButton(":/image/button/icon_menu_knob.png", this);
    m_tab_customknob->setGeometry(1, 20 + 44, 44, 44);
    m_tab_customknob->show();
    m_tab_light = new tabButton(":/image/button/icon_menu_radi.png", this);
    m_tab_light->setGeometry(1, 20 + 44 * 2, 44, 44);
    m_tab_light->show();
    m_tab_config = new tabButton(":/image/button/icon_menu_set.png", this);
    m_tab_config->setGeometry(1, 20 + 44 * 3, 44, 44);
    m_tab_config->show();

    m_label_area = new QLabel(this);
    m_label_area->setStyleSheet("border-image:url(:/image/img_area_opera.png)");
    m_label_area->setGeometry(45, 0, 307, 700);
    m_label_area->show();

    connect(m_tab_customkey, SIGNAL(clicked()), this, SLOT(slot_click_customkey()));
    connect(m_tab_customknob, SIGNAL(clicked()), this, SLOT(slot_click_customknob()));
    connect(m_tab_light, SIGNAL(clicked()), this, SLOT(slot_click_light()));
    connect(m_tab_config, SIGNAL(clicked()), this, SLOT(slot_click_config()));

    // child window
    m_customkey_widget = new CustomKeyWidget(this);
    m_customkey_widget->move(45, 20);
    m_customkey_widget->show();

    m_customknob_widget = new CustomKnobWidget(this);
    m_customknob_widget->move(45, 20);
    m_customknob_widget->hide();

    m_radilight_widget = new RadiLightWidget(this, m_device_comm, m_dev_db);
    m_radilight_widget->move(45, 20);
    m_radilight_widget->hide();

    m_keyset_widget = new KeySetwidget(this);
    m_keyset_widget->move(45, 20);
    m_keyset_widget->hide();
}

//  set tab status
void MainWindow::setTabStatus(int tab)
{
    if (m_current_tab == 1)
    {
        m_tab_customkey->setTabCheck(false);
        m_customkey_widget->hide();
    }
    else if (m_current_tab == 2)
    {
        m_tab_customknob->setTabCheck(false);
        m_customknob_widget->hide();
    }
    else if (m_current_tab == 3)
    {
        m_tab_light->setTabCheck(false);
        m_radilight_widget->hide();
    }
    else if (m_current_tab == 4)
    {
        m_tab_config->setTabCheck(false);
        m_keyset_widget->hide();
    }
    if (tab == 1)
    {
        m_tab_customkey->setTabCheck(true);
        m_customkey_widget->show();;
    }
    else if (tab == 2)
    {
        m_tab_customknob->setTabCheck(true);
        m_customknob_widget->show();
    }
    else if (tab == 3)
    {
        m_tab_light->setTabCheck(true);
        m_radilight_widget->show();
    }
    else if (tab == 4)
    {
        m_tab_config->setTabCheck(true);
        m_keyset_widget->show();
    }
    m_current_tab = tab;
}

void MainWindow::slot_click_customkey()
{
    //  set tab status
    setTabStatus(1);
}

void MainWindow::slot_click_customknob()
{
    //  set tab status
    setTabStatus(2);
}

void MainWindow::slot_click_light()
{
    //  set tab status
    setTabStatus(3);
}

void MainWindow::slot_click_config()
{
    //  set tab status
    setTabStatus(4);
}
