#include "bloc.h"
/*
Bloc::Bloc()
{
    setHidden(false);

    switch(nom)
    {
    case 1: setFixedSize(250,80);
        break;
    case 2: setFixedSize(200,80);
        break;
    case 3: setFixedSize(160,80);
        break;
    case 4: setFixedSize(120,80);
        break;
    case 5: setFixedSize(80,80);
        break;
    default :
        break;
    }
}

Bloc::Bloc(int nom, int nbBlocs)
{
    this->nom=nom;
   // setHidden(false);

    switch(nom)
    {
    case 1: setGeometry(75,477-nbBlocs*80,250,80);
        break;
    case 2: setGeometry(100,477-nbBlocs*80,200,80);
        break;
    case 3: setGeometry(120,477-nbBlocs*80,160,80);
        break;
    case 4: setGeometry(140,477-nbBlocs*80,120,80);
        break;
    case 5: setGeometry(160,477-nbBlocs*80,80,80);
        break;
    default :
        break;
    }
    setParent(0);
}

Bloc::Bloc(QWidget *parent, int nom, int nbBlocs)
{
    this->nom=nom;
    setParent(parent);
    setHidden(false);

    switch(nom)
    {
    case 1: setGeometry(75,477-nbBlocs*80,250,80); //setIcon(QIcon("dep1.png"));  setIconSize(QSize(250,80));
        break;
    case 2: setGeometry(100,477-nbBlocs*80,200,80); //setIcon(QIcon("dep2.png")); setIconSize(QSize(200,80));
        break;
    case 3: setGeometry(120,477-nbBlocs*80,160,80); //setIcon(QIcon("dep3.png")); setIconSize(QSize(160,80));
        break;
    case 4: setGeometry(140,477-nbBlocs*80,120,80); //setIcon(QIcon("dep4.png")); setIconSize(QSize(120,80));
        break;
    case 5: setGeometry(160,477-nbBlocs*80,80,80);  //setIcon(QIcon("dep5.png")); setIconSize(QSize(80,80));
        break;
    default :
        break;
    }

    setCursor(Qt::PointingHandCursor);
}*/

/*void Bloc::paintEvent(QPaintEvent *e)
{
    painter=new QPainter(this);

    QPoint point(0,0);
    QString image("dep");
    QString no(QString::number(nom));
    image+=no+".png";
    painter->drawPixmap(point,QPixmap(image));

}*/

Bloc::Bloc(QWidget *parent, int nom, int nbBlocs)
{
    this->nom=nom;
    setParent(parent);
    setHidden(false);

    switch(nom)
    {
    case 1: setGeometry(75,477-nbBlocs*80,250,80); setIcon(QIcon("dep1.png"));  setIconSize(QSize(250,80));
        break;
    case 2: setGeometry(100,477-nbBlocs*80,200,80); setIcon(QIcon("dep2.png")); setIconSize(QSize(200,80));
        break;
    case 3: setGeometry(120,477-nbBlocs*80,160,80); setIcon(QIcon("dep3.png")); setIconSize(QSize(160,80));
        break;
    case 4: setGeometry(140,477-nbBlocs*80,120,80); setIcon(QIcon("dep4.png")); setIconSize(QSize(120,80));
        break;
    case 5: setGeometry(160,477-nbBlocs*80,80,80);  setIcon(QIcon("dep5.png")); setIconSize(QSize(80,80));
        break;
    default :
        break;
    }

    setCursor(Qt::PointingHandCursor);

}

void Bloc::actualiser(int nbBlocs)
{
    setGeometry(this->x(),477-nbBlocs*80,this->width(),this->height());
    setHidden(false);
}



int Bloc::getNom() const{return nom;}

Bloc::~Bloc()
{

}

