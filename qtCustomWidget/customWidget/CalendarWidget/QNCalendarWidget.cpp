#include "QNCalendarWidget.h"

#include <QLocale>
#include <QPainter>
#include <QTextCharFormat>
#include <QProxyStyle>
#include <QTableView>
#include <QLayout>
#include <QPushButton>
#include <QLabel>
#include "QNGraphicsEffect.h"

class QCustomStyle : public QProxyStyle
{
public:
    QCustomStyle(QWidget *parent){
        setParent(parent);
    }

private:
    void drawPrimitive(PrimitiveElement element, const QStyleOption *option,
        QPainter *painter, const QWidget *widget) const
    {
        if (element == PE_FrameFocusRect)
        {
            return;
        }
        QProxyStyle::drawPrimitive(element, option, painter, widget);
    }
};

QNCalendarWidget::QNCalendarWidget(QWidget *parent) : QCalendarWidget(parent)
{
      initControl();
}

void QNCalendarWidget::initControl()
{
        //设置阴影效果
        QNGraphicsEffect * bodyShadow = new QNGraphicsEffect();
        bodyShadow->setBlurRadius(15.0);
        bodyShadow->setDistance(4.0);
        bodyShadow->setColor(QColor(0, 0, 0, 80));
        this->setGraphicsEffect(bodyShadow);

        //设置控件对象名称
        this->setObjectName("CustCalendar");
        layout()->setSizeConstraint(QLayout::SetFixedSize);
        setLocale(QLocale(QLocale::Chinese));
        setNavigationBarVisible(false);
        setVerticalHeaderFormat(QCalendarWidget::NoVerticalHeader);
        setHorizontalHeaderFormat(QCalendarWidget::SingleLetterDayNames);
        setStyle(new QCustomStyle(this));
   //     this->setStyleSheet("QWidget#CustCalendar{background-color: white;border: 1px solid rgb(217,217,217);}");
        QTextCharFormat format;
        format.setForeground(QColor(160, 160, 160));
        format.setBackground(QColor(255, 255, 255));

        setHeaderTextFormat(format);
        setWeekdayTextFormat(Qt::Saturday, format); //周六
        setWeekdayTextFormat(Qt::Sunday,   format); //周日
        format.setForeground(QColor(51,51,51));
        setWeekdayTextFormat(Qt::Monday,   format);
        setWeekdayTextFormat(Qt::Tuesday,  format);
        setWeekdayTextFormat(Qt::Wednesday,format);
        setWeekdayTextFormat(Qt::Thursday, format);
        setWeekdayTextFormat(Qt::Friday,   format);

        initTopWidget();
//        initBottomWidget();

        connect(this, &QCalendarWidget::currentPageChanged, [this](int year, int month){
            setDataLabelTimeText(year, month);
        });

        connect(this, &QNCalendarWidget::activated,this, &QNCalendarWidget::signalSetCalendarTime);
}

void QNCalendarWidget::initTopWidget()
{
       QWidget* topWidget = new QWidget(this);
       topWidget->setObjectName("CalendarTopWidget");
       topWidget->setFixedHeight(40);
       topWidget->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
       topWidget->setStyleSheet("QWidget#CalendarTopWidget{background-color: white;border-bottom: 1px solid rgb(217,217,217); }");
       QHBoxLayout* hboxLayout = new QHBoxLayout;
       hboxLayout->setContentsMargins(12, 0, 12, 0);
       hboxLayout->setSpacing(4);

       m_leftYearBtn   = new QPushButton(this);
       m_leftMonthBtn  = new QPushButton(this);
       m_rightYearBtn  = new QPushButton(this);
       m_rightMonthBtn = new QPushButton(this);
       m_dataLabel     = new QLabel(this);

       m_dataLabel->setStyleSheet("background-color: white;border-bottom: 1px solid rgb(217,217,217);");
       m_leftYearBtn->setObjectName("CalendarLeftYearBtn");
       m_leftMonthBtn->setObjectName("CalendarLeftMonthBtn");
       m_rightYearBtn->setObjectName("CalendarRightYearBtn");
       m_rightMonthBtn->setObjectName("CalendarRightMonthBtn");
       m_dataLabel->setObjectName("CalendarDataLabel");

       m_leftYearBtn->setFixedSize(16, 16);
       m_leftMonthBtn->setFixedSize(16, 16);
       m_rightYearBtn->setFixedSize(16, 16);
       m_rightMonthBtn->setFixedSize(16, 16);

       m_leftYearBtn->setIcon(QIcon(":/img/windows/year_left.png"));
       m_leftYearBtn->setFlat(true);
       m_leftMonthBtn->setIcon(QIcon(":/img/windows/month_left.png"));
       m_leftMonthBtn->setFlat(true);

       m_rightYearBtn->setIcon(QIcon(":/img/windows/year_right.png"));
       m_rightYearBtn->setFlat(true);
       m_rightMonthBtn->setIcon(QIcon(":/img/windows/month_right.png"));
       m_rightMonthBtn->setFlat(true);



       hboxLayout->addWidget(m_leftYearBtn);
       hboxLayout->addWidget(m_leftMonthBtn);
       hboxLayout->addStretch();
       hboxLayout->addWidget(m_dataLabel);
       hboxLayout->addStretch();
       hboxLayout->addWidget(m_rightMonthBtn);
       hboxLayout->addWidget(m_rightYearBtn);
       topWidget->setLayout(hboxLayout);

       //这里见下图1
       QVBoxLayout *vBodyLayout = qobject_cast<QVBoxLayout *>(layout());
       vBodyLayout->insertWidget(0, topWidget);

       connect(m_leftYearBtn,   SIGNAL(clicked()),  this, SLOT(onbtnClicked()));
       connect(m_leftMonthBtn,  SIGNAL(clicked()),  this, SLOT(onbtnClicked()));
       connect(m_rightYearBtn,  SIGNAL(clicked()),  this, SLOT(onbtnClicked()));
       connect(m_rightMonthBtn, SIGNAL(clicked()),  this, SLOT(onbtnClicked()));

       setDataLabelTimeText(selectedDate().year(), selectedDate().month());
}

void QNCalendarWidget::initBottomWidget()
{
    QWidget* bottomWidget = new QWidget(this);
      bottomWidget->setObjectName("CalendarBottomWidget");
      bottomWidget->setFixedHeight(40);
      bottomWidget->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);

      QHBoxLayout* hboxLayout = new QHBoxLayout;
      hboxLayout->setContentsMargins(12, 0, 12, 0);
      hboxLayout->setSpacing(6);

      m_ensureBtn = new QPushButton(this);
      m_ensureBtn->setObjectName("CalendarEnsureBtn");
      m_ensureBtn->setFixedSize(40, 22);
      m_ensureBtn->setText(QStringLiteral("确定"));

      m_toDayBtn = new QPushButton(this);
      m_toDayBtn->setObjectName("CalendarTodayBtn");
      m_toDayBtn->setFixedSize(40, 22);
      m_toDayBtn->setText(QStringLiteral("现在"));

      hboxLayout->addStretch();
      hboxLayout->addWidget(m_toDayBtn);
      hboxLayout->addWidget(m_ensureBtn);
      bottomWidget->setLayout(hboxLayout);

      //这里见下图1
      QVBoxLayout *vBodyLayout = qobject_cast<QVBoxLayout *>(layout());
      vBodyLayout->addWidget(bottomWidget);

      connect(m_ensureBtn, &QPushButton::clicked, [this](){
          emit signalSetCalendarTime(selectedDate());
          emit activated(selectedDate());
      });

      connect(m_toDayBtn, &QPushButton::clicked, [this](){
          showToday();
      });
}

void QNCalendarWidget::setDataLabelTimeText(int year, int month)
{
    QString yearStr = tr("Year");
    QString monthStr = tr("Month");

    m_dataLabel->setText(QStringLiteral("%1 %2 %3 %4").arg(year).arg(yearStr).arg(month).arg(monthStr));
}

void QNCalendarWidget::mouseDoubleClickEvent(QMouseEvent *event)
{
    event->accept();
}

void QNCalendarWidget::mousePressEvent(QMouseEvent *event)
{
    event->accept();
}

void QNCalendarWidget::mouseMoveEvent(QMouseEvent *event)
{
    event->accept();
}

void QNCalendarWidget::mouseReleaseEvent(QMouseEvent *event)
{
    event->accept();
}

void QNCalendarWidget::onbtnClicked()
{
    QPushButton *senderBtn = qobject_cast<QPushButton *>(sender());
      if (senderBtn == m_leftYearBtn)
      {
          showPreviousYear();
      }
      else if (senderBtn == m_leftMonthBtn)
      {
          showPreviousMonth();
      }
      else if (senderBtn == m_rightYearBtn)
      {
          showNextYear();
      }
      else if (senderBtn == m_rightMonthBtn)
      {
          showNextMonth();
      }
}

void QNCalendarWidget::paintCell(QPainter *painter, const QRect &rect, const QDate &date) const
{
    if (date == selectedDate())
       {
           painter->save();
           painter->setRenderHint(QPainter::Antialiasing);
           painter->setPen(Qt::NoPen);
           painter->setBrush(QColor(0, 145, 255));

           painter->drawRoundedRect(rect.x(), rect.y() + 3, rect.width(), rect.height() - 6, 3, 3);
           painter->setPen(QColor(255, 255, 255));

           painter->drawText(rect, Qt::AlignCenter, QString::number(date.day()));
           painter->restore();
       }
       else if (date == QDate::currentDate())
       {
           painter->save();
           painter->setRenderHint(QPainter::Antialiasing);
           painter->setPen(Qt::NoPen);
           painter->setBrush(QColor(0, 161, 255));
           painter->drawRoundedRect(rect.x(), rect.y() + 3, rect.width(), rect.height() - 6, 3, 3);
           painter->setBrush(QColor(255, 255, 255));
           painter->drawRoundedRect(rect.x() + 1, rect.y() + 4, rect.width() - 2, rect.height() - 8, 2, 2);
           painter->setPen(QColor(0, 161, 255));

           painter->drawText(rect, Qt::AlignCenter, QString::number(date.day()));
           painter->restore();
       }
       else if (date < minimumDate() || date > maximumDate())
       {
           painter->save();
           painter->setRenderHint(QPainter::Antialiasing);
           painter->setPen(Qt::NoPen);
           painter->setBrush(QColor(249, 249, 249));

           painter->drawRect(rect.x(), rect.y() + 3, rect.width(), rect.height() - 6);
           painter->setPen(QColor(220, 220, 220));

           painter->drawText(rect, Qt::AlignCenter, QString::number(date.day()));
           painter->restore();
       }
       else
       {
           __super::paintCell(painter, rect, date);
       }
}
