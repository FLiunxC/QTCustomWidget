#ifndef PUSHBUTTON_H
#define PUSHBUTTON_H

#include <QPushButton>
#include <QMouseEvent>

class PushButton : public QPushButton
{
    Q_OBJECT

public:
    explicit PushButton(QWidget *parent = nullptr);


    //初始化默认样式
    void initDefaultStyleSheet();
    //设置是否有点击效果
    void setClickEffect(bool clickEffect);
    //设置背景图片
    void setBackgroundImage(QString imgPath);
    //设置背景是否透明，不影响图片的设置，单纯的背景透明
    void setButtonTransparency(bool isTransparency);
    //设置背景颜色，默认颜色是蓝色
    void setBackgroundColor(QString backgroundColor);

protected:

    void enterEvent(QEvent *event);
    void leaveEvent(QEvent *event);
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);

private:
    void pressClickStyleSheet();
    void releaseClickStyleSheet();
signals:
    //该信号可以监听单次点击效果
    void sigClick();
    //该信号可以监听点击按钮的次数，isSecondClick ---false为第一次点击，true为第二次点击，只能交替监听2次点击
    void sigClick(bool isSecondClick);
    void backgroundColorChanged(QString backgroundColor);

public slots:

private slots:


private:
    bool m_isClickSecond = false;
    bool m_isClickEffect = false;
    QString m_backGroundImage;
    QString m_backgroundColor = "rgb(14 , 150 , 254)";

};

#endif // PUSHBUTTON_H
