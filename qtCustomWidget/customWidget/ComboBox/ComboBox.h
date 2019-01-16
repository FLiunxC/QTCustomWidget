#ifndef COMBOBOX_H
#define COMBOBOX_H
/**
* @brief: 自定义的QComboBox，提升就ok了
* @author: Fu_Lin
* @date:
* @description: 提升之后需要在控件界面自定义QListWidget
*                       提升QComboBox控件类用法：
*                       第一种：（推荐）
*                                   在需要的地方调用initComBox()后，就可以调用addItemTextData()方法进行item的赋值
*
*                       第二种：（不推荐）自定义使用法：
*                                  m_listwidget = new QListWidget(this);
                                    ui->comboBox->setItemDelegate(new QNoFocusFrameDelegate(this));
                                    ui->comboBox->setModel(m_listwidget->model());
                                    ui->comboBox->setView(m_listwidget);

                                    for (int i = 0; i < 5; ++i)
                                      {
                                          ComboBoxItem* item = new ComboBoxItem(this);
                                          item->setLabelContent(QString("Account") + QString::number(i, 10));

                                          QListWidgetItem* widgetItem = new QListWidgetItem(m_listwidget);
                                          m_listwidget->setItemWidget(widgetItem, item);
                                          connect(m_listwidget, &QListWidget::currentItemChanged , ui->comboBox, &ComboBox::currentItemChanged_slot);
                                      }
*/

#include <QWidget>
#include <QComboBox>

class QListWidgetItem;
class QListWidget;
class ComboBox : public QComboBox
{
    Q_OBJECT
public:
    explicit ComboBox(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *e);


    //使用此控件，必须手动显示调用initComBox()该方法
    void initComBox();

    //必须调用initComBox后才能调用该方法赋值Item数据
    /**
     * @brief addItemTextData 添加ComboBox中子Item的信息
     * @param text 添加的文本信息
     * @param index 当前添加的索引值，从0开始
     */
    void addItemTextData(QString text, int index);

    //设置当前comboBox选中的item名称，出来时候默认是空的
    void setCurrentItem(QString item);

    //设置QComboBox的背景颜色
    void setBackgroundColor(QString color);
    //设置QComboBox的字体颜色
    void setFontColor(QString fontColor);

    //设置默认样式表 background -- 为blue代表蓝色背景，字体为白色； 为white代表白色背景，字体为黑色
    void setInitStyleSheet(QString background);

protected:
    void mouseMoveEvent(QMouseEvent *event);

    void enterEvent(QEvent *event);
    void leaveEvent(QEvent *event);

signals:
    void sigCurrentIndexChange(QString text, int index);
public slots:
public slots:
    //ListWidget的item项选择变换
    void currentItemChanged_slot(QListWidgetItem * current, QListWidgetItem * previous);

private :
    QString m_currentItem;
    QString m_backGroundColor = "#4ba4f2;"; //背景颜色
    QString m_fontColor = "white";
    bool m_update = true;
    QListWidget * m_listwidget = nullptr;
    QRect m_rect;
};

#endif // COMBOBOX_H
