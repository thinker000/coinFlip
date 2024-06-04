#include "mainscene.h"
#include "ui_mainscene.h"
#include<QPixmap>
#include<QPainter>
#include"mypushbutton.h"
#include<QTimer>
#include<QSoundEffect>

MainScene::MainScene(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainScene)
{
 //1.界面框架
    //1.1布局

    ui->setupUi(this);
    this->setFixedSize(600,1000);
    this->setWindowIcon(QPixmap(":/res/Coin0001.png"));
    this->setWindowTitle("老帮主带你翻金币");

    connect(ui->actiontuichu,&QAction::triggered,[=](){
        this->close();   //退出游戏
    });
    //1.2背景设置
        //paintEvent();

    //创建开始按钮

    //QSoundEffect *//backSound = new QSoundEffect(":/res/BackButtonSound.wav",this);       //返回按钮音效
    //QSoundEffect * //music = new QSoundEffect(":/res/TapButtonSound.wav",this);//开始按钮的音效
    myPushButton* startButton = new myPushButton(":res/MenuSceneStartButton.png");
    startButton->setParent(this);
    startButton->move(this->width()*0.5- startButton->width()*0.5,this->height()*0.7);
        //开始按钮跳跃特效
    connect(startButton,&myPushButton::clicked,[=](){
       //music->play();
       startButton->zoom1(); //按下
       startButton->zoom2(); //弹回
       //进入关卡选择场景
       QTimer::singleShot(100,this,[=](){
           this->hide();
           chooseLevScene->setGeometry(this->geometry());
           chooseLevScene->show();

       });
    });
    //返回按钮，返回主场景
    connect(chooseLevScene,&ChooseLevelScene::ChooseLevBack,[=](){
        //backSound->play();
        this->setGeometry(chooseLevScene->geometry());
        this->show();
    });


}

MainScene::~MainScene()
{
    delete ui;
}

void MainScene::paintEvent(QPaintEvent *)
{
    //创建画家
    QPainter painter(this);
    //创建绘画设备
    QPixmap pix;
    pix.load(":/res/PlayLevelSceneBg.png");
    //绘制
    painter.drawPixmap(0,0,this->width(),this->height(),pix);

    //加载标题
    pix.load(":/res/Title.png");

    //缩放图片
    pix =pix.scaled(pix.width()*0.8,pix.height()*0.8);
    painter.drawPixmap(10,30,pix.width(),pix.height(),pix);
}

