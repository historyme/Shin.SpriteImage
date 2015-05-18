#ifndef SPRITEIMAGE_H
#define SPRITEIMAGE_H

#include <QObject>
#include <QWidget>
#include <QPixmap>


class SpriteImage : public QWidget
{
    Q_OBJECT
public:
    explicit SpriteImage(QWidget *parent = 0);
    ~SpriteImage();

    int SetImageFile(QPixmap *Pixmap,int UnitX,int UnitY);

    int RunSprite(void);
    int SetTime(int delay);
    void SetPosition(int X,int Y);
private:
    //定义运行状态
    enum
    {
        STATUS_IDLE = 0,
        STATUS_RUN,
        STATUS_STOP,
        STATUS_PAUSE,
        STATUS_RESUME,
    };

    //声明精灵类的输入结构
    typedef struct Position_XY
    {
        int X;
        int Y;
    }PositionXY;

    typedef struct Sprite_Image_Data
    {
        PositionXY imgXY; //定义输入图片的高
                          //定义输入图片的宽
        PositionXY imgHW;//定义每个单元的高
                         //定义每个单元的宽
        PositionXY UnitXY; //定义宽的单元个数
                           //定义高的单元个数
        int imgTime; // 图片刷新时间
    }SpriteImageData;

    SpriteImageData priv_ImgData;
    QPixmap *imgPixmap;
    QPixmap *imgPixTmp;
    QTimer *timer;

    bool priv_IsTimeSet;
    int priv_Status;
    int count;

private slots:
    void SpriteUpdate(void);
protected:
    void paintEvent(QPaintEvent *);
};

#endif // SPRITEIMAGE_H
