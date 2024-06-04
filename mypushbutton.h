#ifndef MYPUSHBUTTON_H
#define MYPUSHBUTTON_H

#include <QPushButton>
#include<QString>
#include<QPixmap>
#include<QDebug>
#include<QSize>
#include<QPropertyAnimation>
#include<QRect>

class myPushButton : public QPushButton
{
    Q_OBJECT
public:
    explicit myPushButton(QWidget *parent = nullptr);
    myPushButton(QString normalImgPath,QString pressedImgPath="");
    void mousePressEvent(QMouseEvent* e);
    void mouseReleaseEvent(QMouseEvent* e);
    void zoom1();
    void zoom2();

signals:

private:
    QString normalImgPath_m;//默认显示图片路径
    QString pressedImgPath_m;//按下显示图片路径

};

#endif // MYPUSHBUTTON_H
