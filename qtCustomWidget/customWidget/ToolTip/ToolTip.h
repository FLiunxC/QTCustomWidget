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

public:
    explicit ToolTip(QWidget *parent = nullptr);

    /**
     * @brief showToolMessage 设置提示框的位置和消息，并显示出来
     * @param point 提示框出现的位置
     * @param msg 提示框的消息
     */
    void showToolMessage(QPoint point, QString msg);

    /**
     * @brief showToolMessage 重载函数，此方法必须配合setAnimationPopupPosition，否则调用就会无效果
     * @param msg 设置提示框的显示消息
     */
    void showToolMessage(QString msg);

    /**
     * @brief setToolTipDelay 设置提示弹窗的显示时间
     * @param msec 毫秒级别, 默认是2000毫秒 = 2秒
     */
    void setToolTipDelay(int msec = 2000);

    /**
     * @brief setAnimationPopupPosition 调用此方式是启动动画弹出tooltip的位置
     * @param startPoint 弹窗动画的启动点
     * @param endPoint 弹窗动画的结束点
     * @param isStart 是否启动动画，默认调用是true
     */
    void setAnimationPopupPosition(QPoint startPoint, QPoint endPoint, bool isStart = true);

    /**
     * @brief getToolTipWidth 根据message文字获取toolTip的宽度
     * @param message 需要显示的文字宽度
     * @param 返回字体的宽度
     */
    int getToolTipWidth(QString message);

private:
    /**
     * @brief startAnimation 调用即启动动画，外部不能调用
     */
    void startAnimation();

    /**
     * @brief endAnimation 结束时启动该动画
     */
    void endAnimation();
signals:
    //弹窗隐藏时触发
    void sighide();

public slots:
    //隐藏弹出，并触发sighide信号
    void hideToolTip();

private:
    int m_msec = 1500; //定时器的触发时间，跟动画时间没关系，弹窗的显示时间
    QTimer * m_timer = nullptr; //定时器

    bool m_isStartAnimation = false; //是否启动动画
    QPoint m_animStartPoint; //动画移动的开始时间
    QPoint m_anmEndPoint;  //动画移动的结束时间
    QPropertyAnimation * m_animation = nullptr;
    bool m_isStart = true ; //ture代表启动动画，false代表结束动画
};

#endif // TOOLTIP_H
