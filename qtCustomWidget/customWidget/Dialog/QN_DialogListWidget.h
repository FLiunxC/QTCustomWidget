#ifndef QN_DIALOGLISTWIDGET_H
#define QN_DIALOGLISTWIDGET_H

#include <QWidget>
#include <QListWidgetItem>

namespace Ui {
class QN_DialogListWidget;
}

class QN_DialogListWidget : public QWidget
{
    Q_OBJECT

public:
    explicit QN_DialogListWidget(QWidget *parent = 0);
    ~QN_DialogListWidget();

    void addItemText(QString text);

    //获取所有item的个数
    int getItemCount();

    //清空所有的item
    void cleanAllItem();

    //手动将item的光标上移下移
    void ItemUp();
    void ItemDown();

    QString getCurrentItemText();
signals:
    void sigitemDoubleSelectText(QString text);
private slots:
    void ondoubleClickItem(QListWidgetItem* listItem);
private:
    Ui::QN_DialogListWidget *ui;

};

#endif // QN_DIALOGLISTWIDGET_H
