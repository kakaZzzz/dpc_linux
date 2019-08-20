#ifndef QTKEYBOARDKEY_H
#define QTKEYBOARDKEY_H

#include <QString>

struct KeyInfo
{
    int             key_value;
    QString    ket_text;
};
class QtKeyBoardKey
{
public:
    QtKeyBoardKey();

    //  get sys key list
    static void getSysKeyList(QVector<KeyInfo> &vecdata);

    // get all key list
   static  void getAllKeyList(QVector<KeyInfo> &vecdata);

   // get key hid value
   static int getFlashCode(int qt_key);

};

#endif // QTKEYBOARDKEY_H
