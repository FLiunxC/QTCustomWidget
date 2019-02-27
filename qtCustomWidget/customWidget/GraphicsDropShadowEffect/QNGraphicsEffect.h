#ifndef QNGRAPHICSEFFECT_H
#define QNGRAPHICSEFFECT_H
/**
* @brief: 阴影使用框
* @author: Fu_Lin
* @date:
* @description: 用法：
*      QNGraphicsEffect * bodyShadow = new QNGraphicsEffect();
        bodyShadow->setBlurRadius(15.0);  //数字越大越发散
        bodyShadow->setDistance(4.0); //数字越大，半径范围越大
        bodyShadow->setColor(QColor(0, 0, 0, 80));
        ui->XXXX->setGraphicsEffect(bodyShadow);
*/

#include <QObject>
#include <QGraphicsDropShadowEffect>
#include <QGraphicsEffect>
#include <QPainter>
class QNGraphicsEffect : public QGraphicsEffect
{
    Q_OBJECT
public:
    explicit QNGraphicsEffect(QObject *parent = nullptr);
    void draw(QPainter* painter);
    QRectF boundingRectFor(const QRectF& rect) const;

    inline void setDistance(qreal distance) { _distance = distance; updateBoundingRect(); }
    inline qreal distance() const { return _distance; }

    inline void setBlurRadius(qreal blurRadius) { _blurRadius = blurRadius; updateBoundingRect(); }
    inline qreal blurRadius() const { return _blurRadius; }

    inline void setColor(const QColor& color) { _color = color; }
    inline QColor color() const { return _color; }

signals:

public slots:

private:
    qreal  _distance;
    qreal  _blurRadius;
    QColor _color;
};

#endif // QNGRAPHICSEFFECT_H
