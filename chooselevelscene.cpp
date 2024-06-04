#include "chooselevelscene.h"
#include<QMenuBar>
#include<QAction>
#include<QPainter>
#include<QPixmap>
#include<QTimer>
#include "mypushbutton.h"
#include<QLabel>
#include<QString>
#include<QDebug>
#include<QSoundEffect>

ChooseLevelScene::ChooseLevelScene(QWidget *parent) : QMainWindow(parent)
{
    this->setFixedSize(600,1000);
    this->setWindowIcon(QPixmap(":/res/Coin0001.png"));
    this->setWindowTitle("选择关卡");
    QMenuBar* bar = this->menuBar();
    this->setMenuBar(bar);
    QMenu* startMenu = bar->addMenu("开始");
    QAction* quite = startMenu->addAction("退出");
   // QSoundEffect *//chooseSound = new QSoundEffect(":/res/TapButtonSound.wav",this);

    //点击退出
    connect(quite,&QAction::triggered,[=](){
        this->close();
    });
    myPushButton* returnBut = new  myPushButton(":/res/BackButton.png",":/res/BackButtonSelected.png");
    returnBut->setParent(this);
    returnBut->move(this->width()-returnBut->width(),this->height()-returnBut->height());

    connect(returnBut,&QPushButton::clicked,[=](){
            emit this->ChooseLevBack();
            this->close();
    });

    //创建关卡按钮
        for(int i = 0 ; i < 20;i++)
        {
            myPushButton * menuBtn = new myPushButton(":/res/LevelIcon.png");
            menuBtn->setParent(this);
            menuBtn->move(120 + (i%4)*100 , 300+ (i/4)*100);

            connect(menuBtn,&myPushButton::clicked,[=](){
//               QString str= QString("选择第%1关").arg(i+1);//arg方法，用来格式化字符串
//               //这个方法允许你往字符串中插入参数，%1对应一个占位符连接一个arg()，%1表示第一个参数
//               //%2表示第二个参数 QString("选择第%1关，第%2次尝试").arg(i+1).arg(j)
//               qDebug()<<str;
                //chooseSound->play();
                if(play==nullptr)
                {
                    this->hide();
                    play=new playScene(i+1);
                    play->setGeometry(this->geometry());
                    play->show();   //进入关卡场景
                    //开始监听
                    connect(play,&playScene::chooseSceneBack,[=](){
                        this->setGeometry(play->geometry());
                        this->show();
                        delete play;
                        play=nullptr;
                    });
                }

            });

            //按钮上显示的文字
            QLabel * label = new QLabel;
            label->setParent(this);
            label->setFixedSize(menuBtn->width(),menuBtn->height());
            label->setText(QString::number(i+1));
            label->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter); //设置居中
            label->move(120 + (i%4)*100 , 300+ (i/4)*100);
            label->setAttribute(Qt::WA_TransparentForMouseEvents);  //鼠标事件穿透
        }


}

void ChooseLevelScene::paintEvent(QPaintEvent *)
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
    painter.drawPixmap( (this->width() - pix.width())*0.5,30,pix.width(),pix.height(),pix);

}
