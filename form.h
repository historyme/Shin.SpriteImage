#ifndef FORM_H
#define FORM_H

#include <QWidget>
#include "spriteimage.h"

namespace Ui {
class Form;
}

class Form : public QWidget
{
    Q_OBJECT

public:
    explicit Form(QWidget *parent = 0);
    ~Form();

private:
    Ui::Form *ui;
    int x;
    int y;

    SpriteImage *spimg;

    void KeyUpfunc(QKeyEvent *);
    void KeyDownfunc(QKeyEvent *);
    void KeyLeftfunc(QKeyEvent *);
    void KeyRightfunc(QKeyEvent *);


protected:
    void keyPressEvent(QKeyEvent *event);
};

#endif // FORM_H
