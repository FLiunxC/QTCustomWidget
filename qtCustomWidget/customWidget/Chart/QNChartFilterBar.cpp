#include "QNChartFilterBar.h"
#include "ui_QNChartFilterBar.h"
#include <QDebug>
#include  "ComboBoxItem.h"
#include "QNoFocusFrameDelegate.h"
#include "ComboBox.h"

QNChartFilterBar::QNChartFilterBar(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QNChartFilterBar)
{
    ui->setupUi(this);

    setStartTimeText(tr("Start Timer"));
    setEndTimeText(tr("End Timer"));

//    m_listwidget = new QListWidget(this);
//    ui->comboBox->setItemDelegate(new QNoFocusFrameDelegate(this));
//    ui->comboBox->setModel(m_listwidget->model());
//    ui->comboBox->setView(m_listwidget);

//    for (int i = 0; i < 5; ++i)
//    {
//        ComboBoxItem* item = new ComboBoxItem(this);
//        item->setLabelContent(QString("Account") + QString::number(i, 10));

//        QListWidgetItem* widgetItem = new QListWidgetItem(m_listwidget);
//        m_listwidget->setItemWidget(widgetItem, item);
//        connect(m_listwidget, &QListWidget::currentItemChanged , ui->comboBox, &ComboBox::currentItemChanged_slot);
//    }
}

QNChartFilterBar::~QNChartFilterBar()
{
    delete ui;
}

void QNChartFilterBar::setEndTimeText(QString text)
{
    ui->pushButton_endTime->setText(text);
}

void QNChartFilterBar::setStartTimeText(QString text)
{
    ui->pushButton_startTime->setText(text);

}

void QNChartFilterBar::initComboBoxData()
{
    ui->comboBox->initComBox();

     ui->comboBox->setInitStyleSheet("blue");
     QStringList strList;
     strList<<"最近一周~"<<"最近一月~"<<"最近一年~";
     for (int i = 0; i < 3; ++i)
     {
            ui->comboBox->addItemTextData(strList.at(i), i);
     }
}

void QNChartFilterBar::on_pushButton_endTime_clicked()
{
    QPoint point;

    point.setX(ui->pushButton_endTime->x());
    point.setY(ui->pushButton_endTime->y() + ui->pushButton_endTime->height());
    point = ui->frame_date->mapToParent(point);
    point= this->mapFromParent(point);

    clickBtn(point, false);

}

void QNChartFilterBar::on_pushButton_startTime_clicked()
{
    QPoint point;

    point.setX(ui->pushButton_startTime->x());
    point.setY(ui->pushButton_startTime->y() + ui->pushButton_endTime->height());
    point = ui->frame_date->mapToParent(point);
    point= this->mapFromParent(point);

    clickBtn(point, true);
}
