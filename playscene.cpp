#include "playscene.h"
#include"mypushbutton.h"
#include<QDebug>
#include<QString>
#include<QMenuBar>
#include<QPainter>
#include<QTimer>
#include<QLabel>
#include<QPixmap>
#include"mycoin.h"
#include"dataconfig.h"
//#include<QSoundEffect>


playScene::playScene(QWidget *parent) : QMainWindow(parent)
{

}

playScene::playScene(int levelNum)
{
    qDebug()<<QString("进入第%1关").arg(levelNum);
    this->levelIndex=levelNum;
    //初始化游戏场景
    //设置固定大小
    this->setFixedSize(600,1000);
    //设置图标
    this->setWindowIcon(QPixmap(":/res/Coin0001.png"));
    //设置标题
    this->setWindowTitle("翻金币场景");
    //添加菜单栏信息
    QMenuBar* bar =menuBar();
    //创建开始菜单
    QMenu* startMenu = bar->addMenu("开始");
    //创建离开菜单
    QAction* quitAction= startMenu->addAction("退出");
    //退出游戏
    connect(quitAction,&QAction::triggered,[=](){
        this->close();
    });

    //背景  重写paintEvent()
/*
    //翻金币音效
    QSoundEffect *flipSound = new QSoundEffect(this);
    //flipSound->setSource()
    //胜利按钮音效
    QSoundEffect *winSound = new QSoundEffect(this);
    //返回按钮音效
    QSoundEffect *backSound = new QSoundEffect(this);
*/

    //关卡返回按钮
    myPushButton* retBtn= new myPushButton(":/res/BackButton.png",":/res/BackButtonSelected.png");
    retBtn->setParent(this);
    retBtn->move(this->width()-retBtn->width(),this->height()- retBtn->height());

    connect(retBtn,&myPushButton::clicked,[=](){
        //backSound->play();
        QTimer::singleShot(100,this,[=](){
            emit this->chooseSceneBack();
        });
    });

    //显示当前关卡数
    QLabel* label= new  QLabel(this);
    QFont font;
    font.setFamily("华文新魏");
    font.setPointSize(20);
    label->setFont(font);
    QString str = QString("Level: %1").arg(this->levelIndex);
    label->setText(str);
    label->setGeometry(30,this->height()-50,200,50); //设置几何体

    //胜利后显示的图片
      QLabel* winLabel = new QLabel;
      QPixmap tmpPix;
      tmpPix.load(":/res/LevelCompletedDialogBg.png");
      winLabel->setGeometry(0,0,tmpPix.width(),tmpPix.height());
      winLabel->setPixmap(tmpPix);
      winLabel->setParent(this);
      winLabel->move( (this->width() - tmpPix.width())*0.5 , -tmpPix.height());


    //显示金币背景
    //初始化每个关卡的二维数组
    dataConfig data;
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            this->gameArray[i][j]=data.mData[this->levelIndex][i][j];
        }
    }


    //创建金币的背景图片
        for(int i = 0 ; i < 4;i++)
        {
            for(int j = 0 ; j < 4; j++)
            {
               //绘制背景图片
                QPixmap pix = QPixmap(":/res/BoardNode.png");
                QLabel* label = new QLabel;
                label->setGeometry(0,0,pix.width(),pix.height());
                label->setPixmap(pix);
                label->setParent(this);
                label->move(200 + i*pix.width(),400+j*pix.height());

                //绘制金币
                QString image;
                if(this->gameArray[i][j]==1)
                    image=":/res/Coin0001.png";
                else
                    image=":/res/Coin0008.png";

                myCoin* coin= new myCoin(image);
                coin->setParent(this);
                coin->move(202 + i*pix.width(),402+j*pix.height());

                //给金币属性初始化
                coin->posX = i;
                coin->posY = j;
                coin->flag = gameArray[i][j];
                coinBtn[i][j]= coin;

                //点击金币，进行翻转
                connect(coin,&myCoin::clicked,[=](){
                   // //flipSound->play();
                    coin->changeFlag();
                    this->gameArray[i][j]=this->gameArray[i][j]==0 ? 1: 0;
                    //延迟反转周围
                    QTimer::singleShot(50, this,[=](){
                        if(coin->posX+1 <=3)
                        {
                            //flipSound->play();
                            coinBtn[coin->posX+1][coin->posY]->changeFlag();
                            gameArray[coin->posX+1][coin->posY] = gameArray[coin->posX+1][coin->posY]== 0 ? 1 : 0;
                        }
                        if(coin->posX-1>=0)
                        {
                            //flipSound->play();
                            coinBtn[coin->posX-1][coin->posY]->changeFlag();
                            gameArray[coin->posX-1][coin->posY] = gameArray[coin->posX-1][coin->posY]== 0 ? 1 : 0;
                        }
                        if(coin->posY+1<=3)
                        {
                            //flipSound->play();
                            coinBtn[coin->posX][coin->posY+1]->changeFlag();
                            gameArray[coin->posX][coin->posY+1] = gameArray[coin->posX+1][coin->posY]== 0 ? 1 : 0;
                        }
                        if(coin->posY-1>=0)
                        {
                            //flipSound->play();
                            coinBtn[coin->posX][coin->posY-1]->changeFlag();
                            gameArray[coin->posX][coin->posY-1] = gameArray[coin->posX+1][coin->posY]== 0 ? 1 : 0;
                        }
                        //判断是否胜利
                        if(checkWin())
                        {
                            //winSound->play();
                            QPropertyAnimation * animation1 =  new QPropertyAnimation(winLabel,"geometry");
                            animation1->setDuration(1000);
                            animation1->setStartValue(QRect(winLabel->x(),winLabel->y(),winLabel->width(),winLabel->height()));
                            animation1->setEndValue(QRect(winLabel->x(),winLabel->y()+200,winLabel->width(),winLabel->height()));
                            animation1->setEasingCurve(QEasingCurve::OutBounce);
                            animation1->start();
                            coinSetWin();//胜利后，禁止金币按钮点击事件
                        }
                    });
                });

            }
        }

}


void playScene::paintEvent(QPaintEvent *) //重载背景
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/PlayLevelSceneBg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);

    //加载标题
    pix.load(":/res/Title.png");
    pix = pix .scaled(pix.width()*0.5,pix.height()*0.5);
    painter.drawPixmap(10,30,pix.width(),pix.height(),pix);
}

bool playScene::checkWin()
{
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            if(coinBtn[i][j]->flag==false)
            {
                return false;
            }
        }
    }
    return true;
}

void playScene::coinSetWin()
{
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            coinBtn[i][j]->isWin=true;
        }
    }
}
