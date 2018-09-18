#include "ComboBoxItem.h"
#include <QLabel>
#include <QPixmap>
#include <QHBoxLayout>
#include <QPainter>
#include <QDebug>

ComboBoxItem::ComboBoxItem(QWidget *parent):
            QWidget(parent)
{

    m_img = new QLabel(this);
//    QPixmap pic(QStringLiteral(":/img/windows/close_b.png"));

//    m_img->setFixedSize(10,10);

//    pic = pic.scaled(m_img->size(),Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
//    m_img->setPixmap(pic);

    m_label = new QLabel(this);

   m_layout = new QHBoxLayout(this);

   m_layout->addWidget(m_label);
   m_layout->addStretch();
   m_layout->addWidget(m_img);

   m_layout->setSpacing(5);

   m_layout->setContentsMargins(5, 5, 5, 5);

   setLayout(m_layout);
}

void ComboBoxItem::setLabelContent(QString text, int index)
{
    m_label->setText(text);
    m_currentIndex = index;
}

void ComboBoxItem::setImg(QPixmap pic)
{
    m_img->setPixmap(pic);
}

QString ComboBoxItem::getLabelString()
{
    return m_label->text();
}

int ComboBoxItem::getCurrentIndex()
{
    return m_currentIndex;
}

