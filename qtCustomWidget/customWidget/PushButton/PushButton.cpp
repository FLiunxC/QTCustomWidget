#include "PushButton.h"
#include <QPainter>
#include <QString>

PushButton::PushButton(QWidget *parent) : QPushButton(parent)
{

}

void PushButton::initDefaultStyleSheet()
{
    this->setObjectName("pButtonOk");
    this->setStyleSheet(QString("QPushButton{outline:0px;"
                        "border:0px;"
                        "}"
                        "QPushButton#pButtonOk  \
                        { \
                            color:white; \
                            background-color:%1; \
                            border: 1px solid rgb(11 , 137 , 234); \
                        } \
                        QPushButton#pButtonOk:hover \
                        { \
                            color:white;   \
                            background-color:rgb(44 , 137 , 255); \
                            border: 1px solid rgb(11 , 137 , 234); \
                        } \
                        ").arg(m_backgroundColor));
}

void PushButton::setClickEffect(bool clickEffect)
{
    m_isClickEffect = clickEffect;
}

void PushButton::setBackgroundImage(QString imgPath)
{
    m_backGroundImage = imgPath;
    this->setIcon(QIcon(QPixmap(m_backGroundImage)));
    this->setIconSize(this->size());
}

void PushButton::setButtonTransparency(bool isTransparency)
{
     this->setStyleSheet("QPushButton \
    { \
        color:white; \
        background-color:#00000000; \
        border: 0px solid rgb(11 , 137 , 234); \
    } "
     );
}


void PushButton::mousePressEvent(QMouseEvent *e)
{
    if(m_isClickEffect){
        pressClickStyleSheet();
    }
     e->accept();
}

void PushButton::mouseReleaseEvent(QMouseEvent *e)
{
    sigClick();
    sigClick(m_isClickSecond);
    if(m_isClickEffect){
         releaseClickStyleSheet();
    }

    m_isClickSecond = !m_isClickSecond;

    e->accept();
}

void PushButton::pressClickStyleSheet()
{

    this->setStyleSheet("  QPushButton#pButtonOk  \
    {  \
        color:white;  \
        background-color:rgb(14 , 135 , 228); \
        border: 1px solid rgb(12 , 138 , 235);  \
        padding-left:3px; \
        padding-top:3px; \
    }");
}

void PushButton::releaseClickStyleSheet()
{
    this->setStyleSheet("QPushButton#pButtonOk  \
    {  \
        color:white;  \
        background-color:rgb(14 , 135 , 228); \
        border: 1px solid rgb(12 , 138 , 235);  \
        padding-left:0px; \
        padding-top:0px; \
                        }");
}

void PushButton::setBackgroundColor(QString backgroundColor)
{
    if (m_backgroundColor == backgroundColor)
        return;

    m_backgroundColor = backgroundColor;
    initDefaultStyleSheet();
}

void PushButton::enterEvent(QEvent *event)
{
    this->setCursor(Qt::PointingHandCursor);
    event->accept();
}

void PushButton::leaveEvent(QEvent *event)
{
    this->setCursor(Qt::ArrowCursor);
    event->accept();
}
