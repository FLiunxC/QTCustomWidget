#include "ComboBox.h"
#include <QPainter>
#include <QListWidget>
#include <ComboBoxItem.h>
#include <QPaintEvent>
#include<QDebug>
#include "QNoFocusFrameDelegate.h"
#include "HelpClass.h"
#include <QApplication>

ComboBox::ComboBox(QWidget *parent) : QComboBox(parent)
{
    m_currentItem = tr("Latest Week");
    m_update = true;
}

void ComboBox::paintEvent(QPaintEvent *e)
{
      QComboBox::paintEvent(e);

      QRect rect = e->rect();

       rect.setX(rect.x()+5);

       if(m_update)
       {
           m_rect = rect;
      //     setUpdate();
           m_update = false;
       }

       QPainter paint(this);

       paint.setRenderHint(QPainter::Antialiasing);
       //绘制文字
       paint.drawText(m_rect, Qt::AlignLeft|Qt::AlignVCenter, m_currentItem);

}

void ComboBox::initComBox()
{
     if(m_listwidget == nullptr)
     {
          m_listwidget = new QListWidget(this);
          this->setItemDelegate(new QNoFocusFrameDelegate(this));
          this->setModel(m_listwidget->model());
          this->setView(m_listwidget);
     }

     connect(m_listwidget, &QListWidget::currentItemChanged , this, &ComboBox::currentItemChanged_slot);

}

void ComboBox::addItemTextData(QString text, int index)
{
    if(m_listwidget != nullptr){
        ComboBoxItem* item = new ComboBoxItem(this);
        item->setLabelContent(text, index);
        if(index == 0)
        {
            m_currentItem = text;
        }
        QListWidgetItem* widgetItem = new QListWidgetItem(m_listwidget);
        m_listwidget->setItemWidget(widgetItem, item);
    }
}

void ComboBox::setCurrentItem(QString item)
{
    m_currentItem = item;
}

void ComboBox::setBackgroundColor(QString color)
{
    m_backGroundColor = color;

    this->setProperty("boxbackground", m_backGroundColor);
    this->setStyle(QApplication::style());

    m_update = true;
}

void ComboBox::setFontColor(QString fontColor)
{
    m_fontColor = fontColor;
    m_update = true;
}

void ComboBox::setInitStyleSheet(QString background)
{
    QString styleSheet = HelpClass::loaderQSSFile("ComboBox");

    if(styleSheet.isEmpty())
    {
        qInfo()<<"加载失败~";
    }
    this->setProperty("boxbackground", background);
    this->setStyleSheet(styleSheet);
    this->setStyle(QApplication::style());
}


void ComboBox::mouseMoveEvent(QMouseEvent *event)
{
    event->accept();
}

void ComboBox::enterEvent(QEvent *event)
{
    this->setCursor(Qt::PointingHandCursor);
    event->accept();
}

void ComboBox::leaveEvent(QEvent *event)
{
     this->setCursor(Qt::ArrowCursor);
    event->accept();
}


void ComboBox::currentItemChanged_slot(QListWidgetItem *current, QListWidgetItem *previous)
{
     QListWidget *list = current->listWidget();
     ComboBoxItem * c = static_cast<ComboBoxItem *>(list->itemWidget(current));
     m_currentItem = c->getLabelString();
     int index = c->getCurrentIndex();
     sigCurrentIndexChange(m_currentItem,index);

     update();
}
