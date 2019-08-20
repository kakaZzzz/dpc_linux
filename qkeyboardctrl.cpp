#include "qkeyboardctrl.h"

#include <QPushButton>
#include <QPainter>
#include <QDebug>

QKeyboardCtrl::QKeyboardCtrl(QWidget *parent)
    : QWidget(parent)
{
    m_kb_width      = 0;
    m_kb_height     = 0;

    m_kbimagetype   = DT_KB_PRO_87;
    m_kb_ctrl_mode  = KBM_LIGHT_NONE;

    m_bkgcolor      = QColor(255, 225, 0);

    m_hover_item    = -1;
    m_select_item   = -1;

    m_shift_status  = false;

    // 激活鼠标移动消息
    setMouseTracking(true);
    //grabKeyboard();
    // 初始化键盘按键
    initKeyboardKey();
}

QKeyboardCtrl::~QKeyboardCtrl()
{
    // 清空所有按键
    clearAllKeys();
}

// 设置键盘背景
void QKeyboardCtrl::setKeyboardBkg(QString bkg_path)
{
    m_pix_kb_bkg.load(bkg_path);
    m_kb_width = m_pix_kb_bkg.width();
    m_kb_height = m_pix_kb_bkg.height();
}

// 设置键盘类型
void QKeyboardCtrl::setKeyboardMode(int kb_mode)
{
    m_kb_ctrl_mode = kb_mode;
}

// 设置按键选中
void QKeyboardCtrl::setKeyCheck(int key_value, bool key_check)
{
    int key_count = m_vecKey.size();
    for (int i = 0; i < key_count; i++)
    {
        KEY_INFO* key_info = m_vecKey.at(i);
        if (key_info && key_info->key_value == key_value)
        {
            key_info->key_check = key_check;
            break;
        }
    }
}

// 设置所有按键状态
void QKeyboardCtrl::setAllKeyCheck(bool key_check)
{
    int key_count = m_vecKey.size();
    for (int i = 0; i < key_count; i++)
    {
        KEY_INFO* key_info = m_vecKey.at(i);
        if (key_info)
            key_info->key_check = key_check;
    }
}

// 设置按键颜色
void QKeyboardCtrl::setKeyColor(int key_value, QColor color)
{
    int key_count = m_vecKey.size();
    for (int i = 0; i < key_count; i++)
    {
        KEY_INFO* key_info = m_vecKey.at(i);
        if (key_info && key_info->key_value == key_value)
        {
            key_info->key_color = color;
            break;
        }
    }
}

// 设置当前选中按键颜色
void QKeyboardCtrl::setCheckKeyColor(QColor color)
{
    int key_count = m_vecKey.size();
    for (int i = 0; i < key_count; i++)
    {
        KEY_INFO* key_info = m_vecKey.at(i);
        if (key_info && key_info->key_check)
        {
            key_info->key_color = color;
        }
    }
    update();
}

// 设置灯光颜色
void QKeyboardCtrl::setLightColor(QColor color)
{
    m_bkgcolor = color;
    update();
}

// 设置按键颜色
void QKeyboardCtrl::setAllKeysColor(QColor color)
{
    int key_count = m_vecKey.size();
    for (int i = 0; i < key_count; i++)
    {
        KEY_INFO* key_info = m_vecKey.at(i);
        if (key_info)
            key_info->key_color = color;
    }
    update();
}

//  get key info
KEY_INFO* QKeyboardCtrl::getKeyInfo(int key_index)
{
    return m_vecKey.at(key_index);
}

// 清空所有按键
void QKeyboardCtrl::clearAllKeys()
{
    int key_count = m_vecKey.size();
    for (int i = 0; i < key_count; i++)
    {
        KEY_INFO* key_info = m_vecKey.at(i);
        if (key_info)
        {
            delete key_info;
            key_info = NULL;
        }
    }
    m_vecKey.clear();
}

void QKeyboardCtrl::enterEvent(QEvent *)
{
    if (m_kb_ctrl_mode == KBM_LIGHT_NONE || m_kb_ctrl_mode == KBM_LIGHT_STATIC)
        return ;

    m_hover_item = -1;
    update();
}
void QKeyboardCtrl::leaveEvent(QEvent *)
{
    if (m_kb_ctrl_mode == KBM_LIGHT_NONE || m_kb_ctrl_mode == KBM_LIGHT_STATIC)
        return ;

    m_hover_item = -1;
    update();
}
void QKeyboardCtrl::mousePressEvent(QMouseEvent *event)
{
    if (m_kb_ctrl_mode == KBM_LIGHT_NONE || m_kb_ctrl_mode == KBM_LIGHT_STATIC)
        return ;

    setFocus();

    int old_select_item = m_select_item;
    if (m_hover_item != -1)
    {
        m_select_item = m_hover_item;
        if (m_kb_ctrl_mode == KBM_CUSTOMKEY)
        {
             emit slot_keyboard_mousePressKey(m_select_item);
        }
        else if (m_kb_ctrl_mode == KBM_LIGHT_CUSTOM)
        {
            if (m_shift_status == false)
            {
                qDebug() << "m_shift_status = " << m_shift_status;
                // 设置所有按键状态
                setAllKeyCheck(false);
            }

            KEY_INFO* key_info = m_vecKey.at(m_select_item);
            if (key_info && key_info->key_rect.contains(event->pos()))
            {
                key_info->key_check = true;
            }

            update();
            return;
        }
    }
    if (old_select_item != m_select_item)
    {
        update();
    }
}

//void QKeyboardCtrl::mouseReleaseEvent(QMouseEvent *event)
//{
//    if (m_kb_ctrl_mode == KBM_LIGHT_NONE || m_kb_ctrl_mode == KBM_LIGHT_STATIC)
//        return ;
//}

void QKeyboardCtrl::mouseMoveEvent(QMouseEvent *event)
{
    if (m_kb_ctrl_mode == KBM_LIGHT_NONE || m_kb_ctrl_mode == KBM_LIGHT_STATIC)
        return ;

    int old_hover_item = m_hover_item;
    if (m_hover_item != -1)
    {
        KEY_INFO* key_info = m_vecKey.at(m_hover_item);
        if (key_info && key_info->key_rect.contains(event->pos()))
        {
            return ;
        }
        m_hover_item = -1;
    }
    if (m_hover_item == -1)
    {
        int keyCount = m_vecKey.size();
        for (int i = 0; i < keyCount; i++)
        {
            KEY_INFO* key_info = m_vecKey.at(i);
            if (key_info == NULL)
                continue ;

            if (key_info->key_rect.contains(event->pos()))
            {
                m_hover_item = i;
                break;
            }
        }
    }
    if (old_hover_item != m_hover_item)
    {
        update();
    }
}

void QKeyboardCtrl::keyPressEvent(QKeyEvent *event)
{
     qDebug() << event->key();
    if (event->key() == Qt::Key_Shift)
    {
        m_shift_status = true;
        qDebug() << "m_shift_status = true;" << m_kb_ctrl_mode;
    }
}

void QKeyboardCtrl::keyReleaseEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Shift)
    {
        m_shift_status = false;
        qDebug() << "m_shift_status = false;" << m_kb_ctrl_mode;
    }
}

void QKeyboardCtrl::paintEvent(QPaintEvent*)
{
    if (m_kb_ctrl_mode == KBM_LIGHT_NONE || m_kb_ctrl_mode == KBM_LIGHT_STATIC)
    {
        QPainter painter(this);
        // 绘制矩形
        QBrush brush(m_bkgcolor);
        painter.fillRect(QRect(20, 10, m_kb_width - 40, m_kb_height - 20), brush);

        if (m_kb_width > 10 && m_kb_height > 10)
        {
            painter.drawPixmap(0, 0, m_kb_width, m_kb_height, m_pix_kb_bkg);
        }
    }
    else if (m_kb_ctrl_mode == KBM_LIGHT_CUSTOM)
    {
        paintLightCustom();
    }
    else if (m_kb_ctrl_mode == KBM_CUSTOMKEY)
    {
        paintKeyCustom();
    }
}

// 绘制灯光自定义
void QKeyboardCtrl::paintLightCustom()
{
    QPainter painter(this);

    int keyCount = m_vecKey.size();
    for (int i = 0; i < keyCount; i++)
    {
        KEY_INFO* key_info = m_vecKey.at(i);
        if (key_info && key_info->key_color.alpha() != 0)
        {
            painter.fillRect(key_info->key_rect.left() + 1,
                             key_info->key_rect.top(),
                             key_info->key_rect.width() - 2,
                             key_info->key_rect.height() - 6,
                             QBrush(key_info->key_color));
        }
    }

    if (m_kb_width > 10 && m_kb_height > 10)
    {
        painter.drawPixmap(0, 0, m_kb_width, m_kb_height, m_pix_kb_bkg);
    }

    QPen pen(QColor(255,225,0), 2, Qt::SolidLine);

    // 绘制鼠标选择效果
    painter.setPen(pen);
    for (int i = 0; i < keyCount; i++)
    {
        KEY_INFO* key_info = m_vecKey.at(i);
        if (key_info && key_info->key_check)
        {
            //绘制一个矩形
            painter.drawRect(key_info->key_rect.left(),
                             key_info->key_rect.top(),
                             key_info->key_rect.width(),
                             key_info->key_rect.height());
        }
    }
}

void QKeyboardCtrl::paintKeyCustom()
{
    QPainter painter(this);

    // 绘制鼠标滑过
    if (m_hover_item != -1)
    {
        KEY_INFO* key_info = m_vecKey.at(m_hover_item);
        if (key_info)
        {
            painter.fillRect(key_info->key_rect.left() + 1,
                             key_info->key_rect.top(),
                             key_info->key_rect.width() - 2,
                             key_info->key_rect.height() - 6,
                             QBrush(QColor(255,225,0)));
        }
    }

    if (m_kb_width > 10 && m_kb_height > 10)
    {
        painter.drawPixmap(0, 0, m_kb_width, m_kb_height, m_pix_kb_bkg);
    }

    QPen pen(QColor(51,51, 51), 1, Qt::SolidLine);

    // 绘制鼠标选择效果
    painter.setPen(pen);
    if (m_select_item != -1)
    {
        KEY_INFO* key_info = m_vecKey.at(m_select_item);
        if (key_info)
        {
            painter.fillRect(key_info->key_rect.left() + 1,
                             key_info->key_rect.top() ,
                             key_info->key_rect.width() - 2,
                             key_info->key_rect.height() - 2,
                             QBrush(QColor(255,255,255,150)));

            //绘制一个矩形
            painter.drawRect(key_info->key_rect.left() + 2,
                             key_info->key_rect.top() + 2,
                             key_info->key_rect.width() - 5,
                             key_info->key_rect.height() - 5);
        }
    }

    // 绘制鼠标选中效果
    painter.setPen(pen);
    int keyCount = m_vecKey.size();
    for (int i = 0; i < keyCount; i++)
    {
        KEY_INFO* key_info = m_vecKey.at(i);
        if (key_info && key_info->key_check)
        {
            painter.fillRect(key_info->key_rect.left() + 1,
                             key_info->key_rect.top(),
                             key_info->key_rect.width() - 2,
                             key_info->key_rect.height() - 2,
                             QBrush(QColor(255,225,0,150)));

            //绘制一个矩形
            painter.drawRect(key_info->key_rect.left() + 2,
                             key_info->key_rect.top() + 2,
                             key_info->key_rect.width() - 5,
                             key_info->key_rect.height() - 5);
        }
    }
}
