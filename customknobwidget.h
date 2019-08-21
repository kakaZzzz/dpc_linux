#ifndef CUSTOMKNOBWIDGET_H
#define CUSTOMKNOBWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QTreeWidgetItem>
#include "custombutton.h"

namespace Ui {
class CustomKnobWidget;
}

class CustomKnobWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CustomKnobWidget(QWidget *parent = 0);
    ~CustomKnobWidget();

protected:

     //  init control ui
    void initUI();

    //  load db data
    void loadDBdata();

    // update macro data
    void updataMacroData();

    // get knob macro
    void getMacrodata();

    tabButton*                       m_knob_single;
    tabButton*                       m_knob_double;
    tabButton*                       m_knob_forward;
    tabButton*                       m_knob_backward;

    QLabel*                            m_label_knob;

private slots:
    void slot_click_knob_single();
    void slot_click_knob_double();
    void slot_click_knob_forward();
    void slot_click_knob_backward();

    void on_treeWidget_knob_itemPressed(QTreeWidgetItem *item, int column);

    void on_pushButton_save_clicked();

    void on_pushButton_cancel_clicked();

private:
    Ui::CustomKnobWidget *ui;

    int                                                     m_cur_key_value;
    int                                                     m_macro_type;
    int                                                     m_macro_value;
    QString                                            m_macro_desc;
    QVector<QTreeWidgetItem*>     m_vec_tree;

    void clearTreeList();
};

#endif // CUSTOMKNOBWIDGET_H
