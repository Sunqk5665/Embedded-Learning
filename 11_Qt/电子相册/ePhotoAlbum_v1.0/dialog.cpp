#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog),imgnum(0)
{
    ui->setupUi(this);

    pix = new QPixmap;
    timer = new QTimer;
    flashtimer = new QTimer;
    timer->start(2000); // 设置2秒定时
    flashtimer->start(1000);

    QString imgpath1 = ":/new/prefix1/image/img1.jpg";
    QString imgpath2 = ":/new/prefix1/image/img2.jpg";
    QString imgpath3 = ":/new/prefix1/image/img3.jpg";
    QString imgpath4 = ":/new/prefix1/image/img4.jpg";
    QString imgpath5 = ":/new/prefix1/image/img5.jpg";

    imglist <<imgpath1 <<imgpath2 <<imgpath3 <<imgpath4 <<imgpath5;

    connect(ui->prePushBtn,SIGNAL(clicked()),this,SLOT(preImgBtnSlot()));
    connect(ui->nextPushBtn,SIGNAL(clicked()),this,SLOT(nextImgBtnSlot()));
    connect(ui->randomPushBtn,SIGNAL(clicked()),this,SLOT(randomImgBtnSlot()));
    connect(ui->carousePushBtn,SIGNAL(clicked()),this,SLOT(carouseBtnSlot()));
    connect(ui->pushButtonClose,SIGNAL(clicked()),this,SLOT(close())); // 关闭窗口
    connect(flashtimer,SIGNAL(timeout()),this,SLOT(updateTimeSlot()));

    // 定时器信号槽
    connect(timer,SIGNAL(timeout()),this,SLOT(imgCarouselSlot()));

    //    for(int i=0; i<imglist.size(); i++)
    //    {
    //        QString str = imglist.at(i);
    //        qDebug() <<str;
    //    }
}

Dialog::~Dialog()
{
    delete ui;
    delete pix;
    delete timer;
}

void Dialog::preImgBtnSlot()
{
    imgnum = (imgnum + 5 - 1) % 5;
    //qDebug() << "图片" << imgnum;
    pix->load(imglist.at(imgnum)); // 加载imglist中的前一张图片
    ui->label->setPixmap(*pix); // 将图片设置到QLbel上
    ui->label_imgName->setText(QString::number(imgnum+1)); // 图片序号显示
}

void Dialog::nextImgBtnSlot()
{
    imgnum = (imgnum + 1) % 5;
    //qDebug() << "图片" << imgnum;
    pix->load(imglist.at(imgnum));
    ui->label->setPixmap(*pix);
    ui->label_imgName->setText(QString::number(imgnum+1));
}

void Dialog::randomImgBtnSlot()
{
    qint64 time = QDateTime::currentMSecsSinceEpoch();
    qsrand(time);
    int rand = qrand()%5; // 生成0-4的随机数

    imgnum = rand;
    //qDebug() << "随机图片" << imgnum;
    pix->load(imglist.at(imgnum));
    ui->label->setPixmap(*pix);
    ui->label_imgName->setText(QString::number(imgnum+1));
}

void Dialog::carouseBtnSlot()
{
    flag = !flag;
    if(flag)
    {
        timer->start(2000); // 启动定时器
        ui->carousePushBtn->setText("停止轮播");
    }
    else
    {
        timer->stop(); // 停止定时器
        ui->carousePushBtn->setText("开始轮播");
    }
}

void Dialog::imgCarouselSlot()
{
    imgnum = (imgnum + 1) % 5;
    pix->load(imglist.at(imgnum));
    ui->label->setPixmap(*pix);
    ui->label_imgName->setText(QString::number(imgnum+1));
}

void Dialog::updateTimeSlot()
{
    QDateTime now = QDateTime::currentDateTime();
    // 转换为固定格式
    QString time_text = now.toString("yyyy-MM-dd hh:mm:ss");
    //qDebug() << text; // "2023-10-20 16:00:44"
    ui->lcdDate->display(time_text);
}
