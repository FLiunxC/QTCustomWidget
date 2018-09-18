 #ifndef COMBOBOXITEM_H
#define COMBOBOXITEM_H

/**
* @brief: comboBox的显示Item
* @author: Fu_Lin
* @date:
* @description: 用于显示comboxBox的Item
*/

#include <QWidget>

class QLabel;
class QHBoxLayout;

class QListWidgetItem;

class ComboBoxItem:public QWidget
{
public:
    ComboBoxItem(QWidget * parent = nullptr);
    void setLabelContent(QString text, int index);
    void setImg(QPixmap pic);
    QString getLabelString();

    //获取当起那ComboBoxItem的索引
    int getCurrentIndex();

private:
    QLabel * m_img;
    QLabel * m_label;
    QHBoxLayout *m_layout;
    int m_currentIndex;

};

#endif // COMBOBOXITEM_H
