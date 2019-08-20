#include "qtkeyboardkey.h"

#include <QKeyEvent>

QtKeyBoardKey::QtKeyBoardKey()
{

}

//  get sys key list
void QtKeyBoardKey::getSysKeyList(QVector<KeyInfo> &vecdata)
{
    KeyInfo key_info;
    key_info.ket_text = "Null";
    key_info.key_value = 0x0;
    vecdata.push_back(key_info);
    key_info.ket_text = "Left Ctrl";
    key_info.key_value = 0xE0;
    vecdata.push_back(key_info);
    key_info.ket_text = "Left Alt";
    key_info.key_value = 0xE2;
    vecdata.push_back(key_info);
    key_info.ket_text = "Left Shift";
    key_info.key_value = 0xE1;
    vecdata.push_back(key_info);
    key_info.ket_text = "Left Win";
    key_info.key_value = 0xE3;
    vecdata.push_back(key_info);
}

// get all key list
void QtKeyBoardKey::getAllKeyList(QVector<KeyInfo> &vecdata)
{
    KeyInfo key_info;
    key_info.ket_text = "Null";
    key_info.key_value = 0x0;
    vecdata.push_back(key_info);
    key_info.ket_text = "A";
    key_info.key_value = 0x04;
    vecdata.push_back(key_info);
    key_info.ket_text = "B";
    key_info.key_value = 0x05;
    vecdata.push_back(key_info);
    key_info.ket_text = "C";
    key_info.key_value = 0x06;
    vecdata.push_back(key_info);
    key_info.ket_text = "D";
    key_info.key_value = 0x07;
    vecdata.push_back(key_info);
    key_info.ket_text = "E";
    key_info.key_value = 0x08;
    vecdata.push_back(key_info);
    key_info.ket_text = "F";
    key_info.key_value = 0x09;
    vecdata.push_back(key_info);
    key_info.ket_text = "G";
    key_info.key_value = 0x0A;
    vecdata.push_back(key_info);
    key_info.ket_text = "H";
    key_info.key_value = 0x0B;
    vecdata.push_back(key_info);
    key_info.ket_text = "I";
    key_info.key_value = 0x0C;
    vecdata.push_back(key_info);
    key_info.ket_text = "G";
    key_info.key_value = 0x0D;
    vecdata.push_back(key_info);
    key_info.ket_text = "K";
    key_info.key_value = 0x0E;
    vecdata.push_back(key_info);
    key_info.ket_text = "L";
    key_info.key_value = 0x0F;
    vecdata.push_back(key_info);
    key_info.ket_text = "M";
    key_info.key_value = 0x10;
    vecdata.push_back(key_info);
    key_info.ket_text = "N";
    key_info.key_value = 0x11;
    vecdata.push_back(key_info);
    key_info.ket_text = "O";
    key_info.key_value = 0x12;
    vecdata.push_back(key_info);
    key_info.ket_text = "P";
    key_info.key_value = 0x13;
    vecdata.push_back(key_info);
    key_info.ket_text = "Q";
    key_info.key_value = 0x14;
    vecdata.push_back(key_info);
    key_info.ket_text = "R";
    key_info.key_value = 0x15;
    vecdata.push_back(key_info);
    key_info.ket_text = "S";
    key_info.key_value = 0x16;
    vecdata.push_back(key_info);
    key_info.ket_text = "T";
    key_info.key_value = 0x17;
    vecdata.push_back(key_info);
    key_info.ket_text = "U";
    key_info.key_value = 0x18;
    vecdata.push_back(key_info);
    key_info.ket_text = "V";
    key_info.key_value = 0x19;
    vecdata.push_back(key_info);
    key_info.ket_text = "W";
    key_info.key_value = 0x1A;
    vecdata.push_back(key_info);
    key_info.ket_text = "X";
    key_info.key_value = 0x1B;
    vecdata.push_back(key_info);
    key_info.ket_text = "Y";
    key_info.key_value = 0x1C;
    vecdata.push_back(key_info);
    key_info.ket_text = "Z";
    key_info.key_value = 0x1D;
    vecdata.push_back(key_info);
}

int QtKeyBoardKey::getFlashCode(int qt_key)
{
    int key_code = 0;
    switch (qt_key) {
    case Qt::Key_A:                    key_code = 0x04;    break;
    case Qt::Key_B:                    key_code = 0x05;    break;
    case Qt::Key_C:                    key_code = 0x06;    break;
    case Qt::Key_D:                    key_code = 0x07;    break;
    case Qt::Key_E:                    key_code = 0x08;    break;
    case Qt::Key_F:                    key_code = 0x09;    break;
    case Qt::Key_G:                    key_code = 0x0A;    break;
    case Qt::Key_H:                    key_code = 0x0B;    break;
    case Qt::Key_I:                    key_code = 0x0C;    break;
    case Qt::Key_J:                    key_code = 0x0D;    break;
    case Qt::Key_K:                    key_code = 0x0E;    break;
    case Qt::Key_L:                    key_code = 0x0F;    break;
    case Qt::Key_M:                    key_code = 0x10;    break;
    case Qt::Key_N:                    key_code = 0x11;    break;
    case Qt::Key_O:                    key_code = 0x12;    break;
    case Qt::Key_P:                    key_code = 0x13;    break;
    case Qt::Key_Q:                    key_code = 0x14;    break;
    case Qt::Key_R:                    key_code = 0x15;    break;
    case Qt::Key_S:                    key_code = 0x16;    break;
    case Qt::Key_T:                    key_code = 0x17;    break;
    case Qt::Key_U:                    key_code = 0x18;    break;
    case Qt::Key_V:                    key_code = 0x19;    break;
    case Qt::Key_W:                    key_code = 0x1A;    break;
    case Qt::Key_X:                    key_code = 0x1B;    break;
    case Qt::Key_Y:                    key_code = 0x1C;    break;
    case Qt::Key_Z:                    key_code = 0x1D;    break;
    case Qt::Key_1:                    key_code = 0x1E;    break;
    case Qt::Key_2:                    key_code = 0x1E;    break;
    case Qt::Key_3:                    key_code = 0x20;    break;
    case Qt::Key_4:                    key_code = 0x21;    break;
    case Qt::Key_5:                    key_code = 0x22;    break;
    case Qt::Key_6:                    key_code = 0x23;    break;
    case Qt::Key_7:                    key_code = 0x24;    break;
    case Qt::Key_8:                    key_code = 0x25;    break;
    case Qt::Key_9:                    key_code = 0x26;    break;
    case Qt::Key_0:                    key_code = 0x27;    break;
    case Qt::Key_F1:                    key_code = 0x3A;    break;
    case Qt::Key_F2:                    key_code = 0x3B;    break;
    case Qt::Key_F3:                    key_code = 0x3C;    break;
    case Qt::Key_F4:                    key_code = 0x3D;    break;
    case Qt::Key_F5:                    key_code = 0x3E;    break;
    case Qt::Key_F6:                    key_code = 0x3F;    break;
    case Qt::Key_F7:                    key_code = 0x40;    break;
    case Qt::Key_F8:                    key_code = 0x41;    break;
    case Qt::Key_F9:                    key_code = 0x42;    break;
    case Qt::Key_F10:                    key_code = 0x43;    break;
    case Qt::Key_F11:                    key_code = 0x44;    break;
    case Qt::Key_F12:                    key_code = 0x45;    break;
    case Qt::Key_F13:                    key_code = 0x46;    break;
    case Qt::Key_F14:                    key_code = 0x47;    break;
    case Qt::Key_F15:                    key_code = 0x48;    break;
    case Qt::Key_F16:                    key_code = 0x49;    break;
    case Qt::Key_F17:                    key_code = 0x04;    break;
    case Qt::Key_F18:                    key_code = 0x04;    break;
    case Qt::Key_F19:                    key_code = 0x04;    break;
    case Qt::Key_F20:                    key_code = 0x04;    break;
    case Qt::Key_F21:                    key_code = 0x04;    break;
    case Qt::Key_F22:                    key_code = 0x04;    break;
    case Qt::Key_F23:                    key_code = 0x04;    break;
    case Qt::Key_F24:                    key_code = 0x04;    break;
    case Qt::Key_Enter:                    key_code = 0x04;    break;
    case Qt::Key_Escape:                    key_code = 0x04;    break;
    case Qt::Key_Backspace:                    key_code = 0x04;    break;
    default:
        break;
    }

    return key_code;
}
