#include "form.h"
#include "ui_form.h"

#include <QWidget>
#include <QtCore>
#include <QtGui>

Form::Form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form)
{
    ui->setupUi(this);
    Q_INIT_RESOURCE(res);

    QPixmap *Pixmap = new QPixmap(":/img/2.png");
    spimg = new SpriteImage(this);
    spimg->SetImageFile(Pixmap,5,6);
    spimg->SetTime(50);
    spimg->RunSprite();
    x = 0;
    y = 0;
}

Form::~Form()
{
    delete ui;
}


void Form::keyPressEvent(QKeyEvent *event)
{
    switch (event->key())
    {
    case Qt::Key_Up:
        KeyUpfunc(event);
        break;
    case Qt::Key_Down:
        KeyDownfunc(event);
        break;
    case Qt::Key_Left:
        KeyLeftfunc(event);
        break;
    case Qt::Key_Right:
        KeyRightfunc(event);
        break;
    default:
        break;
    }
}

void Form::KeyDownfunc(QKeyEvent *)
{
    y+=10;
    if(600 > y && 0 < y)
    {
       spimg->SetPosition(x,y);
    }
    else
    {
         y = 0;
    }
}

void Form::KeyLeftfunc(QKeyEvent *)
{
    x-=10;
    if(800 > x && 0 < x)
    {
       spimg->SetPosition(x,y);
    }
    else
    {
         x = 0;
    }
}

void Form::KeyRightfunc(QKeyEvent *)
{
    x+=10;
    if(800 > x && 0 < x)
    {
       spimg->SetPosition(x,y);
    }
    else
    {
         x = 0;
    }
}

void Form::KeyUpfunc(QKeyEvent *)
{
    y-=10;
    if(800 > x && 0 < x)
    {
       spimg->SetPosition(x,y);
    }
    else
    {
         y = 0;
    }
}
