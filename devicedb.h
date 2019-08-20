#ifndef DEVICEDB_H
#define DEVICEDB_H

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QVariant>
#include "keyboarddata.h"

// KEY DEFINE
enum KEY_DEFINE
{
    KEY_REALVALUE = 0,
    KEY_DISABLE,
    KEY_REDEFINEVALUE,
    KEY_MACRO,
    KEY_MOUSE,
    KEY_MULTIMEDIA,
    KEY_LINUX,
};
enum KEY_MOUSE_DEFINE
{
    KEY_MOUSE_LEFT = 1,
    KEY_MOUSE_MIDDLE,
    KEY_MOUSE_RIGHT,
    KEY_MOUSE_DBLEFT,
    KEY_MOUSE_SCROLLUP,
    KEY_MOUSE_SCROLLDOWN,
    KEY_MOUSE_BUTTON4,
    KEY_MOUSE_BUTTON5,
};
enum KEY_MULTIMEDIA_DEFINE
{
    KEY_MEDIA_PLAYPAUSE = 1,
    KEY_MEDIA_STOP,
    KEY_MEDIA_PREVIOUS,
    KEY_MEDIA_NEXT,
    KEY_MEDIA_VOL_UP,
    KEY_MEDIA_VOL_DOWN,
    KEY_MEDIA_VOL_SILENT,
};
enum KEY_LINUX_DEFINE
{
    KEY_LINUX_TERMINAL = 1,
    KEY_LINUX_COPY,
    KEY_LINUX_PASTE,
    KEY_LINUX_CUT,
};

class DeviceDB
{
public:
    DeviceDB();
    ~DeviceDB();

public:

    // open
    bool openDB();
    // create table
    void createTable();
    // close
    void closeDB();

    // read config data
    bool readConfigData(int profile, QString key, QString& value);
    // update config data
    bool updateConfigData(int profile, QString key, QString value);

    // write radi data(if profile not exisit)
    void writeRadiData(int profile);
    // modify rgb param
    bool modifyRadiRGBData(RadiData &data);
    // set select mode with current profile
    bool setSelectMode(int profile, int mode);
    // get  select mode with current profile
    int getSelectMode(int profile);
    // query select light data info with profile
    bool querySelectRadiInfo(int profile, RadiData &data);
    // query  light data info with profile and mode
    bool queryRadiInfo(int profile, int mode, RadiData &data);
    // query  light data infos with profile
    int queryRadiInfos(int profile, QVector<RadiData*> &vecdata);

    //  add key rgb color
    bool addKeyRGBData(RGBData data);
    // query key rgb color
    bool queryKeysRGBData(int radi_id, QVector<RGBData*> &vecdata);
    // delete key rgb with radi-mode
    bool deleteKeyRGBData(int radi_id);

    // add key data
    bool addKeyProfile(KeyData &data);
    // query key data ( keyonly == true,  only return keyvalue)
    int queryKeyProfileInfo(int profile, QVector<KeyData*> &vecdata, bool keyvalue_only = true);
    // query key data  (key info)
    bool queryKeyProfileInfo(int profile, int key_value, KeyData &data);

private:
    QSqlDatabase        m_db;

    // init database
    void initDatabase();
};

#endif // DEVICEDB_H
