#ifndef CHOOSELEVELSCENE_H
#define CHOOSELEVELSCENE_H

#include <QMainWindow>
#include"playscene.h"

class ChooseLevelScene : public QMainWindow
{
    Q_OBJECT
public:
    explicit ChooseLevelScene(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent*);


signals:
    void ChooseLevBack();

public:
    //游戏场景的对象指针
    playScene* play=nullptr;

};

#endif // CHOOSELEVELSCENE_H
