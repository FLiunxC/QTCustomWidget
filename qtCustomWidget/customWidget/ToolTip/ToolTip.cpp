#include "ToolTip.h"
#include "QNGraphicsEffect.h"
#include <QPropertyAnimation>
#include <QDebug>
#include <QFontMetrics>
#include "singleinfo.h"
ToolTip::ToolTip(QWidget *parent) : QLabel(parent)
{
    m_timer = new QTimer(this);
    m_timer->setInterval(m_msec);
    m_timer->setSingleShot(true);

    QNGraphicsEffect * bodyShadow = new QNGraphicsEffect();
    bodyShadow->setBlurRadius(10.0);
    bodyShadow->setDistance(3.0);
    bodyShadow->setColor(QColor(0, 0, 0, 20));

    this->setGraphicsEffect(bodyShadow);
    this->setStyleSheet("background:#ffffff; \
                           border:1px solid #dedede;\
                           border-radius:2px; \
                           color:#656565;");
    this->setAlignment(Qt::AlignCenter);

    connect(m_timer, &QTimer::timeout,this,&ToolTip::hideToolTip);
}

void ToolTip::showToolMessage(QPoint point, QString msg)
{
    if(m_isStartAnimation)
    {
        showToolMessage(msg);
    }
    else
    {
        QFontMetrics fontMetrics(QN_Windows_BetterBoldFont);

        this->setGeometry(point.x(), point.y(), fontMetrics.width(msg),  fontMetrics.height()*1.5);

        this->setText(msg);
        this->show();
        m_timer->start();
    }

}

void ToolTip::showToolMessage(QString msg)
{
    if(m_isStartAnimation)
    {
        Q_ASSERT(m_timer);
        if(m_timer->isActive())
        {
              this->sighide();
              m_timer->stop();
        }
        QFontMetrics fontMetrics(QN_Windows_BetterBoldFont);

        this->setGeometry(m_anmEndPoint.x(), m_anmEndPoint.y(), fontMetrics.width(msg),  fontMetrics.height()*1.5);

        this->setText(msg);

        this->show();
        startAnimation();
    }

    m_isStartAnimation = false;
}

void ToolTip::setToolTipDelay(int msec)
{
    m_msec = msec;
    if(m_timer != nullptr)
    {
        m_timer->setInterval(m_msec);
    }
}

void ToolTip::setAnimationPopupPosition(QPoint startPoint, QPoint endPoint, bool isStart)
{
     m_isStartAnimation = isStart;
     m_animStartPoint = startPoint;
     m_anmEndPoint = endPoint;
}

int ToolTip::getToolTipWidth(QString message)
{
    QFontMetrics fontMetrics(QN_Windows_BetterBoldFont);
    return fontMetrics.width(message);
}

void ToolTip::endAnimation()
{
    if(m_animation == nullptr)
    {
        m_animation = new QPropertyAnimation(this, "pos");
    }
    if(m_animation->state()== QAbstractAnimation::Running)
    {
        m_animation->stop();
    }

    m_animation->setDuration(200);

    m_animation->setStartValue(m_anmEndPoint);
    m_animation->setEndValue(m_animStartPoint);

    m_isStart = false;
    m_animation->start();

    connect(m_animation, &QPropertyAnimation::finished, [=]{
            Q_ASSERT(m_timer);
            if(m_timer != nullptr)
            {
                m_timer->start();
            }
    });

}

void ToolTip::startAnimation()
{
    if(m_animation == nullptr)
    {
        m_animation = new QPropertyAnimation(this, "pos");
    }

    if(m_animation->state()== QAbstractAnimation::Running)
    {
        m_animation->stop();
    }

    m_animation->setDuration(400);

    m_animation->setStartValue(m_animStartPoint);
    m_animation->setEndValue(m_anmEndPoint);

    m_isStart = true;
    m_animation->start();
    connect(m_animation, &QPropertyAnimation::finished, [=]{
            Q_ASSERT(m_timer);
            if(m_timer != nullptr)
            {
                m_timer->start();
            }
    });
}

void ToolTip::hideToolTip()
{
    if(m_isStart)
    {
          endAnimation();
    }
    else
    {
          this->sighide();
    }

}
