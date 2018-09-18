#ifndef QNCHART_H
#define QNCHART_H
/**
* @brief: chart图形集合，集折线图，饼图，水平柱状图于一体
* @author: Fu_Lin
* @date:
* @description: 根据需求调用不同的init方法，返回对应的QChart
*/

#include <QObject>
#include <QChart>
#include <QDateTime>
#include <QDate>
#include <QChartView>
#include <QValueAxis>
#include <QScatterSeries>
#include <QLineSeries>
#include <QPieSeries>
#include <QPieSlice>
#include <QDateTimeAxis>
#include <QLegend>
#include <QHorizontalBarSeries>
#include <QBarSet>
#include <QList>
#include <QBarCategoryAxis>


QT_CHARTS_USE_NAMESPACE
class QNChart : public QChart
{
    Q_OBJECT
public:
    explicit QNChart(QChart *parent = nullptr);

    //初始化折线图chart
    QChart *initLineChartData();
    //初始化饼图chart
    QChart* initPieChartData();
    //初始化水平柱状图Chart
    QChart * initHBarSeries();

    //往后折线图追加数据
    void addLineChartData(qreal x, qreal y);
signals:
    //折线图hover
    void sighover(const QPointF &point, bool state);
    //饼图hover
    void sigPieHover(QString text,bool state);
public slots:
    void on_LineChartclick_slot(const QPointF &point);
    void on_LineChartReleased_slot(const QPointF &point);
    void on_PieHover_slot(bool state);
private:
    //折线图变量
    QLineSeries * m_LineSeries = nullptr;
    QScatterSeries * m_ScatterSeries = nullptr;
    QDateTimeAxis * m_axisX = nullptr;
    QValueAxis * m_axisY = nullptr;

    //饼图变量
    QPieSeries * m_PieSeries = nullptr;
    QList<QPieSlice *> m_PieSliceList;

    //水平柱状图变量
   QHorizontalBarSeries * m_horizontalBarSeries = nullptr;
   QList<QBarSet*> m_barSetList;
};

#endif // QNCHART_H
