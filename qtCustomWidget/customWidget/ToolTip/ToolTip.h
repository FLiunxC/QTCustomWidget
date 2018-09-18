#ifndef TOOLTIP_H
#define TOOLTIP_H
/**
* @brief: 临时弹窗提示toolTip
* @author: Fu_Lin
* @date:
* @description: 自定义弹窗位置，输入语句即可 ，可以启动动画弹出和定时显示功能
*/
#include <QObject>
#include <QLabel>
#include <QTimer>

class QPropertyAnimation;
class ToolTip : public QLabel
{
    Q_OBJECT
 //   Q_PROPERTY(QString  "" READ "" WRITE set"" NOTIFY ""Changed)
public:
    explicit ToolTip(QWidget *parent = nullptr);
    void showToolMessage(QPoint point, QString msg);

    //调用setAnimationPopup后再调用方法
    void showToolMessage(QString msg);

    void setToolTipDelay(int msec); //设置延时度

    /**
     * @brief setAnimationPopup 调用此方式是启动动画弹出tooltip
     * @param startPoint 动画的启动点
     * @param endPoint 动画的结束点
     * @param isStart 是否启动动画，默认调用时true
     */
    void setAnimationPopup(QPoint startPoint, QPoint endPoint, bool isStart = true);

private:
    //调用即启动动画，外部不能调用
    void startAnimation();
signals:
    void sighide();
public slots:
    void hideToolTip();

private:
    int m_msec = 2000; //定时器的触发时间，跟动画时间没关系
    QTimer * m_timer = nullptr; //定时器
    bool m_isStartAnimation = false; //是否启动动画
    QPoint m_animStartPoint; //动画移动的开始时间
    QPoint m_anmEndPoint;  //动画移动的结束时间
    QPropertyAnimation * m_animation = nullptr;
};

#endif // TOOLTIP_H
