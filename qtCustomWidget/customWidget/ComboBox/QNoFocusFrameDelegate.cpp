#include "QNoFocusFrameDelegate.h"
#include <QPainter>
QNoFocusFrameDelegate::QNoFocusFrameDelegate(QWidget *parent) : QStyledItemDelegate(parent)
{

}

void QNoFocusFrameDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QStyleOptionViewItem itemOption(option);

    if(itemOption.state & QStyle::State_HasFocus)
    {
        itemOption.state ^= QStyle::State_HasFocus;
    }
    QStyledItemDelegate::paint(painter, itemOption, index);
}
