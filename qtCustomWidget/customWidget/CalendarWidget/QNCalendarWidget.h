#ifndef QNCALENDARWIDGET_H
#define QNCALENDARWIDGET_H

#include <QObject>
#include <QCalendarWidget>
#include <QMouseEvent>

class QPushButton;
class QLabel;

class QNCalendarWidget : public QCalendarWidget
{
    Q_OBJECT
public:
    explicit QNCalendarWidget(QWidget *parent = nullptr);

    void initControl();
    //日历的头部显示栏
    void initTopWidget();
    //日历的底部按钮选择栏，目前隐藏不使用
    void initBottomWidget();
    //设置显示当前年月更改的数据
    void setDataLabelTimeText(int year, int month);
signals:
    void signalSetCalendarTime(const QDate& data);

protected:
    void mouseDoubleClickEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
private slots:
    void onbtnClicked();
protected:
    void paintCell(QPainter *painter, const QRect &rect, const QDate &date) const;

private:
    QPushButton* m_leftYearBtn;
    QPushButton* m_leftMonthBtn;

    QPushButton* m_rightYearBtn;
    QPushButton* m_rightMonthBtn;

    QPushButton* m_ensureBtn;
    QPushButton* m_toDayBtn;

    QLabel* m_dataLabel;
};

#endif // QNCALENDARWIDGET_H
