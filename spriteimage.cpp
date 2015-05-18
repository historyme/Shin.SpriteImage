#include "spriteimage.h"

#include <QPainter>
#include <QPixmap>
#include <QBitmap>
#include <QWidget>
#include <QTextStream>
#include <QTimer>

using namespace std;

SpriteImage::SpriteImage(QWidget *parent)
    : QWidget(parent)
{
    setAttribute(Qt::WA_TranslucentBackground);//这个是widget的背景弄透明

    imgPixmap = new QPixmap();
    imgPixTmp = new QPixmap();
    timer = new QTimer(this);
    memset(&priv_ImgData,0,sizeof(SpriteImageData));
    priv_IsTimeSet = false;
    priv_Status = STATUS_IDLE;
    count = 0;

}

SpriteImage::~SpriteImage()
{

}

//设定载入的文件信息
int SpriteImage::SetImageFile(QPixmap *Pixmap,int UnitX,int UnitY)
{
    QTextStream out(stdout);
    imgPixmap = Pixmap;
    int hight= imgPixmap->height();
    int width = imgPixmap->width();
    int UnitH,UnitW;

    //计算图片中的位置
    UnitH = hight%UnitY;
    UnitW = width%UnitX;
    if((0!=UnitH )&& (0!=UnitW))
    {
        out <<"img error :not a standardized format!\n";
        return EXIT_FAILURE;
    }
    else
    {
        UnitH = hight/UnitY;
        UnitW = width/UnitX;
        if((0 >=UnitH )&&(0 >= UnitW))
        {
            out <<"img error:not a img file!\n";
            return EXIT_FAILURE;
        }
    }

    //保存文件数据到私有全局变量
    priv_ImgData.imgXY.X = width;
    priv_ImgData.imgXY.Y = hight;
    priv_ImgData.imgHW.X = UnitW;
    priv_ImgData.imgHW.Y = UnitH;
    priv_ImgData.UnitXY.X = UnitX;
    priv_ImgData.UnitXY.Y = UnitY;

    return EXIT_SUCCESS;
}

//精灵动画中的时间设定
int SpriteImage::SetTime(int delay)
{
    QTextStream out(stdout);
    if(0 >= delay)
    {
        out<<"set time error :not a time format!\n";
        return EXIT_FAILURE;
    }

    priv_ImgData.imgTime = delay;
    priv_IsTimeSet = true;

    return EXIT_SUCCESS;
}

//精灵动画的控制接口
int SpriteImage::RunSprite(void)
{
    priv_Status = STATUS_RUN;

    timer->start(priv_ImgData.imgTime);
    connect(timer,SIGNAL(timeout()),this,SLOT(SpriteUpdate()));
    show();

    return EXIT_SUCCESS;
}

//定时器处理函数
void SpriteImage::SpriteUpdate(void)
{   
    int X, Y;
    count++;
    if(count >= priv_ImgData.UnitXY.X * priv_ImgData.UnitXY.Y)
    {
        count = 0;
    }
    X = priv_ImgData.imgHW.X * (count % priv_ImgData.UnitXY.X);
    Y = priv_ImgData.imgHW.Y * (count / priv_ImgData.UnitXY.X);
    *imgPixTmp = imgPixmap->copy(X,Y,priv_ImgData.imgHW.X,priv_ImgData.imgHW.Y);
    resize(imgPixTmp->size());
    setMask(QBitmap(imgPixTmp->mask()));
    update();
}

//设定图片显示位置
void SpriteImage::SetPosition(int X,int Y)
{
    setGeometry(X,Y,priv_ImgData.imgHW.X,priv_ImgData.imgHW.Y);
}

void SpriteImage::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawPixmap(0,0,*imgPixTmp);
}
