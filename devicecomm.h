#ifndef DEVICECOMM_H
#define DEVICECOMM_H

#include <QString>
#include "libusb-1.0/libusb.h"

class DeviceComm
{
public:
    DeviceComm();
    ~DeviceComm();

    // find drevo device
    QString enumerateDevice();

    // get keyboard layout
    int getKeyboardLayout() { return m_kb_layout; }

    //  set device data( length < 8)
    int setDeviceData(const unsigned char *data, size_t length);
    // set device datas ( length > 8)
    int setDeviceDatas(const unsigned char *data, size_t length);

private:

    QString IsExsitDevice(uint16_t dev_vid, uint16_t dev_pid);

    libusb_device_handle*       m_hid_device;
    bool                                       m_isconnect;
    int                                          m_interface; //default 0
    int                                          m_kb_layout;
};

#endif // DEVICECOMM_H
