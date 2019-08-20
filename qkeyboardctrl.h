#ifndef Q_KEYBOARDCTRL_H
#define Q_KEYBOARDCTRL_H

#include <QWidget>
#include <QPixmap>
#include <QEvent>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QVector>

// 键盘控件模式
enum KeyBoardMode
{
    KBM_LIGHT_NONE = 0,
    KBM_LIGHT_STATIC,
    KBM_LIGHT_CUSTOM,
    KBM_CUSTOMKEY = 100,
};
// 按键信息
struct KEY_INFO
{
    int         key_index;
    int         key_value;
    QString     key_text;
    QRect       key_rect;
    QColor      key_color;
    bool        key_check;
};

class QKeyboardCtrl : public QWidget
{
    Q_OBJECT
public:
    explicit QKeyboardCtrl(QWidget *parent = 0);
    ~QKeyboardCtrl();

    // 设置键盘背景
    void setKeyboardBkg(QString bkg_path);
    // 设置键盘类型
    void setKeyboardMode(int kb_mode);

    // 设置按键选中
    void setKeyCheck(int key_value, bool key_check);
    // 设置所有按键状态
    void setAllKeyCheck(bool key_check);

    // 设置按键颜色
    void setKeyColor(int key_value, QColor color);
    // 设置当前选中按键颜色
    void setCheckKeyColor(QColor color);
    // 设置灯光颜色
    void setLightColor(QColor color);
    // 设置按键颜色
    void setAllKeysColor(QColor color);

    // get key list
    QVector<KEY_INFO*> getKeyItems() { return m_vecKey; }
    //  get key info
    KEY_INFO* getKeyInfo(int key_index);

    // 清空所有按键
    void clearAllKeys();

signals:
    void slot_keyboard_mousePressKey(int key_index);

public slots:

protected:
    void enterEvent(QEvent *);
    void leaveEvent(QEvent *);
    void mousePressEvent(QMouseEvent *event);
    //void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
    void paintEvent(QPaintEvent*);

    // 绘制灯光自定义
    void paintLightCustom();
    // 绘制按键自定义
    void paintKeyCustom();

private:
    // 初始化键盘按键
    void initKeyboardKey();
    // 添加键
    int addKeyItem(QString key_text, int key_value, QRect key_rect);

private:
    // 设备类型
    enum DeviceType
    {
        DT_KB_PRO_87 = 1,
        DT_KB_PRO_88 ,
        DT_KB_PRO_89,
        DT_KB_PRO_91,
        DT_KB_TE_87,
        DT_KB_TE_88,
        DT_KB_TE_89,
        DT_KB_TE_91,
        DT_KB_MAX,
    };
    // 键盘图片
    QPixmap             m_pix_kb_bkg;
    int                 m_kb_width;
    int                 m_kb_height;
    int                 m_kbimagetype;
    int                 m_kb_ctrl_mode;

    QColor              m_bkgcolor; // 键盘背景颜色

    int                 m_hover_item;
    int                 m_select_item;

    bool                m_shift_status;

    // 按键链表
    QVector<KEY_INFO*>  m_vecKey;
};

#endif // Q_KEYBOARDCTRL_H
