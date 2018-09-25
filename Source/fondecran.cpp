#include "fondecran.h"

FondEcran::FondEcran(QWidget *parent) : QWidget(parent)
{
    setGeometry(0,0,1280,720);
    //setParent(parent);
    image= new QString("back1.png");
}

FondEcran::FondEcran(QWidget *parent, QString fond)
{
    setGeometry(0,0,1280,720);
    setParent(parent);
    image= new QString(fond);

}

void FondEcran::paintEvent(QPaintEvent *e)
{
    QPainter *painter=new QPainter(this);
    QPoint point(0,0);
    painter->drawPixmap(point,QPixmap(*image));
}

