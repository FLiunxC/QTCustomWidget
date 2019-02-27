#ifndef TREEWIDGET_H
#define TREEWIDGET_H

/**
* @brief: 基于树形结构的显示数据
* @author: Fu_Lin
* @date:
* @description:  用法简单，可随意更改显示结构和前缀图标
*/

#include <QTreeWidget>
#include <QTreeWidgetItem>

class TreeWidget : public QTreeWidget
{
    Q_OBJECT
public:
    TreeWidget(QWidget * parent = nullptr);

    /**
     * @brief takeTreeWidgetDefaultProperty 去掉默认的间隔，折叠图标, 表头
     *                                     等等其他自带的默认属性
     */
    void takeTreeWidgetDefaultProperty();

    /**
     * @brief isParent 是否有父对象
     * @param treeWidgetItem 传送过来的item
     * @return  true 有父对象，false 没有父对象
     */
    bool isParent(QTreeWidgetItem * treeWidgetItem);

    /**
     * @brief isExpanded 项目是否是展开的
     * @param treeWidgetItem
     */
    bool isExpanded(QTreeWidgetItem * treeWidgetItem);
    /**
     * @brief setRootDecorated 设置折叠装饰图标
     * @param openIcon 打开时的图标icon路径
     * @param closeIcon 关闭时的图标icon路径
     */
    void setRootDecorated(QString openIcon, QString closeIcon);

    /**
     * @brief setTreeViewBackgroundColor 设置树形结构的背景颜色
     * @param backgroundColor 背景颜色
     */
    void setTreeViewBackgroundColor(QString backgroundColor);

    /**
     * @brief setTreeViewItemHoverColor item悬浮时的颜色
     * @param hoverColor 悬浮颜色
     */
    void setTreeViewItemHoverColor(QString hoverColor);

    /**
     * @brief setTreeViewItemSelectColor item选中后的颜色
     * @param selectColor 选中颜色
     */
    void setTreeViewItemSelectColor(QString selectColor);

    /**
     * @brief setBranchEnabled 设置是否使能显示树状分支引导
     * @param enabled  true显示，false不显示
     */
    void setBranchEnabled(bool enabled);


    /**
     * @brief setBranchVlineIcon 设置分支的垂直显示图片
     * @param vlineIcon 显示图标的路径
     */
    void setBranchVlineIcon(QString vlineIcon);

    /**
     * @brief setBranchMoreIcon 设置分支展开更多时的显示图标
     * @param branchMoreIcon 图标路径
     */
    void setBranchMoreIcon(QString branchMoreIcon);

    /**
     * @brief setBranchEndIcon 设置分支结束时的显示图标
     * @param branchEndIcon 图标路径
     */
    void setBranchEndIcon(QString branchEndIcon);


    //重置样式，包含点击，悬浮，背景颜色, 折叠小图标的重置
    void resetTreeViewStyle();

private slots:
    void onItemExpandedSlot(QTreeWidgetItem *item);
    void onItemCollapsedSlot(QTreeWidgetItem *item);
private:
    //前缀折叠图标显示
    QString m_DecoratedOpenIcon;  //折叠小图标打开，有孩子时的状态
    QString m_DecoratedCloseIcon; //折叠小图标关闭，无孩子时的状态

    //虚线分支引导显示图标
    QString m_TreeViewbranchVlineIcon;  //树状虚线分支垂直线的显示图标
    QString m_TreeViewbranchMoreIcon; //树状虚线分支更多的显示图标
    QString m_TreeViewbranchEndIcon; //树状虚线分支结束的显示图标

    //item选中，悬浮，背景颜色等
    QString m_TreeViewBackgroundColor =  "#FFFFFF";  //树形结构的整体背景颜色, 默认白色
    QString m_TreeViewItemSelcetColor = "#F7F7F7"; //树形Item选择后的颜色，默认暗青色
    QString m_TreeViewItemHoverColor = "#4BA4F2"; //树形item悬浮时的颜色，默认蓝色

    bool m_isBranchEnabled = false;  //分支引导显示图标是否使能，默认不显示引导图

};

#endif // TREEWIDGET_H
