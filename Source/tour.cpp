#include "tour.h"

Tour::Tour()
{
    setHidden(false);
    setFixedSize(400,650);
    //setCursor(Qt::PointingHandCursor);
    clique=false;
connect(this,SIGNAL(tourCliquee()),this,SLOT(cliquee()));

}

Tour::Tour(int nbBlocs)
{
    setHidden(false);
    setFixedSize(400,650);
    //setCursor(Qt::PointingHandCursor);
    clique=false;
}

Tour::Tour(QWidget *parent,int nom)
{
    setParent(parent);
    setHidden(false);
    switch(nom)
    {
    case 0: setGeometry(50,80,400,570);
        break;
    case 1: setGeometry(450,80,400,570);
        break;
    case 2: setGeometry(850,80,400,570);
        break;
    default:
        break;
    }


    setCursor(Qt::PointingHandCursor);
    clique=false;
    connect(this,SIGNAL(tourCliquee()),this,SLOT(cliquee()));

}

Tour::~Tour()
{

}


void Tour::paintEvent(QPaintEvent *e)
{
    QPainter *painter=new QPainter(this);
    QPoint point(0,0);
    painter->drawPixmap(point,QPixmap("TourW.png"));


}

int Tour::getNbBlocs() const{return blocs.size();}

Bloc *Tour::at(int i) const{return blocs[i];}

Bloc* Tour::dernierBloc()
{
    if(!blocs.empty()) return blocs[blocs.size()-1];
}

void Tour::setCliquee(bool b)
{
    clique=b;

}



bool Tour::getCliquee() const
{
    return clique;
}

void Tour::cliquee()
{
    clique=true;
}

void Tour::mousePressEvent(QMouseEvent *ev)
{
   emit tourCliquee();
   //emit FenetrePrincipale::fenClique();

}


int Tour::ajouterBloc(Bloc *bloc)
{
    if(!blocs.empty())
    {
        if(blocs[blocs.size()-1]->getNom() < bloc->getNom())
        {
    bloc->setParent(this);
    bloc->actualiser(blocs.size());
    blocs.push_back(bloc);
        return 0;
        }
        else
        {
            QMessageBox::critical(this, "ERREUR", "En essayant d’effectuer ce déplacement vous enfreignez la règle du jeu !");
            return -1;
        }
    }
    else
    {
        bloc->setParent(this);
        bloc->actualiser(blocs.size());

        blocs.push_back(bloc);
        return 0;
    }
    }

void Tour::supprimerBloc()
{
    if(!blocs.empty())
    {
    blocs.pop_back();
    }
}

void Tour::vider()
{
    if(!blocs.empty())
    {   int a=blocs.size();
        for(int i=0;i<a;i++)
        {   std::cerr<<"Nom du BLOC : "<<blocs[a-i-1]->getNom()<<"\n";
            blocs[a-i-1]->setHidden(true);
            blocs[a-i-1]->setParent(0);
            delete blocs[a-i-1];
            blocs.pop_back();
        }
    }
}
