#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QDebug>
#include <QString>
#include <QDateTime>
#include <QList>
#include <QTimer>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

private:
    Ui::Dialog *ui;
    int imgnum; // 图片序号
    bool flag = true; // 轮播按钮状态标志
    QPixmap *pix;   // 建立QPixmap对象
    QTimer *timer; //设置定时器
    QTimer *flashtimer; // 1秒刷新
    QList<QString> imglist; // 图片路径列表
private slots:
    void preImgBtnSlot(); // 前一张图片槽函数
    void nextImgBtnSlot(); // 后一张图片槽函数
    void randomImgBtnSlot(); // 随机图片槽函数
    void carouseBtnSlot(); // 轮播开始or暂停按钮槽函数
    void imgCarouselSlot(); //图片自动轮播槽函数
    void updateTimeSlot();
};

#endif // DIALOG_H
