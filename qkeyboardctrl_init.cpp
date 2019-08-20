#include "qkeyboardctrl.h"

// 初始化键盘按键
void QKeyboardCtrl::initKeyboardKey()
{
    // 清空所有按键
    clearAllKeys();

    int xpos = 21;
    int ypos = 15;
    int key_width = 35, key_height = 36;
    QRect rcItem(xpos,ypos, key_width, key_height);
    addKeyItem(("Esc"), 0x29, rcItem);
    xpos = 92;
    rcItem.setCoords(xpos,ypos, xpos+key_width, ypos+key_height);
    addKeyItem(("F1"), 0x3A, rcItem);
    xpos += (key_width+1);
    rcItem.setCoords(xpos,ypos, xpos+key_width, ypos+key_height);
    addKeyItem(("F2"),  0x3B, rcItem);
    xpos += (key_width+1);
    rcItem.setCoords(xpos,ypos, xpos+key_width, ypos+key_height);
    addKeyItem(("F3"), 0x3C, rcItem);
    xpos += (key_width+1);
    rcItem.setCoords(xpos,ypos, xpos+key_width, ypos+key_height);
    addKeyItem(("F4"), 0x3D, rcItem);
    xpos += (key_width+20);
    rcItem.setCoords(xpos,ypos, xpos+key_width, ypos+key_height);
    addKeyItem(("F5"), 0x3E, rcItem);
    xpos += (key_width+1);
    rcItem.setCoords(xpos,ypos, xpos+key_width, ypos+key_height);
    addKeyItem(("F6"),  0x3F, rcItem);
    xpos += (key_width+1);
    rcItem.setCoords(xpos,ypos, xpos+key_width, ypos+key_height);
    addKeyItem(("F7"),  0x40, rcItem);
    xpos += (key_width+1);
    rcItem.setCoords(xpos,ypos, xpos+key_width, ypos+key_height);
    addKeyItem(("F8"), 0x41, rcItem);
    xpos += (key_width+19);
    rcItem.setCoords(xpos,ypos, xpos+key_width, ypos+key_height);
    addKeyItem(("F9"), 0x42, rcItem);
    xpos += (key_width+1);
    rcItem.setCoords(xpos,ypos, xpos+key_width, ypos+key_height);
    addKeyItem(("F10"), 0x43, rcItem);
    xpos += (key_width+1);
    rcItem.setCoords(xpos,ypos, xpos+key_width, ypos+key_height);
    addKeyItem(("F11"), 0x44, rcItem);
    xpos += (key_width+1);
    rcItem.setCoords(xpos,ypos, xpos+key_width, ypos+key_height);
    addKeyItem(("F12"), 0x45, rcItem);
    xpos = 570;
    rcItem.setCoords(xpos,ypos, xpos+key_width, ypos+key_height);
    addKeyItem(("PRTSC"), 0x46, rcItem);
    xpos += (key_width+1);
    rcItem.setCoords(xpos,ypos, xpos+key_width, ypos+key_height);
    addKeyItem(("SCRLK"), 0x47, rcItem);
    xpos += (key_width+1);
    rcItem.setCoords(xpos,ypos, xpos+key_width, ypos+key_height);
    addKeyItem(("PAUSE"), 0x48, rcItem);
    // `~
    xpos = 21;
    ypos = 60;
    rcItem.setCoords(xpos,ypos, xpos+key_width, ypos+key_height);
    if (m_kbimagetype == DT_KB_PRO_91 || m_kbimagetype == DT_KB_TE_91)\
        addKeyItem(("半角/全角"), 0x35, rcItem);
    else
        addKeyItem(("~"), 0x35, rcItem);

    xpos += (key_width+1);
    rcItem.setCoords(xpos,ypos, xpos+key_width, ypos+key_height);
    addKeyItem(("1"), 0x1E, rcItem);
    xpos += (key_width+1);
    rcItem.setCoords(xpos,ypos, xpos+key_width, ypos+key_height);
    addKeyItem(("2"), 0x1F, rcItem);
    xpos += (key_width+1);
    rcItem.setCoords(xpos,ypos, xpos+key_width, ypos+key_height);
    addKeyItem(("3"),  0x20, rcItem);
    xpos += (key_width+1);
    rcItem.setCoords(xpos,ypos, xpos+key_width, ypos+key_height);
    addKeyItem(("4"), 0x21, rcItem);
    xpos += (key_width+1);
    rcItem.setCoords(xpos,ypos, xpos+key_width, ypos+key_height);
    addKeyItem(("5"), 0x22, rcItem);
    xpos += (key_width+1);
    rcItem.setCoords(xpos,ypos, xpos+key_width, ypos+key_height);
    addKeyItem(("6"), 0x23, rcItem);
    xpos += (key_width+1);
    rcItem.setCoords(xpos,ypos, xpos+key_width, ypos+key_height);
    addKeyItem(("7"), 0x24, rcItem);
    xpos += (key_width+1);
    rcItem.setCoords(xpos,ypos, xpos+key_width, ypos+key_height);
    addKeyItem(("8"), 0x25, rcItem);
    xpos += (key_width+1);
    rcItem.setCoords(xpos,ypos, xpos+key_width, ypos+key_height);
    addKeyItem(("9"), 0x26, rcItem);
    xpos += (key_width+1);
    rcItem.setCoords(xpos,ypos, xpos+key_width, ypos+key_height);
    addKeyItem(("0"), 0x27, rcItem);
    xpos += (key_width+1);
    rcItem.setCoords(xpos, ypos, xpos+key_width, ypos+key_height);
    addKeyItem(("_-"), 0x2D, rcItem);
    xpos += (key_width+1);
    rcItem.setCoords(xpos,ypos, xpos+key_width, ypos+key_height);
    if (m_kbimagetype == DT_KB_PRO_91 || m_kbimagetype == DT_KB_TE_91)
    {
        addKeyItem(("^"), 0x2E, rcItem);
        xpos += (key_width+1);
        rcItem.setCoords(xpos,ypos, xpos+key_width, ypos+key_height);
        addKeyItem(("¥"), 137, rcItem);
        xpos += (key_width+1);
        rcItem.setCoords(xpos,ypos, xpos+key_width, ypos+key_height);
        addKeyItem(("←"), 0x2A, rcItem);
    }
    else
    {
        addKeyItem(("="), 0x2E, rcItem);
        xpos += (key_width+1);
        rcItem.setCoords(xpos,ypos, xpos+71, ypos+key_height);
        addKeyItem(("←"), 0x2A, rcItem);
    }
    xpos = 570;
    rcItem.setCoords(xpos,ypos, xpos+key_width, ypos+key_height);
    addKeyItem(("INS"), 0x49, rcItem);
    xpos += (key_width+1);
    rcItem.setCoords(xpos,ypos, xpos+key_width, ypos+key_height);
    addKeyItem(("HOME"), 0x4A, rcItem);
    xpos += (key_width+1);
    rcItem.setCoords(xpos,ypos, xpos+key_width, ypos+key_height);
    addKeyItem(("PG UP"), 0x4B, rcItem);
    // TAB
    xpos = 21;
    ypos += key_height;
    rcItem.setCoords(xpos,ypos, xpos+52, ypos+key_height);
    addKeyItem(("TAB"), 0x2B, rcItem);
    xpos += 53;
    rcItem.setCoords(xpos,ypos, xpos+key_width, ypos+key_height);
    addKeyItem(("Q"),  0x14, rcItem);
    xpos += (key_width+1);
    rcItem.setCoords(xpos,ypos, xpos+key_width, ypos+key_height);
    addKeyItem(("W"),  0x1A, rcItem);
    xpos += (key_width+1);
    rcItem.setCoords(xpos,ypos, xpos+key_width, ypos+key_height);
    addKeyItem(("E"),  0x08, rcItem);
    xpos += (key_width+1);
    rcItem.setCoords(xpos,ypos, xpos+key_width, ypos+key_height);
    addKeyItem(("R"), 0x15, rcItem);
    xpos += (key_width+1);
    rcItem.setCoords(xpos,ypos, xpos+key_width, ypos+key_height);
    addKeyItem(("T"), 0x17, rcItem);
    xpos += (key_width+1);
    rcItem.setCoords(xpos,ypos, xpos+key_width, ypos+key_height);
    addKeyItem(("Y"), 0x1C, rcItem);
    xpos += (key_width+1);
    rcItem.setCoords(xpos,ypos, xpos+key_width, ypos+key_height);
    addKeyItem(("U"), 0x18, rcItem);
    xpos += (key_width+1);
    rcItem.setCoords(xpos,ypos, xpos+key_width, ypos+key_height);
    addKeyItem(("I"), 0x0C, rcItem);
    xpos += (key_width+1);
    rcItem.setCoords(xpos,ypos, xpos+key_width, ypos+key_height);
    addKeyItem(("O"),  0X12, rcItem);
    xpos += (key_width+1);
    rcItem.setCoords(xpos,ypos, xpos+key_width, ypos+key_height);
    addKeyItem(("P"),  0X13, rcItem);
    xpos += (key_width+1);
    if (m_kbimagetype == DT_KB_PRO_88 || m_kbimagetype == DT_KB_TE_88)
    {
        rcItem.setCoords(xpos,ypos, xpos+key_width, ypos+key_height);
        addKeyItem(("["),  0x2F, rcItem);
        xpos += (key_width+2);
        rcItem.setCoords(xpos,ypos, xpos+key_width, ypos+key_height);
        addKeyItem(("]"),  0x30, rcItem);
        xpos += (key_width+2);
        rcItem.setCoords(xpos,ypos, xpos+52, ypos+key_height);
        addKeyItem(("ENTER"), 0x28, rcItem);
    }
    else if (m_kbimagetype == DT_KB_PRO_91 || m_kbimagetype == DT_KB_TE_91)
    {
        rcItem.setCoords(xpos,ypos, xpos+key_width, ypos+key_height);
        addKeyItem(("@"),  0x2F, rcItem);
        xpos += (key_width+2);
        rcItem.setCoords(xpos,ypos, xpos+key_width, ypos+key_height);
        addKeyItem(("["),  0x30, rcItem);
        xpos += (key_width+2);
        rcItem.setCoords(xpos,ypos, xpos+52, ypos+key_height);
        addKeyItem(("ENTER"), 0x28, rcItem);
    }
    else
    {
        rcItem.setCoords(xpos,ypos, xpos+key_width, ypos+key_height);
        addKeyItem(("["), 0x2F, rcItem);
        xpos += (key_width+2);
        rcItem.setCoords(xpos,ypos, xpos+key_width, ypos+key_height);
        addKeyItem(("]"), 0x30, rcItem);
        xpos += (key_width+2);
        rcItem.setCoords(xpos,ypos, xpos+52, ypos+key_height);
        addKeyItem(("\\"), 0x31, rcItem);
    }
    xpos = 570;
    rcItem.setCoords(xpos,ypos, xpos+key_width, ypos+key_height);
    addKeyItem(("DEL"), 0x4C, rcItem);
    xpos += (key_width+1);
    rcItem.setCoords(xpos,ypos, xpos+key_width, ypos+key_height);
    addKeyItem(("END"), 0x4D, rcItem);
    xpos += (key_width+1);
    rcItem.setCoords(xpos,ypos, xpos+key_width, ypos+key_height);
    addKeyItem(("PG DN"), 0x4E, rcItem);
    // CAPS
    xpos = 21;
    ypos += key_height;
    key_height -= 1;
    rcItem.setCoords(xpos,ypos, xpos+62, ypos+key_height);
    addKeyItem(("CAPS"),  0x39, rcItem);
    xpos += (63);
    rcItem.setCoords(xpos,ypos, xpos+key_width, ypos+key_height);
    addKeyItem(("A"), 0x04, rcItem);
    xpos += (key_width+1);
    rcItem.setCoords(xpos,ypos, xpos+key_width, ypos+key_height);
    addKeyItem(("S"),  0x16, rcItem);
    xpos += (key_width+1);
    rcItem.setCoords(xpos,ypos, xpos+key_width, ypos+key_height);
    addKeyItem(("D"),  0x07, rcItem);
    xpos += (key_width+1);
    rcItem.setCoords(xpos,ypos, xpos+key_width, ypos+key_height);
    addKeyItem(("F"), 0x09, rcItem);
    xpos += (key_width+1);
    rcItem.setCoords(xpos,ypos, xpos+key_width, ypos+key_height);
    addKeyItem(("G"),  0x0A, rcItem);
    xpos += (key_width+1);
    rcItem.setCoords(xpos,ypos, xpos+key_width, ypos+key_height);
    addKeyItem(("H"),  0x0B, rcItem);
    xpos += (key_width+1);
    rcItem.setCoords(xpos,ypos, xpos+key_width, ypos+key_height);
    addKeyItem(("J"),  0x0D, rcItem);
    xpos += (key_width+1);
    rcItem.setCoords(xpos,ypos, xpos+key_width, ypos+key_height);
    addKeyItem(("K"), 0x0E, rcItem);
    xpos += (key_width+1);
    rcItem.setCoords(xpos,ypos, xpos+key_width, ypos+key_height);
    addKeyItem(("L"),  0x0F, rcItem);
    xpos += (key_width+1);
    if (m_kbimagetype == DT_KB_PRO_91 || m_kbimagetype == DT_KB_TE_91)
    {
        rcItem.setCoords(xpos,ypos, xpos+key_width, ypos+key_height);
        addKeyItem((";"), 0x33, rcItem);
        xpos += (key_width+1);
        rcItem.setCoords(xpos,ypos, xpos+key_width, ypos+key_height);
        addKeyItem((":"), 222, rcItem);
        xpos += (key_width+1);
        rcItem.setCoords(xpos,ypos, xpos+key_width, ypos+key_height);
        addKeyItem(("]"), 220, rcItem);
    }
    else if (m_kbimagetype == DT_KB_PRO_87 || m_kbimagetype == DT_KB_TE_87)
    {
        rcItem.setCoords(xpos,ypos, xpos+key_width, ypos+key_height);
        addKeyItem((";"), 0x33, rcItem);
        xpos += (key_width+1);
        rcItem.setCoords(xpos,ypos, xpos+key_width, ypos+key_height);
        addKeyItem(("'"), 0x34, rcItem);
        xpos += (key_width+1);
        rcItem.setCoords(xpos,ypos, xpos+80, ypos+key_height);
        addKeyItem(("ENTER"), 0x28, rcItem);
    }
    else if (m_kbimagetype == DT_KB_PRO_88 || m_kbimagetype == DT_KB_TE_88)
    {
        rcItem.setCoords(xpos,ypos, xpos+key_width, ypos+key_height);
        addKeyItem((";"), 0x33, rcItem);
        xpos += (key_width+1);
        rcItem.setCoords(xpos,ypos, xpos+key_width, ypos+key_height);
        addKeyItem(("'"), 0x34, rcItem);
        xpos += (key_width+1);
        rcItem.setCoords(xpos,ypos, xpos+key_width, ypos+key_height);
        addKeyItem(("\\|"), 0x31, rcItem);
    }
    // shift
    xpos = 21;
    ypos += key_height;
    key_height += 1;
    if (m_kbimagetype == DT_KB_PRO_88 || m_kbimagetype == DT_KB_TE_88)
    {
        rcItem.setCoords(xpos,ypos, xpos+44, ypos+key_height);
        addKeyItem(("SHIFT"), 0xE1, rcItem);
        xpos += (44+1);
        rcItem.setCoords(xpos,ypos, xpos+key_width, ypos+key_height);
        addKeyItem(("\\"), 0x64, rcItem);
        xpos += (key_width+1);
    }
    else
    {
        rcItem.setCoords(xpos,ypos, xpos+80, ypos+key_height);
        addKeyItem(("SHIFT"), 0xE1, rcItem);
        xpos += (81);
    }
    rcItem.setCoords(xpos,ypos, xpos+key_width, ypos+key_height);
    addKeyItem(("Z"), 0x1D, rcItem);
    xpos += (key_width+1);
    rcItem.setCoords(xpos,ypos, xpos+key_width, ypos+key_height);
    addKeyItem(("X"), 0x1B, rcItem);
    xpos += (key_width+1);
    rcItem.setCoords(xpos,ypos, xpos+key_width, ypos+key_height);
    addKeyItem(("C"), 0x06, rcItem);
    xpos += (key_width+1);
    rcItem.setCoords(xpos,ypos, xpos+key_width, ypos+key_height);
    addKeyItem(("V"), 0x19, rcItem);
    xpos += (key_width+1);
    rcItem.setCoords(xpos,ypos, xpos+key_width, ypos+key_height);
    addKeyItem(("B"), 0x05, rcItem);
    xpos += (key_width+1);
    rcItem.setCoords(xpos,ypos, xpos+key_width, ypos+key_height);
    addKeyItem(("N"), 0x11, rcItem);
    xpos += (key_width+1);
    rcItem.setCoords(xpos,ypos, xpos+key_width, ypos+key_height);
    addKeyItem(("M"), 0x10, rcItem);
    xpos += (key_width+1);
    rcItem.setCoords(xpos,ypos, xpos+key_width, ypos+key_height);
    addKeyItem(("<"), 0x36, rcItem);
    xpos += (key_width+1);
    rcItem.setCoords(xpos,ypos, xpos+key_width, ypos+key_height);
    addKeyItem((">"), 0x37, rcItem);
    xpos += (key_width+1);
    if (m_kbimagetype == DT_KB_PRO_91 || m_kbimagetype == DT_KB_TE_91)
    {
        rcItem.setCoords(xpos,ypos, xpos+key_width, ypos+key_height);
        addKeyItem(("/"), 0x38, rcItem);
        xpos += (key_width+1);
        rcItem.setCoords(xpos,ypos, xpos+key_width, ypos+key_height);
        addKeyItem(("\\"), 0x87, rcItem);
        xpos += (key_width+1);
        rcItem.setCoords(xpos,ypos, xpos+60, ypos+key_height);
        addKeyItem(("SHIFT"), 0xE5, rcItem);
    }
    else
    {
        rcItem.setCoords(xpos,ypos, xpos+key_width, ypos+key_height);
        addKeyItem("/", 0x38, rcItem);
        xpos += (key_width+1);
        rcItem.setCoords(xpos,ypos, xpos+98, ypos+key_height);
        addKeyItem(("SHIFT"), 0xE5, rcItem);
    }
    xpos = 570;
    xpos += (key_width+1);
    rcItem.setCoords(xpos,ypos, xpos+key_width, ypos+key_height);
    addKeyItem(("↑"), 0x52, rcItem);
    // ctrl
    xpos = 21;
    ypos += key_height;
    rcItem.setCoords(xpos,ypos, xpos+44, ypos+key_height);
    addKeyItem(("CTRL"), 0xE0, rcItem);
    if (m_kbimagetype == DT_KB_PRO_91 || m_kbimagetype == DT_KB_TE_91)
    {
        xpos += (45);
        rcItem.setCoords(xpos,ypos, xpos+key_width, ypos+key_height);
        addKeyItem(("WIN"), 0xE3, rcItem);
        xpos += (key_width+1);
        rcItem.setCoords(xpos,ypos, xpos+44, ypos+key_height);
        addKeyItem(("ALT"), 0xE2, rcItem);
        xpos += (44+1);
        rcItem.setCoords(xpos,ypos, xpos+key_width, ypos+key_height);
        addKeyItem(("無変換"), 139, rcItem);
        xpos += (key_width+1);
        rcItem.setCoords(xpos,ypos, xpos+180, ypos+key_height);
        addKeyItem(("SPACE"), 0x2C, rcItem);
        xpos += (180);
        rcItem.setCoords(xpos,ypos, xpos+key_width, ypos+key_height);
        addKeyItem(("変換"), 0x8a, rcItem);
        xpos += (key_width+1);
        rcItem.setCoords(xpos,ypos, xpos+44, ypos+key_height);
        addKeyItem(("カタカナひらがな"), 0x88, rcItem);
        xpos += (44+1);
        rcItem.setCoords(xpos,ypos, xpos+key_width, ypos+key_height);
        addKeyItem(("ALT"), 0xE6, rcItem);
        xpos += (key_width+1);
        rcItem.setCoords(xpos,ypos, xpos+key_width, ypos+key_height);
        addKeyItem(("FN"), 0xFE, rcItem);
        xpos += (key_width+1);
        rcItem.setCoords(xpos,ypos, xpos+44, ypos+key_height);
        addKeyItem(("CTRL"), 0XE4, rcItem);
        xpos = 570;
        rcItem.setCoords(xpos,ypos, xpos+key_width, ypos+key_height);
        addKeyItem(("←"), 0x50, rcItem);
        xpos += (key_width+1);
        rcItem.setCoords(xpos,ypos, xpos+key_width, ypos+key_height);
        addKeyItem(("↓"), 0x51, rcItem);
        xpos += (key_width+1);
        rcItem.setCoords(xpos,ypos, xpos+key_width, ypos+key_height);
        addKeyItem(("→"), 0x4F, rcItem);
    }
    else
    {
        xpos += (45);
        rcItem.setCoords(xpos,ypos, xpos+44, ypos+key_height);
        addKeyItem(("WIN"), 0xE3, rcItem);
        xpos += (45);
        rcItem.setCoords(xpos,ypos, xpos+44, ypos+key_height);
        addKeyItem(("ALT"), 0xE2, rcItem);
        xpos += (45);
        rcItem.setCoords(xpos,ypos, xpos+224, ypos+key_height);
        addKeyItem(("SPACE"), 0x2C, rcItem);
        xpos += (225);
        rcItem.setCoords(xpos,ypos, xpos+44, ypos+key_height);
        addKeyItem(("ALT"), 0xE6, rcItem);
        xpos += (45);
        rcItem.setCoords(xpos,ypos, xpos+44, ypos+key_height);
        addKeyItem(("MENU"), 0xE7, rcItem);
        xpos += (45);
        rcItem.setCoords(xpos,ypos, xpos+44, ypos+key_height);
        addKeyItem(("FN"), 0xFE, rcItem);
        xpos += (45);
        rcItem.setCoords(xpos,ypos, xpos+44, ypos+key_height);
        addKeyItem(("CTRL"), 0xE4, rcItem);
        xpos = 570;
        rcItem.setCoords(xpos,ypos, xpos+key_width, ypos+key_height);
        addKeyItem(("←"), 0x50, rcItem);
        xpos += (key_width+1);
        rcItem.setCoords(xpos,ypos, xpos+key_width, ypos+key_height);
        addKeyItem(("↓"), 0x51, rcItem);
        xpos += (key_width+1);
        rcItem.setCoords(xpos,ypos, xpos+key_width, ypos+key_height);
        addKeyItem(("→"), 0x4F, rcItem);
    }
    // 侧边背光
    rcItem.setRect(0,0,0,0);
    addKeyItem(("Left Side backlight"), 600, rcItem);
    addKeyItem(("Top Side backlight"), 601, rcItem);
    addKeyItem(("Right Side backlight"), 602, rcItem);
    addKeyItem(("Bottom Side backlight"), 603, rcItem);
}

// 添加键
int QKeyboardCtrl::addKeyItem(QString key_text, int key_value, QRect key_rect)
{
    KEY_INFO* key_info  = new KEY_INFO;
    key_info->key_text  = key_text;
    key_info->key_index = (int)m_vecKey.size();
    key_info->key_value = key_value;
    key_info->key_rect  = key_rect;
    key_info->key_color = QColor(0, 0, 0, 0);
    key_info->key_check = false;

    m_vecKey.push_back(key_info);
    return (int)(m_vecKey.size() - 1);
}
