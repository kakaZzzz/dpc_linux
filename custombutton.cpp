#include "custombutton.h"

#include <QPainter>
#include <QDebug>

tabButton::tabButton(QString image_path, QWidget *parent, QString text)
                    :QPushButton(parent)
{
    this->setCursor(Qt::PointingHandCursor);
    m_index = 0;
    m_enter = false;
    m_check = false;
    m_text  = text;
    QPixmap pix(image_path);
    for (int i = 0; i < 4; i++)
    {
        m_list_pixmap << pix.copy(i * pix.width()/4, 0, pix.width()/4, pix.height());
    }
}

tabButton::~tabButton()
{

}

// set tab check
void tabButton::setTabCheck(bool check)
{
    m_check = check;
    update();
}

void tabButton::enterEvent(QEvent*)
{
    m_index = 1;
    m_enter = true;
    update();
}

void tabButton::leaveEvent(QEvent*)
{
    m_index = 0;
    m_enter = false;
    update();
}

void tabButton::paintEvent(QPaintEvent* e)
{
    QPainter painter(this);

    if (m_check)
    {
        painter.drawPixmap((width()-m_list_pixmap.at(3).width())/2,
                           (height()-m_list_pixmap.at(m_index).height())/2,
                           m_list_pixmap.at(3).width(),
                           m_list_pixmap.at(3).height(),
                           m_list_pixmap.at(3));
    }
    else
    {
        painter.drawPixmap((width()-m_list_pixmap.at(m_index).width())/2,
                           (height()-m_list_pixmap.at(m_index).height())/2,
                           m_list_pixmap.at(m_index).width(),
                           m_list_pixmap.at(m_index).height(),
                           m_list_pixmap.at(m_index));
    }

    if (!m_text.isEmpty())
    {
        painter.setPen(QColor(51, 51, 51));
        QFont font;
        QFontMetrics metric(font);
        int text_width = metric.width(m_text);
        painter.drawText((width() - text_width)/2, 32, m_text);
        //QPushButton::paintEvent(e);
    }
}

void tabButton::mousePressEvent(QMouseEvent *e)
{
    if (e->button() == Qt::LeftButton)
    {
        m_index = 2;
        update();
        QPushButton::mousePressEvent(e);
    }
}

void tabButton::mouseReleaseEvent(QMouseEvent *e)
{
    if (e->button() == Qt::LeftButton)
    {
        m_index = 1;
        update();
        QPushButton::mouseReleaseEvent(e);
    }
}
