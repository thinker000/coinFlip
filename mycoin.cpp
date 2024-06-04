#include "mycoin.h"
#include<QDebug>
#include<QString>

//myCoin::myCoin(QWidget *parent) : QPushButton(parent)
//{

//}

myCoin::myCoin(QString bkImg)
{
    QPixmap pix;
    bool ret = pix.load(bkImg);
    if(!ret)
        qDebug()<<QString("加载图片%1失败！").arg(bkImg);
    this->setFixedSize(pix.width(),pix.height());
    this->setStyleSheet("QPushButton{border:0px;}");
    this->setIcon(pix);
    this->setIconSize(QSize(pix.width(),pix.height()));
    timer1= new QTimer(this);
    timer2= new QTimer(this);

    connect(timer1,&QTimer::timeout,[=](){
        QPixmap pix;
        QString str = QString(":/res/Coin000%1.png").arg(this->min++);
        pix.load(str);
        this->setFixedSize(pix.width(),pix.height());
        this->setStyleSheet("QPushButton{border:0px;}");
        this->setIcon(pix);
        this->setIconSize(QSize(pix.width(),pix.height()));

        if(this->min>this->max)
        {
            timer1->stop();
            isChange=false;
            this->min=1;
        }
    });
    connect(timer2,&QTimer::timeout,[=](){
        QPixmap pix;
        QString str = QString(":/res/Coin000%1.png").arg(this->max--);
        pix.load(str);
        this->setFixedSize(pix.width(),pix.height());
        this->setStyleSheet("QPushButton{border:0px;}");
        this->setIcon(pix);
        this->setIconSize(QSize(pix.width(),pix.height()));

        if(this->min>this->max)
        {
            timer2->stop();
            isChange=false;
            this->max=8;
        }
    });
}

void myCoin::changeFlag()
{
    if(this->flag)
    {
        timer1->start(30);
        isChange=true;
        this->flag=false;
    }
    else
    {
        timer2->start(30);
        isChange=true;
        this->flag=true;
    }
}

void myCoin::mousePressEvent(QMouseEvent *e)
{
    if(this->isChange || this->isWin)
        return ;
    else
        QPushButton::mousePressEvent(e);
}
