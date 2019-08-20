#include "devicedb.h"
#include <QDir>
#include <QDebug>
#include <QFileInfo>

DeviceDB::DeviceDB()
{
    QSqlDatabase data_base;
    if (QSqlDatabase::contains("qt_sql_default_connection"))
    {
        data_base = QSqlDatabase::database("qt_sql_default_connection");
    }
    else
    {
        m_db = QSqlDatabase::addDatabase("QSQLITE");

        QString db_name = QDir::currentPath() + QString("/") + QString("device.db");

        QFileInfo file_info(db_name);
        bool file_exist = file_info.isFile();

        m_db.setDatabaseName(db_name);
        openDB();

        if (file_exist == false)
            createTable();
    }
}

DeviceDB::~DeviceDB()
{
    // close
    closeDB();
}

// open
bool DeviceDB::openDB()
{
    if (m_db.open() == false)
    {
        return false;
    }
    return true;
}

// create
void DeviceDB::createTable()
{
    // open
    if (openDB() ==false)
        return ;

    QSqlQuery query;
    QString strSql = "";
    strSql = QString("CREATE TABLE IF NOT EXISTS t_configdata(key TEXT PRIMARY KEY, profile INTEGER, value TEXT)");
    query.exec(strSql);

    strSql = QString("CREATE TABLE IF NOT EXISTS t_radiprofile(radi_id INTEGER PRIMARY KEY AUTOINCREMENT, \
                     profile INTEGER, name TEXT, mode INTEGER, rgb_mode INTEGER, rgb_speed INTEGER, rgb_brightness INTEGER, \
                     rgb_direction INTEGER, r_value INTEGER, g_value INTEGER, b_value INTEGER, status INTEGER)");
    query.exec(strSql);
    strSql = QString("CREATE INDEX IF NOT EXISTS radiindex ON t_radiprofile(radi_id)");
    query.exec(strSql);

    strSql = QString("CREATE TABLE IF NOT EXISTS t_keyrgbdata(rgb_id INTEGER PRIMARY KEY AUTOINCREMENT, \
                     radi_id INTEGER, keyvalue INTEGER, r_value INTEGER, g_value INTEGER, b_value INTEGER)");
    query.exec(strSql);
    strSql = QString("CREATE INDEX IF NOT EXISTS rgbindex ON t_keyrgbdata(rgb_id)");
    query.exec(strSql);

    strSql = QString("CREATE TABLE IF NOT EXISTS t_keyprofile(key_id INTEGER PRIMARY KEY AUTOINCREMENT, \
                     profile INTEGER, keyvalue INTEGER, macrotype INTEGER, macrovalue INTEGER, macrodesc TEXT, \
                     macrovalue1 INTEGER, macrovalue2 INTEGER)");
    query.exec(strSql);
    strSql = QString("CREATE INDEX IF NOT EXISTS keyindex ON t_keyprofile(key_id)");
    query.exec(strSql);

    // init database
    initDatabase();
}

// close
void DeviceDB::closeDB()
{
    m_db.close();
}

// read config data
bool DeviceDB::readConfigData(int profile, QString key, QString& value)
{
    QSqlQuery query;
    query.prepare("SELECT value FROM t_configdata WHERE profile = ? AND key = ?");
    query.addBindValue(profile);
    query.addBindValue(key);
    bool result = query.exec();

    if (result == true && query.next())
    {
        QSqlRecord record  = query.record();
        if (record.count() > 0)
        {
            int index_mode = record.indexOf("value");
            value = record.value(index_mode).toString();
        }
    }
    return result;
}

// update config data
bool DeviceDB::updateConfigData(int profile, QString key, QString value)
{
    QSqlQuery query;
    query.prepare("UPDATE t_configdata SET value = ? WHERE key = ? AND profile = ?");
    query.addBindValue(value);
    query.addBindValue(key);
    query.addBindValue(profile);

    return query.exec();
}

// write radi data
void DeviceDB::writeRadiData(int profile)
{
    QSqlQuery query;
    query.prepare("SELECT * FROM t_radiprofile WHERE profile = ?");
    query.addBindValue(profile);
    bool result = query.exec();
    if (result == true && query.next())
    {
        QSqlRecord record  = query.record();
        if (record.count() > 0)
        {
            return ;
        }
    }

    QString radiname = "";
    for (int i=1; i<13; i++)
    {
        QSqlQuery radi_query;
        radi_query.prepare("INSERT INTO t_radiprofile (profile, name, mode, \
                           rgb_mode, rgb_speed, rgb_brightness, rgb_direction, r_value, g_value, b_value, status) VALUES\
                            (:profile, :name, :mode, :rgb_mode, :rgb_speed, :rgb_brightness, :rgb_direction, :r_value, :g_value, :b_value, :status)");

        if (i == 1)			radiname = "Static";
        else if (i == 2)	radiname = "Spectrum";
        else if (i == 3)	radiname = "Rainbow";
        else if (i == 4)	radiname = "Power Gauge";
        else if (i == 5)	radiname = "Breathing";
        else if (i == 6)	radiname = "Twinkling Stars";
        else if (i == 7)	radiname = "Reactive";
        else if (i == 8)	radiname = "Marquee";
        else if (i == 9)	radiname = "Aurora";
        else if (i == 10)	radiname = "Icey Fire";
        else if (i == 11)	radiname = "Fn";
        else if (i == 12)	radiname = "Custom";

        radi_query.bindValue(":profile", profile);
        radi_query.bindValue(":name", radiname);
        radi_query.bindValue(":mode", i);

        radi_query.bindValue(":rgb_mode", 0);
        radi_query.bindValue(":rgb_speed", 3);
        radi_query.bindValue(":rgb_brightness", 10);
        radi_query.bindValue(":rgb_direction", 0);
        radi_query.bindValue(":r_value", 255);
        radi_query.bindValue(":g_value", 225);
        radi_query.bindValue(":b_value", 0);

        if (i == 1)
            radi_query.bindValue(":status", 1);
        else
            radi_query.bindValue(":status", 0);

        radi_query.exec();
    }
}

// modify rgb param
bool DeviceDB::modifyRadiRGBData(RadiData &data)
{
    QSqlQuery query;
    query.prepare("UPDATE t_radiprofile SET rgb_mode = ?, rgb_speed = ?, rgb_brightness = ?, rgb_direction = ?, \
                    r_value = ?, g_value = ?, b_value = ? WHERE profile = ? AND mode = ?");
    query.addBindValue(data.rgb_mode);
    query.addBindValue(data.rgb_speed);
    query.addBindValue(data.rgb_brightness);
    query.addBindValue(data.rgb_direction);
    query.addBindValue(data.r_value);
    query.addBindValue(data.g_value);
    query.addBindValue(data.b_value);
    query.addBindValue(data.profile_id);
    query.addBindValue(data.mode);
    bool result = query.exec();

    return result;
}

// set select mode with current profile
bool DeviceDB::setSelectMode(int profile, int mode)
{
    QSqlQuery query;
    query.prepare("UPDATE t_radiprofile SET status = ? WHERE profile = ?");
    query.addBindValue(0);
    query.addBindValue(profile);
    bool result = query.exec();

    if (result == true)
    {
        query.prepare("UPDATE t_radiprofile SET status = ? WHERE profile = ? AND mode = ?");
        query.addBindValue(1);
        query.addBindValue(profile);
        query.addBindValue(mode);
        result = query.exec();
    }
    return result;
}

// get  select mode with current profile
int DeviceDB::getSelectMode(int profile)
{
    QSqlQuery query;
    query.prepare("SELECT mode FROM t_radiprofile WHERE profile = ? AND status = ?");
    query.addBindValue(profile);
    query.addBindValue(1);
    bool result = query.exec();

    int selectMode = 0;
    if (result == true && query.next())
    {
        QSqlRecord record  = query.record();
        if (record.count() > 0)
        {
            int index_mode = record.indexOf("mode");
            selectMode = record.value(index_mode).toInt();
        }
    }
    return selectMode;
}

// query select light data info with profile
bool DeviceDB::querySelectRadiInfo(int profile, RadiData &data)
{
    QSqlQuery query;
    query.prepare("SELECT * FROM t_radiprofile WHERE profile = ? AND status = ?");
    query.addBindValue(profile);
    query.addBindValue(1);
    bool result = query.exec();

    if (result == true && query.next())
    {
        QSqlRecord record  = query.record();
        if (record.count() > 0)
        {
            int index = record.indexOf("radi_id");
            data.radi_id = record.value(index).toInt();

            index = record.indexOf("profile");
            data.profile_id = record.value(index).toInt();

            index = record.indexOf("name");
            data.name = record.value(index).toString();

            index = record.indexOf("mode");
            data.mode = record.value(index).toInt();

            index = record.indexOf("rgb_mode");
            data.rgb_mode = record.value(index).toInt();

            index = record.indexOf("rgb_speed");
            data.rgb_speed = record.value(index).toInt();

            index = record.indexOf("rgb_brightness");
            data.rgb_brightness = record.value(index).toInt();

            index = record.indexOf("rgb_direction");
            data.rgb_direction = record.value(index).toInt();

            index = record.indexOf("r_value");
            data.r_value = record.value(index).toInt();

            index = record.indexOf("g_value");
            data.g_value = record.value(index).toInt();

            index = record.indexOf("b_value");
            data.b_value = record.value(index).toInt();

            index = record.indexOf("status");
            data.status = record.value(index).toInt();
        }
    }
    return result;
}

// query  light data info with profile and mode
bool DeviceDB::queryRadiInfo(int profile, int mode, RadiData &data)
{
    QSqlQuery query;
    query.prepare("SELECT * FROM t_radiprofile WHERE profile = ? AND mode = ?");
    query.addBindValue(profile);
    query.addBindValue(mode);
    bool result = query.exec();

    if (result == true && query.next())
    {
        QSqlRecord record  = query.record();
        if (record.count() > 0)
        {
            int index = record.indexOf("radi_id");
            data.radi_id = record.value(index).toInt();

            index = record.indexOf("profile");
            data.profile_id = record.value(index).toInt();

            index = record.indexOf("name");
            data.name = record.value(index).toString();

            index = record.indexOf("mode");
            data.mode = record.value(index).toInt();

            index = record.indexOf("rgb_mode");
            data.rgb_mode = record.value(index).toInt();

            index = record.indexOf("rgb_speed");
            data.rgb_speed = record.value(index).toInt();

            index = record.indexOf("rgb_brightness");
            data.rgb_brightness = record.value(index).toInt();

            index = record.indexOf("rgb_direction");
            data.rgb_direction = record.value(index).toInt();

            index = record.indexOf("r_value");
            data.r_value = record.value(index).toInt();

            index = record.indexOf("g_value");
            data.g_value = record.value(index).toInt();

            index = record.indexOf("b_value");
            data.b_value = record.value(index).toInt();

            index = record.indexOf("status");
            data.status = record.value(index).toInt();
        }
    }
    return result;
}

// query  light data infos with profile
int DeviceDB::queryRadiInfos(int profile, QVector<RadiData*> &vecdata)
{
    QSqlQuery query;
    query.prepare("SELECT * FROM t_radiprofile WHERE profile = ?");
    query.addBindValue(profile);
    if (query.exec() == false)
        return 0;

    while (query.next())
    {
        QSqlRecord record  = query.record();
        if (record.count() > 0)
        {
            RadiData* data = new RadiData();

            int index = record.indexOf("radi_id");
            data->radi_id = record.value(index).toInt();

            index = record.indexOf("profile");
            data->profile_id = record.value(index).toInt();

            index = record.indexOf("name");
            data->name = record.value(index).toString();

            index = record.indexOf("mode");
            data->mode = record.value(index).toInt();

            index = record.indexOf("rgb_mode");
            data->rgb_mode = record.value(index).toInt();

            index = record.indexOf("rgb_speed");
            data->rgb_speed = record.value(index).toInt();

            index = record.indexOf("rgb_brightness");
            data->rgb_brightness = record.value(index).toInt();

            index = record.indexOf("rgb_direction");
            data->rgb_direction = record.value(index).toInt();

            index = record.indexOf("r_value");
            data->r_value = record.value(index).toInt();

            index = record.indexOf("g_value");
            data->g_value = record.value(index).toInt();

            index = record.indexOf("b_value");
            data->b_value = record.value(index).toInt();

            index = record.indexOf("status");
            data->status = record.value(index).toInt();

            vecdata.push_back(data);
        }
    }
    return vecdata.size();
}

//  add key rgb color
bool DeviceDB::addKeyRGBData(RGBData data)
{
    // delete old key color
    QSqlQuery query;
    query.prepare("DELETE FROM t_keyrgbdata WHERE radi_id = ? AND keyvalue = ?");
    query.addBindValue(data.radi_id);
    query.addBindValue(data.key_value);
    bool result = query.exec();

    if (data.r_value == 0 &&  data.g_value == 0 && data.b_value == 0)
        return  result;

    query.prepare("INSERT INTO t_keyrgbdata(radi_id, keyvalue, r_value, g_value, b_value)\
                                 VALUES (?, ?, ?, ?, ?);");
    query.addBindValue(data.radi_id);
    query.addBindValue(data.key_value);
    query.addBindValue(data.r_value);
    query.addBindValue(data.g_value);
    query.addBindValue(data.b_value);

    result = query.exec();
    return result;
}

// query key rgb color
bool DeviceDB::queryKeysRGBData(int radi_id, QVector<RGBData*> &vecdata)
{
    QSqlQuery query;
    query.prepare("SELECT * FROM t_keyrgbdata WHERE radi_id = ?");
    query.addBindValue(radi_id);
    bool result = query.exec();
    if (result == false)
        return result;

    while(query.next())
    {
        QSqlRecord record  = query.record();
        if (record.count() > 0)
        {
            RGBData *data = new RGBData;

            int index = record.indexOf("rgb_id");
            data->rgb_id = record.value(index).toInt();

            index = record.indexOf("radi_id");
            data->radi_id = record.value(index).toInt();

            index = record.indexOf("keyvalue");
            data->key_value = record.value(index).toInt();

            index = record.indexOf("r_value");
            data->r_value = record.value(index).toInt();

            index = record.indexOf("g_value");
            data->g_value = record.value(index).toInt();

            index = record.indexOf("b_value");
            data->b_value = record.value(index).toInt();

            vecdata.push_back(data);
        }
    }
    return result;
}

// delete key rgb with radi-mode
bool DeviceDB::deleteKeyRGBData(int radi_id)
{
    QSqlQuery query;
    query.prepare("DELETE FROM t_keyrgbdata WHERE radi_id = ?");
    query.addBindValue(radi_id);

    return query.exec();
}

// add key data
bool DeviceDB::addKeyProfile(KeyData &data)
{
    if (data.key_value <= 0)
        return false ;

    // delete old key profile
    QSqlQuery query;
    query.prepare("DELETE FROM t_keyprofile WHERE profile = ? AND keyvalue = ?");
    query.addBindValue(data.profile);
    query.addBindValue(data.key_value);
    bool result = query.exec();

    if (data.macro_value == 0)
        return  result;

    query.prepare("INSERT INTO t_keyprofile(profile, keyvalue, macrotype, macrovalue, macrodesc, macrovalue1, macrovalue2)\
                                 VALUES (?, ?, ?, ?, ?, ?, ?);");
    query.addBindValue(data.profile);
    query.addBindValue(data.key_value);
    query.addBindValue(data.macro_type);
    query.addBindValue(data.macro_value);
    query.addBindValue(data.macro_name);
    query.addBindValue(data.macro_value1);
    query.addBindValue(data.macro_value2);

    result = query.exec();
    return result;
}

// query key data ( keyonly == true,  only return keyvalue)
int DeviceDB::queryKeyProfileInfo(int profile, QVector<KeyData*> &vecdata, bool keyvalue_only)
{
    QSqlQuery query;

    if (keyvalue_only)
        query.prepare("SELECT keyvalue FROM t_keyprofile WHERE profile = ?");
    else
        query.prepare("SELECT * FROM t_keyprofile WHERE profile = ?");

    query.addBindValue(profile);
    bool result = query.exec();
    if (result == false)
        return 0;

    while(query.next())
    {
        QSqlRecord record  = query.record();
        if (record.count() > 0)
        {
            KeyData *data = new KeyData;

            if (keyvalue_only)
            {
                int index = record.indexOf("keyvalue");
                data->key_value = record.value(index).toInt();
            }
            else
            {
                int index = record.indexOf("key_id");
                data->key_id = record.value(index).toInt();

                index = record.indexOf("profile");
                data->profile = record.value(index).toInt();

                index = record.indexOf("keyvalue");
                data->key_value = record.value(index).toInt();

                index = record.indexOf("macrotype");
                data->macro_type = record.value(index).toInt();

                index = record.indexOf("macrovalue");
                data->macro_value = record.value(index).toInt();

                index = record.indexOf("macrodesc");
                data->macro_name = record.value(index).toString();

                index = record.indexOf("macrovalue1");
                data->macro_value1 = record.value(index).toInt();

                index = record.indexOf("macrovalue2");
                data->macro_value2 = record.value(index).toInt();
            }
            vecdata.push_back(data);
        }
    }
    return vecdata.size();
}

// query key data  (key info)
bool DeviceDB::queryKeyProfileInfo(int profile, int key_value, KeyData &data)
{
    QSqlQuery query;
    query.prepare("SELECT * FROM t_keyprofile WHERE profile = ? and keyvalue = ?");
    query.addBindValue(profile);
    query.addBindValue(key_value);
    bool result = query.exec();
    if (result == false)
        return false;

    result = false;

    while(query.next())
    {
        QSqlRecord record  = query.record();
        if (record.count() > 0)
        {
            result = true;

            int index = record.indexOf("key_id");
            data.key_id = record.value(index).toInt();

            index = record.indexOf("profile");
            data.profile = record.value(index).toInt();

            index = record.indexOf("keyvalue");
            data.key_value = record.value(index).toInt();

            index = record.indexOf("macrotype");
            data.macro_type = record.value(index).toInt();

            index = record.indexOf("macrovalue");
            data.macro_value = record.value(index).toInt();

            index = record.indexOf("macrodesc");
            data.macro_name = record.value(index).toString();

            index = record.indexOf("macrovalue1");
            data.macro_value1 = record.value(index).toInt();

            index = record.indexOf("macrovalue2");
            data.macro_value2 = record.value(index).toInt();
        }
    }
    return result;
}

// init database
void DeviceDB::initDatabase()
{
    QSqlQuery query;
    query.prepare("INSERT INTO t_configdata VALUES (:key, :profile, :value)");
    query.bindValue(":key", "report_rate");
    query.bindValue(":profile", 1);
    query.bindValue(":value", "2");
    query.exec();

    query.prepare("INSERT INTO t_configdata VALUES (:key, :profile, :value)");
    query.bindValue(":key", "delay_usbwiresleep");
    query.bindValue(":profile", 1);
    query.bindValue(":value", "300");
    query.exec();

    query.prepare("INSERT INTO t_configdata VALUES (:key, :profile, :value)");
    query.bindValue(":key", "delay_closelight");
    query.bindValue(":profile", 1);
    query.bindValue(":value", "120");
    query.exec();

    query.prepare("INSERT INTO t_configdata VALUES (:key, :profile, :value)");
    query.bindValue(":key", "delay_wirelesssleep");
    query.bindValue(":profile", 1);
    query.bindValue(":value", "180");
    query.exec();
}
