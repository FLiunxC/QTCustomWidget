#ifndef QNOFOCUSFRAMEDELEGATE_H
#define QNOFOCUSFRAMEDELEGATE_H

/**
* @brief: 摘要
* @author: Fu_Lin
* @date:
* @description: 去除QComboBox下拉框中的虚线框
*/

#include <QWidget>
#include <QStyledItemDelegate>

class QNoFocusFrameDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit QNoFocusFrameDelegate(QWidget *parent = nullptr);

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
signals:

public slots:
};

#endif // QNOFOCUSFRAMEDELEGATE_H
