#include "ComboBoxItem.h"
#include <QLabel>
#include <QPixmap>
#include <QHBoxLayout>
#include <QPainter>
#include <QDebug>

ComboBoxItem::ComboBoxItem(QWidget *parent):
            QWidget(parent)
{

    initUILayout();

}

void ComboBoxItem::setItemText(QString text, int index)
{
    m_layout->removeItem(m_HspacerItemEnd);

    if(m_comboxText == nullptr)
    {
        m_comboxText = new QLabel(this);
        m_comboxText->setObjectName("comboxText");
    }

    m_comboxText->setText(text);
    m_layout->insertWidget(2, m_comboxText);
    m_layout->addSpacerItem(m_HspacerItemEnd);
    setCurrentIndex(index);
}

void ComboBoxItem::setLeftIcon(const QString &LiconPath, int index, QSize iconSize)
{
    m_layout->removeItem(m_HspacerItemEnd);
    if(m_comboxLeftIcon == nullptr)
    {
        m_comboxLeftIcon = new QLabel(this);
        m_comboxLeftIcon->setObjectName("comboxLIcon");
    }

    if(!iconSize.isEmpty())
    {
        setIconMaxAndMinValue(m_comboxLeftIcon, iconSize);
    }

    m_comboxLeftIcon->setStyleSheet("#comboxLIcon { background-position:center; background-repeat:no_repeat; image: url("+LiconPath+");}");

    m_layout->insertWidget(1, m_comboxLeftIcon);
    m_layout->addSpacerItem(m_HspacerItemEnd);

    setCurrentIndex(index);

}

void ComboBoxItem::setRightIcon(const QString &RiconPath, int index, QSize iconSize)
{
    m_layout->removeItem(m_HspacerItemEnd);

    if(m_comboxRightIcon == nullptr)
    {
        m_comboxRightIcon = new QLabel(this);
        m_comboxRightIcon->setObjectName("comboxRIcon");
    }

    if(!iconSize.isEmpty())
    {
        setIconMaxAndMinValue(m_comboxRightIcon, iconSize);
    }
    m_comboxRightIcon->setStyleSheet("#comboxRIcon { image: url("+RiconPath+");}");
    m_layout->insertWidget(3, m_comboxRightIcon);
    m_layout->addSpacerItem(m_HspacerItemEnd);

    setCurrentIndex(index);
}

QString ComboBoxItem::getLabelString()
{
    return m_comboxText->text();
}

int ComboBoxItem::getCurrentIndex()
{
    return m_currentIndex;
}

void ComboBoxItem::setCurrentIndex(int currentIndex)
{
    if(currentIndex < 0)
    {
         return;
    }

    m_currentIndex = currentIndex;
}

void ComboBoxItem::initUILayout()
{
    QSizePolicy  sizePolicy(QSizePolicy::Preferred,QSizePolicy::Preferred);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(this->sizePolicy().hasHeightForWidth());
    this->setSizePolicy(sizePolicy);

    m_layout = new QHBoxLayout(this);

    //加弹簧
    m_HspacerItemStart = new QSpacerItem(20, 20, QSizePolicy::Expanding);
    m_layout->addSpacerItem(m_HspacerItemStart);

    //加弹簧
    m_HspacerItemEnd = new QSpacerItem(20, 20, QSizePolicy::Expanding);
    m_layout->addSpacerItem(m_HspacerItemEnd);

    m_layout->setContentsMargins(0,0,0,0);
    m_layout->setSpacing(10);
}

void ComboBoxItem::setIconMaxAndMinValue(QWidget *widget, const QSize &size)
{
    //设置最大值
    widget->setMaximumWidth(size.width());
    widget->setMaximumHeight(size.height());

    //设置最小值
    widget->setMinimumWidth(size.width());
    widget->setMinimumHeight(size.height());

}

