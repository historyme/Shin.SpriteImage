
//main.cpp
#include <QTextCodec>
#include <QApplication>


#include "form.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    Form w;
    w.show();
    return a.exec();
}
