#include "QNChart.h"
#include <QDebug>
#include "../../control/singleinfo.h"

QNChart::QNChart(QChart *parent) : QChart(parent)
{

}

void QNChart::addLineChartData(qreal x, qreal y)
{
    m_LineSeries->append(x, y);
    m_ScatterSeries->append(x, y);
}

QChart* QNChart::initLineChartData()
{
    Q_ASSERT(m_LineSeries == nullptr);
    QChart * chart = new QChart();
    if(m_LineSeries == nullptr)
    {
        m_LineSeries = new QLineSeries();
    }
    if(m_ScatterSeries == nullptr)
    {
        m_ScatterSeries = new QScatterSeries();
    }
    //记录日期，1号到7号
    QStringList value;
    value<<"1"<<"2"<<"3"<<"4"<<"5"<<"6"<<"7";

    for(int i = 0; i < 30; i++)
    {
        QDateTime momentInTime;
        QString data = QString::number(i+1);//value.at(i);
        momentInTime.setDate(QDate(2008,5 , data.toInt()));
        qint64 msecs =  momentInTime.toMSecsSinceEpoch();
        addLineChartData(msecs, qrand()%10);
    }

    chart->addSeries(m_LineSeries);
    chart->addSeries(m_ScatterSeries);
    chart->legend()->hide();
    chart->setTitle("Simple line chart example");

    if(m_axisX == nullptr)
    {
        m_axisX = new QDateTimeAxis();
    }

    m_axisX->setFormat("MMM/dd");
    m_axisX->setTickCount(12);
    m_axisX->setGridLineVisible(false);

    chart->addAxis(m_axisX, Qt::AlignBottom);
    m_LineSeries->attachAxis(m_axisX);
    m_ScatterSeries->attachAxis(m_axisX);

    if(m_axisY == nullptr)
    {
        m_axisY = new QValueAxis();
    }

    chart->addAxis(m_axisY, Qt::AlignLeft);
    m_LineSeries->attachAxis(m_axisY);
    m_ScatterSeries->attachAxis(m_axisY);
     connect(m_ScatterSeries, &QScatterSeries::hovered, this, &QNChart::sighover);
     connect(m_ScatterSeries, &QScatterSeries::clicked, this, &QNChart::on_LineChartclick_slot);
     connect(m_ScatterSeries, &QScatterSeries::released, this, &QNChart::on_LineChartReleased_slot);

     return chart;
}

QChart *QNChart::initPieChartData()
{
    Q_ASSERT(m_PieSeries == nullptr);
    QChart * chart = new QChart();
    if(m_PieSeries == nullptr)
    {
        m_PieSeries = new QPieSeries();
    }

    m_PieSeries = new QPieSeries();
    m_PieSeries->setPieSize(1.0);
    m_PieSeries->setHoleSize(0.3);

    QPieSlice * PieSliceTemp = m_PieSeries->append("微信来源", 30);
    PieSliceTemp->setBrush(QColor("#619FF5"));

    m_PieSliceList.append(PieSliceTemp);
    PieSliceTemp =  m_PieSeries->append("QQ来源", 20);
   PieSliceTemp->setBrush(QColor("#57C792"));
    m_PieSliceList.append(PieSliceTemp);
    PieSliceTemp = m_PieSeries->append("Other",50);
    PieSliceTemp->setBrush(QColor("#FBB95E"));
    m_PieSliceList.append(PieSliceTemp);

    chart->addSeries(m_PieSeries);
    QLegend * legend = chart->legend();
    legend->setMarkerShape(QLegend::MarkerShapeCircle);
    QFontMetrics fontMetrics(QN_Windows_BetterNormalFont);

    legend->setAlignment(Qt::AlignBottom);
    legend->setColor(QColor("#B2B2B2"));
    legend->setFont(QN_Windows_NormalFont2);
   for(int i = 0; i < m_PieSliceList.length(); i++)
   {
        legend->resize(fontMetrics.width( m_PieSliceList.at(i)->label()), 20);
       m_PieSliceList.at(i)->setExplodeDistanceFactor(0.05);
       connect(m_PieSliceList.at(i), &QPieSlice::hovered,this, &QNChart::on_PieHover_slot);
   }

    return chart;
}

QChart *QNChart::initHBarSeries()
{
    Q_ASSERT(m_horizontalBarSeries == nullptr);

   QChart * chart = new QChart();

    if(m_horizontalBarSeries == nullptr)
    {
          m_horizontalBarSeries = new QHorizontalBarSeries();
    }
    QStringList str;
    str<<tr("System average")<<tr("My");

    //条棒bar的颜色
    QStringList colorStr;
    colorStr<<"#D4EBFF"<<"#5899F1";
    for(int i = 0; i < 2; i++)
    {
        QBarSet * setBar = new QBarSet(str[i]);
        for(int i = 0; i < 3; i++)
        {
              qreal value = qrand()%100;
              setBar->append(value);
        }

        setBar->setBrush(QColor(colorStr[i]));


        m_barSetList.append(setBar);
    }
    m_horizontalBarSeries->append(m_barSetList);
    chart->addSeries(m_horizontalBarSeries);
    QStringList categories;
    //最上面的在最下面
    categories.append(tr("Session access"));
    categories.append(tr("First response time"));
    categories.append(tr("Satisfaction"));
//    categories.append("A");
//    categories.append("N");
//    categories.append("B");
    //    QBarCategoryAxis *axisY = new QBarCategoryAxis();
    //    axisY->append(categories);
    //    axisY->setGridLineVisible(false);
    //    axisY->setLabelsFont(QN_Windows_NormalFont2);

    QBarCategoryAxis *axisY = new QBarCategoryAxis();
    axisY->append(categories);
    chart->setAxisY(axisY, m_horizontalBarSeries);
    QValueAxis *axisX = new QValueAxis();
    chart->setAxisX(axisX, m_horizontalBarSeries);
    axisX->applyNiceNumbers();
    axisX->setVisible(true);
    axisX->setGridLineVisible(false);
    QLegend * legend = chart->legend();
    legend->setMarkerShape(QLegend::MarkerShapeCircle);

    legend->setAlignment(Qt::AlignBottom);
    legend->setColor(QColor("#B2B2B2"));
    legend->setFont(QN_Windows_NormalFont2);
    chart->legend()->setVisible(true);

    return chart;
}

void QNChart::on_LineChartclick_slot(const QPointF &point)
{
    sighover(point, true);
}

void QNChart::on_LineChartReleased_slot(const QPointF &point)
{
    sighover(point, false);
}

void QNChart::on_PieHover_slot(bool state)
{
    QPieSlice * pieSlick = qobject_cast<QPieSlice*>(sender());

    if(state)
    {
        pieSlick->setExploded();
    }
    else
    {
        pieSlick->setExploded(false);
    }
    QString infoText = pieSlick->label() +"\n"+QString::number(pieSlick->value())+"%";
    emit sigPieHover(infoText, state);
}

