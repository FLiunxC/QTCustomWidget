#include "ComboBox.h"
#include <QPainter>
#include <QListWidget>
#include <QPaintEvent>
#include<QDebug>
#include "QNoFocusFrameDelegate.h"
#include "HelpClass.h"
#include <QApplication>

ComboBox::ComboBox(QWidget *parent) : QComboBox(parent)
{
    //m_currentItem = tr("Latest Week");
    this->clear();
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

void ComboBox::initComBox(QString StyleSheetback)
{
     if(m_listwidget == nullptr)
     {
          m_listwidget = new QListWidget(this);
          this->setItemDelegate(new QNoFocusFrameDelegate(this));
          this->setModel(m_listwidget->model());
          this->setView(m_listwidget);

          //如果原生有数据则转换为提升控件数据
          int count = this->count();

          for(int i = 0; i < count; i++)
          {
              addItemTextData(this->itemText(i));
          }

          setInitStyleSheet(StyleSheetback);

          connect(m_listwidget, &QListWidget::itemPressed , this, &ComboBox::currentItemClicked_slot);
     }
}

void ComboBox::addItemTextData(QString text, int index)
{
    if(m_listwidget != nullptr){
        ComboBoxItem* item = new ComboBoxItem(this);
        m_comboBoxItemList.append(item);
        item->setItemText(text, index);
        //item->setImg(":/img/windows/close_b.png");
        if(index == 0)
        {
            m_currentItem = text;
        }
        QListWidgetItem* widgetItem = new QListWidgetItem(m_listwidget);
        m_listwidget->setItemWidget(widgetItem, item);
    }
}

void ComboBox::addItemIconTextData(const QString &text, const QString &LeftIcon, const QString &RightIcon, const int index, const QSize &LeftIconsize, const QSize &RightIconsize)
{
    if(m_listwidget != nullptr){
        ComboBoxItem* item = new ComboBoxItem(this);
        m_comboBoxItemList.append(item);
        item->setItemText(text, index);
        item->setLeftIcon(LeftIcon, index, LeftIconsize);
        item->setRightIcon(RightIcon, index, RightIconsize);
        //item->setImg(":/img/windows/close_b.png");
        if(index == 0)
        {
            m_currentItem = text;
        }
        QListWidgetItem* widgetItem = new QListWidgetItem(m_listwidget);
        m_listwidget->setItemWidget(widgetItem, item);
    }
}

void ComboBox::addItemLeftIconText(const QString &text, const QString &LeftIcon, const int index, const QSize &size)
{
    if(m_listwidget != nullptr){
        ComboBoxItem* item = new ComboBoxItem(this);
        m_comboBoxItemList.append(item);
        item->setItemText(text, index);
        item->setLeftIcon(LeftIcon, index, size);
        //item->setImg(":/img/windows/close_b.png");
        if(index == 0)
        {
            m_currentItem = text;
        }
        QListWidgetItem* widgetItem = new QListWidgetItem(m_listwidget);
        m_listwidget->setItemWidget(widgetItem, item);
    }
}

void ComboBox::addItemRightIconText(const QString &text, const QString &RightIcon, const int index, const QSize &size)
{
    if(m_listwidget != nullptr){
        ComboBoxItem* item = new ComboBoxItem(this);
        m_comboBoxItemList.append(item);
        item->setItemText(text, index);
        item->setRightIcon(RightIcon, index, size);
        //item->setImg(":/img/windows/close_b.png");
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

void ComboBox::setCurrentItemIndex(int index)
{
     for(auto comboBoxItem:m_comboBoxItemList)
     {
         if(comboBoxItem)
         {
             int currentIndex = comboBoxItem->getCurrentIndex();
             if(currentIndex == index)
             {
                 m_currentItem = comboBoxItem->getLabelString();
                 this->setCurrentIndex(index);
                 update();
             }

         }
     }
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
        qWarning()<<"ComboBox QSS 加载失败~";
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

void ComboBox::currentItemClicked_slot(QListWidgetItem *currentItem)
{
     QListWidget *list = currentItem->listWidget();
     ComboBoxItem * c = static_cast<ComboBoxItem *>(list->itemWidget(currentItem));
     m_currentItem = c->getLabelString();
     int index = c->getCurrentIndex();
     sigCurrentIndexChange(m_currentItem,index);

     update();
}
