#include "devicecomm.h"
#include <QDebug>

DeviceComm::DeviceComm()
{
    libusb_init(NULL);
    m_hid_device = NULL;
    m_isconnect = false;
    m_interface = 0;
    m_kb_layout = 1;
}
DeviceComm::~DeviceComm()
{
    if (m_hid_device)
    {
        libusb_release_interface(m_hid_device, m_interface);
        libusb_close(m_hid_device);
    }

    libusb_exit(NULL);
}

QString DeviceComm::enumerateDevice()
{
    m_isconnect = false;

    QString device_name = "CONNECT YOUR DEVICE";
    libusb_device  **dev_list;
    ssize_t num_devs = libusb_get_device_list(NULL, &dev_list);
    if (num_devs <= 0)
        return  device_name;

    for ( int i = 0; i <num_devs; i++ )
    {
         libusb_device  *dev_info = dev_list[i];
         if  (dev_info == NULL)
             continue ;

         struct libusb_device_descriptor desc;
         int res = libusb_get_device_descriptor(dev_info, &desc);
         uint16_t dev_vid = desc.idVendor;
         uint16_t dev_pid = desc.idProduct;

         QString res_desc = IsExsitDevice(dev_vid, dev_pid);
         if (res_desc.isEmpty())
             continue;

         device_name = res_desc;

         res = libusb_open(dev_info, &m_hid_device);
         if (m_hid_device)
         {
             if (libusb_kernel_driver_active(m_hid_device, m_interface) == 1)
             {
                 res = libusb_detach_kernel_driver(m_hid_device, m_interface);
                 if (res < 0)
                 {
                     libusb_close(m_hid_device);
                     qDebug() << "Unable to detach Kernel Driver";
                     break;
                 }
             }
             res = libusb_claim_interface(m_hid_device, m_interface);
             if (res < 0) {
                 qDebug() << "can't claim interface"  << m_interface << res;
                 libusb_close(m_hid_device);
                 break;
             }
             m_isconnect = true;
         }
         else
         {
             device_name.append("(LIBUSB_ERROR_ACCESS)");
         }
         break;
    }
    libusb_free_device_list(dev_list, 1);
    return device_name;
}

//  set device data
int  DeviceComm::setDeviceData(const unsigned char *data, size_t length)
{
    qDebug() << data[0] << "" << data[1] << "" << data[2] << "" << data[3] << ""
                          << data[4] << "" << data[5] << "" << data[6] << "" << data[7] << "";

    if (m_hid_device == NULL)
        return -1;

    int res = -1;
    int skipped_report_id = 0;
    int report_number = data[0];

    if (report_number == 0x0) {
        data++;
        length--;
        skipped_report_id = 1;
    }

    res = libusb_control_transfer(m_hid_device,
        LIBUSB_REQUEST_TYPE_CLASS|LIBUSB_RECIPIENT_INTERFACE|LIBUSB_ENDPOINT_OUT,
        0x09/*HID set_report*/,
        (3/*HID feature*/ << 8) | report_number,
        0,
        (unsigned char *)data, length,
        1000/*timeout millis*/);

    if (res < 0)
        return -1;

    /* Account for the report ID */
    if (skipped_report_id)
        length++;

    return length;
}

// set device datas ( length > 8)
int DeviceComm::setDeviceDatas(const unsigned char *data, size_t length)
{
    int steps = length / 6;
    int data_pos = 0;
    int ret = 0;
    for (int i = 0; i < steps; i++)
    {
        unsigned char buf[8] = {0};
        buf[0] = 0x05;
        // 新多包指令
        if (i == 0)
        {
            memcpy(&buf[1], data + data_pos, 7);
            data_pos += 7;
        }
        else
        {
            buf[1] = 0x00;
            memcpy(&buf[2], data + data_pos, 6);
            data_pos += 6;
        }
        ret = setDeviceData(buf, 8);
    }
    return ret;
}

QString DeviceComm::IsExsitDevice(uint16_t dev_vid, uint16_t dev_pid)
{
    QString dev_name = "";
    if (dev_vid != 0x1a2c)
        return dev_name;

    if  (dev_pid == 0xb51f)
    {
        m_kb_layout = 1;
        dev_name = "BladeMaster TE 87K";
    }
    else if (dev_pid == 0xb58f)
    {
        m_kb_layout = 2;
        dev_name = "BladeMaster TE 88K";
    }
    else if (dev_pid == 0xb5bf)
    {
        m_kb_layout = 4;
        dev_name = "BladeMaster TE 91K";
    }
    else if (dev_pid == 0xb57e)
    {
        m_kb_layout = 1;
        dev_name = "BladeMaster PRO 87K";
    }
    else if (dev_pid == 0xb58e)
    {
        m_kb_layout = 2;
        dev_name = "BladeMaster PRO 88K";
    }
    else if (dev_pid == 0xb5be)
    {
        m_kb_layout = 4;
        dev_name = "BladeMaster PRO 91K";
    }

    return dev_name;
}
