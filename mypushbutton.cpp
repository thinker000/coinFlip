#include "mypushbutton.h"

myPushButton::myPushButton(QWidget *parent) : QPushButton(parent)
{

}

myPushButton::myPushButton(QString normalImgPath, QString pressedImgPath)
{
    normalImgPath_m = normalImgPath;
    pressedImgPath_m = pressedImgPath;

    QPixmap pixmap;
    bool ret = pixmap.load(normalImgPath_m);//能否加载图片
    if(!ret)
        qDebug()<<"PIX load error";

    this->setFixedSize(pixmap.width(),pixmap.height());
    this->setStyleSheet("QPushButton{border:0px;}");
    this->setIcon(pixmap);
    this->setIconSize(QSize(pixmap.width(),pixmap.height()));
}

void myPushButton::mousePressEvent(QMouseEvent *e)
{
    if(pressedImgPath_m != "") //选中路径不为空，显示选中图片
        {
            QPixmap pixmap;
            bool ret = pixmap.load(pressedImgPath_m);
            if(!ret)
            {
                qDebug() << pressedImgPath_m << "加载图片失败!";
            }

            this->setFixedSize( pixmap.width(), pixmap.height() );
            this->setStyleSheet("QPushButton{border:0px;}");
            this->setIcon(pixmap);
            this->setIconSize(QSize(pixmap.width(),pixmap.height()));
        }
        //交给父类执行按下事件
    return QPushButton::mousePressEvent(e);

}

void myPushButton::mouseReleaseEvent(QMouseEvent *e)
{
    if(normalImgPath_m != "") //选中路径不为空，显示选中图片
        {
            QPixmap pixmap;
            bool ret = pixmap.load(normalImgPath_m);
            if(!ret)
            {
                qDebug() << normalImgPath_m << "加载图片失败!";
            }
            this->setFixedSize( pixmap.width(), pixmap.height() );
            this->setStyleSheet("QPushButton{border:0px;}");
            this->setIcon(pixmap);
            this->setIconSize(QSize(pixmap.width(),pixmap.height()));
        }
        //交给父类执行 释放事件
     return QPushButton::mouseReleaseEvent(e);

}

void myPushButton::zoom1()  //按下
{
    //创建动画对象
    QPropertyAnimation* anmAction = new QPropertyAnimation(this,"geometry");

    //设置时间间隔

    anmAction->setDuration(100);

    //开始位置
    anmAction->setStartValue(QRect(this->x(),this->y(),this->width(),this->height()));
    //结束位置
    anmAction->setEndValue((QRect(this->x(),this->y()+10,this->width(),this->height())));

    //跳跃效果
    anmAction->setEasingCurve(QEasingCurve::OutBounce);
    anmAction->start();
}

void myPushButton::zoom2() //弹回
{
    //创建动画对象
    QPropertyAnimation* anmAction = new QPropertyAnimation(this,"geometry");

    //设置时间间隔

    anmAction->setDuration(100);

    //开始位置
    anmAction->setStartValue(QRect(this->x(),this->y()+10,this->width(),this->height()));
    //结束位置
    anmAction->setEndValue((QRect(this->x(),this->y(),this->width(),this->height())));

    //跳跃效果
    anmAction->setEasingCurve(QEasingCurve::OutBounce);
    anmAction->start();
}
