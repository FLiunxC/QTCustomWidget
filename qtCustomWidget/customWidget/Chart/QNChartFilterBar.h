#ifndef QNCHARTFILTERBAR_H
#define QNCHARTFILTERBAR_H

#include <QWidget>
#include "QNCalendarWidget.h"
#include <QPoint>
#include <QListWidget>

namespace Ui {
class QNChartFilterBar;
}

class QNChartFilterBar : public QWidget
{
    Q_OBJECT

public:
    explicit QNChartFilterBar(QWidget *parent = 0);
    ~QNChartFilterBar();

    void setEndTimeText(QString text);
    void setStartTimeText(QString text);

    void initComboBoxData();
private slots:
    void on_pushButton_endTime_clicked();
    void on_pushButton_startTime_clicked();

signals:
    /**
     * @brief clickBtn 按钮点击后发出
     * @param isStartBtn true表示开始时间按钮，false表示结束时间按钮
     */
    void clickBtn(QPoint, bool isStartBtn);


private:
    Ui::QNChartFilterBar *ui;

    QNCalendarWidget * m_calendar = nullptr;

    QListWidget * m_listwidget = nullptr;
};

#endif // QNCHARTFILTERBAR_H
