#ifndef KEYBOARDDATA_H
#define KEYBOARDDATA_H

#include <QString>
#include <QVector>

// radi light data
struct RadiData
{
    int             radi_id;
    int             profile_id;
    int             mode;
    int             rgb_mode;
    int             rgb_speed;
    int             rgb_brightness;
    int             rgb_direction;
    int             r_value;
    int             g_value;
    int             b_value;
    int             status;
    QString    name;
};

// key rgb data
struct RGBData
{
    int             rgb_id;
    int             radi_id;
    int             key_value;
    int             r_value;
    int             g_value;
    int             b_value;
};

// key data
struct KeyData
{
    int             key_id;
    int             profile;
    int             key_value;
    int             macro_type;
    int             macro_value;
    int             macro_value1;
    int             macro_value2;
    QString     macro_name;
};

// macro type
enum MacroType
{
    MT_DELAYTIME = 1,
    MT_KEY_DOWN,
    MT_KEY_UP,
    MT_MOUSE_L_DOWN,
    MT_MOUSE_L_UP,
    MT_MOUSE_M_DOWN,
    MT_MOUSE_M_UP,
    MT_MOUSE_R_DOWN,
    MT_MOUSE_R_UP,
    MT_MOUSE_BUTTON4_DOWN,
    MT_MOUSE_BUTTON4_UP,
    MT_MOUSE_BUTTON5_DOWN,
    MT_MOUSE_BUTTON5_UP,
    MT_MOUSE_SCROLL_DOWN,
    MT_MOUSE_SCROLL_UP,
};

// key macro
struct KeyMacro
{
    int         macro_type;
    int         macro_value;
};

// key remap(kb_profile: 0(G1-fn + ctrl + f1), 1(G2-fn + ctrl + f2), 2(G3-fn + ctrl + f3))
void hid_keyRemapData(int src_key, int dst_key, int kb_layout, uint8_t* kb_data, int kb_profile = 0);

// combo key (kb_profile: 0(G1-fn + ctrl + f1), 1(G2-fn + ctrl + f2), 2(G3-fn + ctrl + f3))
void hid_combokeyData(int src_key, int dst_syskey1, int dst_syskey2, int dst_key, int kb_layout, uint8_t* kb_data, int kb_profile = 0);

// key macro
void hid_keymacro(int src_key,  int play_times, QVector<KeyMacro*> &vec_data, int kb_layout, uint8_t* kb_data, int kb_profile = 0);

// key default value
void hid_keyDefaultValue(int src_key,  int kb_layout, uint8_t* kb_data, int kb_profile = 0);

// disable key
void hid_disablekeyValue(int src_key,  int kb_layout, uint8_t* kb_data, int kb_profile = 0);

// get radi-light data(kb_data size is 8)
void hid_getRadiData(RadiData data, uint8_t* kb_data);

// get radi-light key rgb list data
void hid_getKeyRGBData(QVector<RGBData*> &vecdata, int kb_layout, uint8_t* kb_data);

// get keyboard report rate
void hid_getKeyboardReportRate(int value, uint8_t* kb_data);

// usb mode sleep time
void hid_getUSBModeSleepTime(int time, uint8_t* kb_data);

// wireless mode sleep time
void hid_getWirelessModeSleepTime(int backlight_time, int wireless_time, uint8_t* kb_data);

// reset keyboard data
void hid_getResetKeyboard(uint8_t* kb_data);

// get key index(1: 87; 2: 88; 3:89; 4:91)
int kb_getKeyIndex(int key_value, int kb_layout);
int kb_get87LayoutKeyIndex(int key_value);
int kb_get88LayoutKeyIndex(int key_value);
int kb_get91LayoutKeyIndex(int key_value);


#endif // KEYBOARDDATA_H
