#ifndef MYCOIN_H
#define MYCOIN_H

#include <QPushButton>
#include<QTimer>

class myCoin : public QPushButton
{
    Q_OBJECT
public:
    //explicit myCoin(QWidget *parent = nullptr);
    myCoin(QString bkImg);
    void changeFlag();
    void mousePressEvent(QMouseEvent*);  //重写鼠标点1击事件

signals:

public:   //金币的属性
    int posX;   //坐标x
    int posY;   //坐标y
    bool flag;  //正反属性

    QTimer* timer1;   //定时器，用于正面翻反面
    QTimer* timer2;   //定时器，用于反面翻正面
    int min = 1;
    int max = 8;

    bool isChange= false;
    bool isWin=false ; //是否胜利

};

#endif // MYCOIN_H
