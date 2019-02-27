 #ifndef COMBOBOXITEM_H
#define COMBOBOXITEM_H

/**
* @brief: comboBox的显示Item
* @author: Fu_Lin
* @date:
* @description: 用于显示comboxBox的Item
*/

#include <QWidget>
#include <QSpacerItem>
#include <QSize>
#include <QMouseEvent>

class QLabel;
class QHBoxLayout;

class QListWidgetItem;

class ComboBoxItem:public QWidget
{
public:
    ComboBoxItem(QWidget * parent = nullptr);

    //设置item文本
    void setItemText(QString text, int index = 0);

    //设置左边icon
    void setLeftIcon(const QString &LiconPath, int index = -1,QSize iconSize = QSize());

    //设置右边icon
    void setRightIcon(const QString &RiconPath,  int index =-1 ,QSize iconSize = QSize());

    QString getLabelString();

    //获取当起那ComboBoxItem的索引
    int getCurrentIndex();

    void setCurrentIndex(int currentIndex);

private:
    void initUILayout();
    void setIconMaxAndMinValue(QWidget * widget, const QSize &size);
private:
    QLabel * m_comboxLeftIcon = nullptr; //comboxItem左边的小图标
    QLabel * m_comboxText = nullptr;  //comboxItem 文本
    QLabel * m_comboxRightIcon = nullptr; //comboxItem 右边的小图标

    //布局
    QHBoxLayout *m_layout;
    QSpacerItem * m_HspacerItemStart;
    QSpacerItem * m_HspacerItemEnd;
    int m_currentIndex;

};

#endif // COMBOBOXITEM_H
