#include "QN_Dialog.h"
#include "ui_QN_Dialog.h"
#include "HelpClass.h"
#include "QTimer"
#include "QNGraphicsEffect.h"
#include <QDebug>

QN_Dialog::QN_Dialog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QN_Dialog)
{
    ui->setupUi(this);

    initUI();


}

QN_Dialog::~QN_Dialog()
{
    delete ui;
}

void QN_Dialog::initUI()
{

    this->setMaximumSize(m_dialogWidth, m_dialogHeight);
    this->setMinimumSize(m_dialogWidth, m_dialogHeight);


    ui->pushButton_close->setBackgroundColor("#EFF3F5");
     ui->pushButton_close->setButtonBorderWideAndColor(0);
    ui->pushButton_close->setLeftIcon(":/img/windows/close2.png", ui->pushButton_close->size());
    ui->pushButton_close->setText("");

    ui->pushButton_copy->setButtonBorderWideAndColor(0);
    ui->pushButton_copy->setBackgroundColor("white");
    ui->pushButton_copy->setFontColor("#4BA4F2");
    ui->pushButton_copy->setText(tr("Copy"));
    ui->pushButton_copy->setButtonBorderWideAndColor(0);
    ui->pushButton_copy->setBackgroundColor("white");

    ui->label_dialogContent->adjustSize();
    ui->label_dialogContent->setReadOnly(true);
  //  ui->label_dialogContent->setGeometry(QRect(328, 240, 329, 27*2)); //两倍行距
    ui->label_dialogContent->setAlignment(Qt::AlignLeft);
    ui->label_dialogContent->raise();
    ui->label_dialogContent->show();

    QNGraphicsEffect * bodyShadow = new QNGraphicsEffect(this);
    bodyShadow->setBlurRadius(15.0);
    bodyShadow->setDistance(10.0);
    bodyShadow->setColor(QColor(204, 204, 204, 80));
    this->setGraphicsEffect(bodyShadow);

    connect(ui->pushButton_close, &PushButton::sigHover, this, &QN_Dialog::onPushButtonCloseHoverState);
    connect(ui->pushButton_close, &PushButton::sigBtnClick, this, &QN_Dialog::onPushButtonCloseClick);
    connect(ui->pushButton_copy, &PushButton::sigBtnClick, this, &QN_Dialog::onPushButtonCopyClick);

}

void QN_Dialog::setDialogTitle(QString titleText)
{
    if(!m_isHideTitle)
    {
        ui->label_dialogTitle->setText(titleText);
    }

}

void QN_Dialog::setDialogTitleProperty(QString color, int borderBttomLineWide)
{
    m_titleColor  = color;
    ui->widget_titleContainer->setStyleSheet(QString("QWidget#widget_titleContainer{ \
                                             background-color:%1; \
                                             border-radius:2px 0px 0px 2px;  \
                                             border-bottom:%2px solid rgba(234,234,234,1);}").arg(color, borderBttomLineWide));
}

void QN_Dialog::setDialogText(QString text)
{

    int fontwide = HelpClass::getFontWidth(text);
    qInfo()<<"fontwide = "<<fontwide;
       qInfo()<<"label width = "<<ui->label_dialogContent->width();
    qInfo()<<"转折次数= "<<fontwide/ui->label_dialogContent->width();
    ui->label_dialogContent->setText(text);

}

void QN_Dialog::setDialogSize(QSize size)
{
    m_dialogWidth = size.width();
    m_dialogHeight = size.height();
    this->setMaximumSize(size);
    this->setMinimumSize(size);
}

void QN_Dialog::setDialogBackgroundColor(QString color)
{
    m_backgroundColor = color;
    ui->widget_Container->setStyleSheet(QString("QWidget#widget_Container{ \
                                        background-color:%1;}").arg(color));
}

bool QN_Dialog::setCentreShow(QWidget *parent)
{
    QWidget * parentWidget  = nullptr;
    if(this->parent())
    {
         parentWidget =  static_cast<QWidget *> (this->parent());
    }
    else
    {
        this->setWindowFlags( Qt::Dialog| Qt::FramelessWindowHint);  //且无边框，保持最前
        parentWidget = parent;
    }

  if(!parentWidget)
  {
      return true;
  }

  if(!m_isHandMove)
  {
      int centreX = (parentWidget->width()-m_dialogWidth)/2;
      int centreY = (parentWidget->height() - m_dialogHeight)/2-30;

      m_movePoint = QPoint(centreX, centreY);
      this->move(centreX, centreY);
  }


  this->setWindowModality(Qt::WindowModal);
  this->show();

  if(m_eventLoop == nullptr){
      m_eventLoop = new QEventLoop(this);
      m_eventLoop->exec();
  };

   return m_close;
}


void QN_Dialog::onPushButtonCloseHoverState(bool hover)
{
    if(hover)
    {
        ui->pushButton_close->setLeftIcon(":/img/windows/close_b.png", QSize(15, 15));
    }
    else
    {
        ui->pushButton_close->setLeftIcon(":/img/windows/close2.png", QSize(30, 30));
    }
}

void QN_Dialog::onPushButtonCloseClick()
{
    emit sigColse();
    this->close();

    if(m_eventLoop)
    {
          m_eventLoop->exit();
          m_eventLoop->deleteLater();
          m_eventLoop = nullptr;
    }

     m_close = true;
}

void QN_Dialog::onPushButtonCopyClick()
{
    HelpClass::copyText(ui->label_dialogContent->toPlainText());
    ui->pushButton_copy->setText(tr("Copy success"));
    QTimer::singleShot(500, this, [=]{
        ui->pushButton_copy->setText(tr("Copy"));
    });
}

void QN_Dialog::onAnimationFinish()
{
    this->move(m_movePoint);
}


void QN_Dialog::onShakeWindow()
{
    if(m_pAnimation == nullptr)
    {
         m_pAnimation = new QPropertyAnimation(this, "pos", this);
    }

    if(m_pAnimation->state() == QAbstractAnimation::Running)
    {
        m_pAnimation->stop();
    }
    m_pAnimation->setDuration(300);
    m_pAnimation->setLoopCount(1);

//    pAnimation->setKeyValueAt(0, QPoint(geometry().x() - 3, geometry().y() - 3));
//    pAnimation->setKeyValueAt(0.1, QPoint(geometry().x() + 6, geometry().y() + 6));
//    pAnimation->setKeyValueAt(0.2, QPoint(geometry().x() - 6, geometry().y() - 6));
//    pAnimation->setKeyValueAt(0.3, QPoint(geometry().x() + 6, geometry().y() - 6));
//    pAnimation->setKeyValueAt(0.4, QPoint(geometry().x() - 6, geometry().y() + 6));
//    pAnimation->setKeyValueAt(0.5, QPoint(geometry().x() + 6, geometry().y() + 6));
//    pAnimation->setKeyValueAt(0.6, QPoint(geometry().x() - 6, geometry().y() - 6));
//    pAnimation->setKeyValueAt(0.7, QPoint(geometry().x() + 6, geometry().y() - 6));
//    pAnimation->setKeyValueAt(0.8, QPoint(geometry().x() - 6, geometry().y() + 6));
//    pAnimation->setKeyValueAt(0.9, QPoint(geometry().x() , geometry().y() ));
//    pAnimation->setKeyValueAt(1, QPoint(geometry().x() + 3, geometry().y() + 3));

    int zf = 6;
    for(float i= 0; i < 1.1; i = i+0.1) {
        m_pAnimation->setKeyValueAt(i, QPoint(geometry().x()+zf*(int(i*10)%2*(-1)),geometry().y()+zf*(int(i*10)%3*(-1)) ));
    }


    m_pAnimation->start();

    connect(m_pAnimation, &QPropertyAnimation::finished, this, &QN_Dialog::onAnimationFinish);
}

void QN_Dialog::hideDialogTitle(bool isHide)
{
    m_isHideTitle = isHide;
    if(isHide)
    {
       //ui->label_dialogContent->setMargin(10);
       ui->label_dialogTitle->setText("");
       ui->label_dialogTitle->setStyleSheet(QString("QLabel#label_dialogTitle{background-color:%1;border-bottom:0px;}").arg(m_backgroundColor));
       ui->widget_titleContainer->setStyleSheet("QWidget#widget_titleContainer{border-bottom:0px solid rgba(234,234,234,1);}");
       ui->pushButton_close->setBackgroundColor(m_backgroundColor);
       setDialogTitleProperty(m_backgroundColor, 0);
       QColor color("#BDBDBD");
    }
    else
    {
         //ui->label_dialogContent->setMargin(15);
        ui->label_dialogTitle->setStyleSheet(QString("QLabel#label_dialogTitle{background-color:%1;}").arg(m_titleColor));
        ui->widget_titleContainer->setStyleSheet("QWidget#widget_titleContainer{border-bottom:1px solid rgba(234,234,234,1);}");
        ui->pushButton_close->setBackgroundColor(m_titleColor);
        setDialogTitleProperty(m_titleColor, 0);
    }
}

bool QN_Dialog::handMove(QPoint point)
{
    m_isHandMove = true;
    this->move(point);

    m_movePoint = point;
    this->setWindowModality(Qt::WindowModal);
    this->show();

    if(m_eventLoop == nullptr){
        m_eventLoop = new QEventLoop(this);
        m_eventLoop->exec();
    }


    return m_close;
}

QPoint QN_Dialog::getMovePoint()
{
    return m_movePoint;
}

void QN_Dialog::mouseMoveEvent(QMouseEvent *event)
{
    event->accept();
}

void QN_Dialog::mousePressEvent(QMouseEvent *event)
{
    event->accept();
}

void QN_Dialog::mouseReleaseEvent(QMouseEvent *event)
{
    event->accept();
}
