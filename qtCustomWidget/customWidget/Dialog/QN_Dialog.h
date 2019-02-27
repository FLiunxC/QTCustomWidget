#ifndef QN_DIALOG_H
#define QN_DIALOG_H

#include <QWidget>
#include <QEventLoop>
#include <QPropertyAnimation>

namespace Ui {
class QN_Dialog;
}

class QN_Dialog : public QWidget
{
    Q_OBJECT

public:
    explicit QN_Dialog(QWidget *parent = 0);
    ~QN_Dialog();

    void initUI();

    void setDialogTitle(QString titleText);
    void setDialogTitleProperty(QString color, int borderBttomLineWide = 1);

    void setDialogText(QString text);
    void setDialogSize(QSize size);

    void setDialogBackgroundColor(QString color);


    void onShakeWindow();
    void hideDialogTitle(bool isHide);

    bool setCentreShow(QWidget * parent = nullptr);
    bool handMove(QPoint point);
    QPoint getMovePoint();
protected:
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

private slots:
    void onPushButtonCloseHoverState(bool hover);
    void onPushButtonCloseClick();
    void onPushButtonCopyClick();
    void onAnimationFinish();

signals:
    void sigColse();
private:
    Ui::QN_Dialog *ui;
    int m_dialogHeight = 250;
    int m_dialogWidth = 300;
    QEventLoop * m_eventLoop = nullptr;
    bool m_close = false;
    bool m_isHideTitle = false;  //标题是否隐藏
    QString m_backgroundColor = "white"; //背景颜色，默认白色
    QString m_titleColor = "#EFF3F5";  //标题栏颜色，默认青褐色
    bool m_isHandMove = false;  //是否手动移动
    QPoint m_movePoint; //记录移动的点
    QPropertyAnimation *m_pAnimation = nullptr;
};

#endif // QN_DIALOG_H
