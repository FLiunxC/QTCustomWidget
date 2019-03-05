#ifndef TREEWIDGET_H
#define TREEWIDGET_H

/**
* @brief: 基于树形结构的显示数据
* @author: Fu_Lin
* @date:
* @description:  用法简单，可随意更改显示结构和前缀图标
* 用法实例：demo只嵌套2层，多层按照实例一样显示
*    ui->treeWidget被提升为本类TreeWidget
*   //首先拿掉默认属性
*    ui->treeWidget->takeTreeWidgetDefaultProperty();
*
*  需要显示的数据
    QStringList strList ={"A", "AA", "AAA", "AAAA"};  父数据
    QStringList strChildList = {"BB","CC","DD","EE"}; 子数据
    QStringList strChildListS = {"GG","FF","MM","ZZ"}; 子数据的子数据
    for(auto str:strList)
    {
        //使用自定义item
//        Item * item = new Item(ui->treeWidget);
//        item->setLabelText(str);
//      QTreeWidgetItem * treeitem = ui->treeWidget->addParentWidget(ui->treeWidget, item); 下面的就不写出来了

      //使用原始的item文本设置，调用重载函数
        QTreeWidgetItem * treeitem = ui->treeWidget->addParentWidget(ui->treeWidget, str);

        //子孩子
        for(auto strChild : strChildList)
        {
//            Item * childitem = new Item(ui->treeWidget);
//             childitem->setLabelText(strChild);
            //使用原始的item文本设置，调用重载函数
            QTreeWidgetItem * childtreeitem =ui->treeWidget->addChildWidget(treeitem, strChild);
            //子孩子的孩子
            for(auto str:strChildListS)
            {
//                Item * childitems = new Item(ui->treeWidget);
//                childitems->setLabelText(str);

                //使用原始的item文本设置，调用重载函数
                ui->treeWidget->addChildWidget(childtreeitem, str);
            }
        }
    }
*/

#include <QTreeWidget>
#include <QTreeWidgetItem>

class TreeWidget : public QTreeWidget
{
    Q_OBJECT
public:
    TreeWidget(QWidget * parent = nullptr);

    /**
     * @brief addParentWidget 设置父Item，也是第一层item
     * @param parent 顶层item的父对象
     * @param widgetItem 自定义的较复杂的Item
     * @return 返回当前设置的父item
     */
    QTreeWidgetItem *addParentWidget(QWidget * parent, QWidget *  widgetItem);

    /**
     * @brief addParentWidget  重载函数，调用原生QTreeWidgetItem设置当前显示文本
     * @param parent 顶层item的父对象
     * @param text 需要显示的文本
     * @param column 显示在第几列
     * @param font 当前显示文本的字体参数
     * @return 返回当前设置的父item
     */
    QTreeWidgetItem *addParentWidget(QWidget * parent,  QString text, int column = 0, QFont font =QFont("Microsoft Yahei",10));


    /**
     * @brief addChildWidget 设置子Item， 属于非第一层item
     * @param parent  设置当前item的父对象，可以是顶层item和顶层item子孩子
     * @param widgetItem 自定义的较复杂的item
     * @return  返回当前设置的子item
     */
    QTreeWidgetItem *addChildWidget(QTreeWidgetItem * parent, QWidget *widgetItem);


    /**
     * @brief addChildWidget  重载函数，调用原生QTreeWidgetItem设置当前显示文本
     * @param parent  设置当前item的父对象，可以是顶层item和顶层item子孩子
     * @param text 当前显示的文本
     * @param column 当前显示的是第几列
     * @param font 当前显示文本的字体参数
     * @return 返回当前设置的子item
     */
    QTreeWidgetItem *addChildWidget(QTreeWidgetItem * parent,  QString text, int column = 0, bool withUpper = false, QFont font =QFont("Microsoft Yahei",10));


    /**
     * @brief setColumnCount 设置当前treeWidget的总共列数
     * @param column 设置的列数
     */
    void setColumnNum(int column);

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


    //设置是否单击点击展开
    void setSinglePointExpand(bool isSinglePoint);


    //重置样式，包含点击，悬浮，背景颜色, 折叠小图标的重置
    void resetTreeViewStyle();

private slots:
    void onItemExpandedSlot(QTreeWidgetItem *item, int column);
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

    bool m_singlePointExpand = true; //是否为单击展开，true为单击，false为双击点开
};

#endif // TREEWIDGET_H
