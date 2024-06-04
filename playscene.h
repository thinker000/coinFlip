#ifndef PLAYSCENE_H
#define PLAYSCENE_H

#include <QMainWindow>
#include<QVector>
#include"mycoin.h"

class playScene : public QMainWindow
{
    Q_OBJECT
public:
    explicit playScene(QWidget *parent = nullptr);
    playScene(int levelNum);
    void paintEvent(QPaintEvent*);
    bool checkWin();
    void coinSetWin();

signals:
    void chooseSceneBack();

public:
    int levelIndex;
    int gameArray[4][4]; // 二维数组，用来维护每个关卡的具体数据
    myCoin * coinBtn[4][4]; //金币按钮数组
    bool isWin;
};

#endif // PLAYSCENE_H
