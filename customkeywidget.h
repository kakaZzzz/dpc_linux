#ifndef CUSTOMKEYWIDGET_H
#define CUSTOMKEYWIDGET_H

#include <QWidget>
#include <QTreeWidgetItem>
#include "qkeyboardctrl.h"

namespace Ui {
class CustomKeyWidget;
}

class CustomKeyWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CustomKeyWidget(QWidget *parent = 0);
    ~CustomKeyWidget();

protected:

     //  init control ui
    void initUI();

    //  load db data
    void loadDBdata();

    // update macro data
    void updataMacroData();

    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);


    QKeyboardCtrl*          m_keyboard_ctrl;

private slots:
    void on_treeWidget_key_itemPressed(QTreeWidgetItem *item, int column);

    // keybaord control message
    void on_keyboard_key_pressed(int key_index);

    void on_pushButton_save_clicked();

    void on_pushButton_cancel_clicked();

private:
    Ui::CustomKeyWidget *ui;

    int                                                     m_cur_key_value;
    int                                                     m_macro_type;
    int                                                     m_macro_value;
    QString                                            m_macro_desc;
    QVector<QTreeWidgetItem*>     m_vec_tree;

    void clearTreeList();
};

#endif // CUSTOMKEYWIDGET_H
