#include "TreeWidget.h"
#include <QDebug>

TreeWidget::TreeWidget(QWidget * parent):QTreeWidget(parent)
{
    this->setObjectName("treeWidget");


    connect(this, &TreeWidget::itemExpanded, this, &TreeWidget::onItemExpandedSlot);
}

QTreeWidgetItem * TreeWidget::addParentWidget(QWidget *parent, QWidget *widgetItem)
{
    QTreeWidget * treeParent = nullptr;
    if(!parent)
    {
         treeParent = this;
    }
    else
    {
         treeParent = static_cast<QTreeWidget *>(parent);
    }
      QTreeWidgetItem *parentitem = new QTreeWidgetItem(treeParent);

      addTopLevelItem(parentitem);
      setItemWidget(parentitem, 0,widgetItem);

      return parentitem;
}

QTreeWidgetItem *TreeWidget::addParentWidget(QWidget *parent, QString text, int column, QFont font)
{
    QTreeWidget * treeParent= nullptr;
    if(!parent)
    {
         treeParent = this;
    }
    else
    {
         treeParent = static_cast<QTreeWidget *>(parent);
    }

    this->setColumnCount(column+1);

    QTreeWidgetItem *parentitem = new QTreeWidgetItem(treeParent);

    parentitem->setFont(column, font);
    parentitem->setText(column, text);
     addTopLevelItem(parentitem);


     return parentitem;
 }

 QTreeWidgetItem * TreeWidget::addChildWidget(QTreeWidgetItem *parent, QWidget *widgetItem)
{
    QTreeWidgetItem *childitem = new QTreeWidgetItem(parent);

    parent->addChild(childitem);
    setItemWidget(childitem, 0,widgetItem);

    return childitem;
 }

 QTreeWidgetItem *TreeWidget::addChildWidget(QTreeWidgetItem *parent, QString text, int column, bool withUpper, QFont font)
 {
     static QTreeWidgetItem * beforechildItem = nullptr;
     QTreeWidgetItem * childItem = nullptr;
     if(!withUpper)
    {
          childItem = new QTreeWidgetItem(parent);
          beforechildItem = childItem;
     }
     else
     {
         if(!beforechildItem)
         {
             qWarning()<<"TreeWidget beforechildItem is NULL!!!";
             return childItem;
         }
         childItem = beforechildItem;
     }

     if(column > 0)
     {
         this->setColumnCount(column+1);
     }

     childItem->setFont(column, font);
     childItem->setText(column, text);

     parent->addChild(childItem);

     return childItem;
 }

void TreeWidget::takeTreeWidgetDefaultProperty()
{
    //去掉父子间距
    //this->setIndentation(0);
    //去掉折叠小图标
    this->setRootIsDecorated(false);
    //去掉表头
    this->setHeaderHidden(true);

    this->setStyleSheet("QTreeView::branch:has-children:!has-siblings:closed,\
                        QTreeView::branch:closed:has-children:has-siblings{border-image: none; image: none;}\
                        QTreeView::branch:open:has-children:!has-siblings,\
                        QTreeView::branch:open:has-children:has-siblings{border-image: none; image: none;}");

}

bool TreeWidget::isParent(QTreeWidgetItem *treeWidgetItem)
{
    if(treeWidgetItem->parent())
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool TreeWidget::isExpanded(QTreeWidgetItem *treeWidgetItem)
{
    int type = treeWidgetItem->type();

    return type == 1?true:false;
}

void TreeWidget::setRootDecorated(QString openIcon, QString closeIcon)
{
    m_DecoratedOpenIcon = openIcon;
    m_DecoratedCloseIcon = closeIcon;
    resetTreeViewStyle();
}

void TreeWidget::setTreeViewBackgroundColor(QString backgroundColor)
{
    m_TreeViewBackgroundColor = backgroundColor;
    resetTreeViewStyle();
}

void TreeWidget::setTreeViewItemHoverColor(QString hoverColor)
{
    m_TreeViewItemHoverColor = hoverColor;
    resetTreeViewStyle();
}

void TreeWidget::setTreeViewItemSelectColor(QString selectColor)
{
    m_TreeViewItemSelcetColor = selectColor;
    resetTreeViewStyle();
}

void TreeWidget::setBranchEnabled(bool enabled)
{
    m_isBranchEnabled = enabled;
    resetTreeViewStyle();
}

void TreeWidget::setBranchVlineIcon(QString vlineIcon)
{
    m_TreeViewbranchVlineIcon = vlineIcon;
    resetTreeViewStyle();
}

void TreeWidget::setBranchMoreIcon(QString branchMoreIcon)
{
    m_TreeViewbranchMoreIcon = branchMoreIcon;
    resetTreeViewStyle();
}

void TreeWidget::setBranchEndIcon(QString branchEndIcon)
{
    m_TreeViewbranchEndIcon = branchEndIcon;
    resetTreeViewStyle();
}

void TreeWidget::resetTreeViewStyle()
{
    qInfo()<<"进入treeview样式";
    QString styleSheetstr;

    //整行拓展显示
    styleSheetstr = "QTreeView#treeWidget{  \
            show-decoration-selected: 1;}";

//treeview的背景颜色设置
styleSheetstr += QString("QTreeView{ \
                         border: none; \
        background-color: %1; \
font-size: 16px; \
outline:none;}").arg(m_TreeViewBackgroundColor);

//    // 鼠标滑过
styleSheetstr += QString("QTreeView#treeWidget::item:hover, QTreeView#treeWidget::branch:hover {  \
                         background-color: %1;}").arg(m_TreeViewItemHoverColor);

//鼠标选中
styleSheetstr += QString("QTreeView::item:selected, QTreeView::branch:selected {  \
                         background-color: %1;}").arg(m_TreeViewItemSelcetColor);

//前缀图标的背景透明
if(this->rootIsDecorated())
{
    styleSheetstr += "QTreeView#treeWidget::branch {  \
            background-color: transparent;}";

//前缀图标的显示
styleSheetstr += QString("QTreeView#treeWidget::branch:open:has-children"
                         "{image: url(%1);}").arg(m_DecoratedOpenIcon);
styleSheetstr += QString("QTreeView#treeWidget::branch:closed:has-children {  \
                         image: url(%1);}").arg(m_DecoratedCloseIcon);

}

if(m_isBranchEnabled)
{
    styleSheetstr += QString("QTreeView#treeWidget::branch:has-siblings:!adjoins-item { \
                             border-image: url(%0) 0;} \
QTreeView#treeWidget::branch:has-siblings:adjoins-item {  \
                                 border-image: url(%1) 0;} \
QTreeView#treeWidget::branch:!has-children:!has-siblings:adjoins-item { \
                                  border-image: url(%2) 0;}").arg(m_TreeViewbranchVlineIcon, m_TreeViewbranchMoreIcon, m_TreeViewbranchEndIcon);
}

this->setStyleSheet(styleSheetstr);
}

void TreeWidget::onItemExpandedSlot(QTreeWidgetItem *item)
{
    item->setToolTip(0, "1");
}

void TreeWidget::onItemCollapsedSlot(QTreeWidgetItem *item)
{
    item->setToolTip(0, "0");
}
