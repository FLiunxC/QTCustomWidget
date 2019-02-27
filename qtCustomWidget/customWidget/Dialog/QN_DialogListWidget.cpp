#include "QN_DialogListWidget.h"
#include "ui_QN_DialogListWidget.h"
#include <QScrollBar>
#include <QBrush>
#include "singleinfo.h"
QN_DialogListWidget::QN_DialogListWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QN_DialogListWidget)
{
    ui->setupUi(this);
    connect(ui->listWidget, &QListWidget::itemDoubleClicked, this, &QN_DialogListWidget::ondoubleClickItem);

    ui->listWidget->setStyleSheet("  QListWidget{"
                                                            "background-color:rgba(250,250,250,1); \
                                                              border-radius:2px 0px 2px 0px; \
                                                              border:1px solid rgba(234,234,234,1);}  \
                                                      QListWidget::item:selected{   \
                                                              background:#D9D9D9;  \
                                                              color:#333333;  } \
                                                      QListWidget::item:selected:!active{ \
                                                              background:#D9D9D9; \
                                                              color:#333333; }  \
                                                      }");

   QScrollBar * scorllbar = ui->listWidget->verticalScrollBar();
   scorllbar->setStyleSheet("width:0px;");

}

QN_DialogListWidget::~QN_DialogListWidget()
{
    delete ui;
}

void QN_DialogListWidget::addItemText(QString text)
{
    QListWidgetItem * item = new QListWidgetItem(ui->listWidget);
    item->setText(text);
    item->setBackground(QBrush(QColor("white")));
    item->setTextColor(QColor("#838B8B"));
    item->setFont(QN_Windows_NormalFont2);

    ui->listWidget->addItem(item);
    ui->listWidget->setCurrentRow(0,QItemSelectionModel::SelectCurrent);
}

int QN_DialogListWidget::getItemCount()
{
    return ui->listWidget->count();
}

void QN_DialogListWidget::cleanAllItem()
{
    ui->listWidget->clear();
}

void QN_DialogListWidget::ItemUp()
{
    int currenRow = ui->listWidget->currentRow();

    if(currenRow)
    {
        currenRow  = currenRow-1;
        ui->listWidget->setCurrentRow(currenRow);
    }
    else
    {
        ui->listWidget->setCurrentRow(ui->listWidget->count()-1);
    }
}

void QN_DialogListWidget::ItemDown()
{
    int currenRow = ui->listWidget->currentRow();

    if(currenRow < ui->listWidget->count() - 1)
    {
        currenRow  = currenRow+1;
        ui->listWidget->setCurrentRow(currenRow);
    }
    else
    {
        ui->listWidget->setCurrentRow(0);
    }
}

QString QN_DialogListWidget::getCurrentItemText()
{
     QListWidgetItem * item = ui->listWidget->item(ui->listWidget->currentRow());

     if (item)
     {
         return item->text();
     }

     return "";

}

void QN_DialogListWidget::ondoubleClickItem(QListWidgetItem *listItem)
{
    emit sigitemDoubleSelectText(listItem->text());
}
