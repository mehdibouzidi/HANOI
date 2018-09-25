#include "fenetreprincipale.h"
#include "ui_fenetreprincipale.h"

FenetrePrincipale::FenetrePrincipale(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FenetrePrincipale)
{
    ui->setupUi(this);
    FondEcran *fon=new FondEcran(ui->centralwidget,"back1.png");
    lancee=false;
    /********** Layouts **********/
    QVBoxLayout *layoutGeneral  = new QVBoxLayout;
    QHBoxLayout *layoutEntete   = new QHBoxLayout;
    QHBoxLayout *layoutTour     = new QHBoxLayout;

    QPalette pal;
    pal.setColor(QPalette::WindowText,Qt::white);
    label = new QLabel("Nombre de disques : ");
    label->setFont(QFont("Calibri",12,QFont::Bold));
    label->setPalette(pal);
    scoreParfait = new QLabel;
    scoreParfait->setFont(QFont("Calibri",12,QFont::Bold));
    scoreParfait->setPalette(pal);
    scoreParfait->setHidden(true);
    nombreDepalcement = new QLabel("Nombre de déplacements : ");
    nombreDepalcement->setFont(QFont("Calibri",12,QFont::Bold));
    nombreDepalcement->setPalette(pal);
    nombreDepalcement->setHidden(true);
    nombreBlocs     = new QSpinBox;
    nombreBlocs->setMaximum(5); nombreBlocs->setMinimum(3);
    okBtn           = new QPushButton("Lancer");
    compteur        = new QLCDNumber;
    compteur->setDigitCount(2);
    compteur->setFixedSize(40,40);
    compteur->setHidden(true);

    espaceJeu       = new QWidget;

    QWidget *widgetFantome = new QWidget;
    widgetFantome->setFixedSize(900,20);
    layoutEntete->addWidget(label);
    layoutEntete->addWidget(nombreBlocs);
    layoutEntete->addWidget(okBtn);
    layoutEntete->addWidget(nombreDepalcement);
    layoutEntete->addWidget(compteur);
    layoutEntete->addWidget(scoreParfait);
    layoutEntete->addWidget(widgetFantome);

    layoutGeneral->addLayout(layoutEntete);
    layoutGeneral->addWidget(espaceJeu);
    Tour *tour;
    for(int i=0;i<3;i++)
    {
        tour = new Tour(ui->centralwidget,i);
        tours.push_back(tour);
    }

    espaceJeu->setLayout(layoutTour);

    ui->centralwidget->setLayout(layoutGeneral);
    setFixedSize(1280,720);



    connect(okBtn,SIGNAL(clicked()),this,SLOT(lance()));
    connect(this,SIGNAL(fenClique()),this,SLOT(mouvement()));

    aDeplacer[0]=-1; aDeplacer[1]=-1;
    nbCliques=0;
    estClique=false;
    setCursor(Qt::PointingHandCursor);


    /*********************** Les Menus ***********************/
    QMenu *menuFichier = menuBar()->addMenu("&Partie");
    QMenu *menuInfos = menuBar()->addMenu("&?");

    QAction *actionNouvellePartie = new QAction("Nouvelle partie", this);
    QAction *actionAnnuler = new QAction("Annuler", this);
    QAction *actionStatistiques = new QAction("Statistiques", this);
    QAction *actionQuitter = new QAction("Quitter", this);
    QAction *actionAPropos = new QAction("À propos", this);

    actionNouvellePartie->setShortcut(QKeySequence("Ctrl+N"));
    actionAnnuler->setShortcut(QKeySequence("Ctrl+Z"));
    actionStatistiques->setShortcut(QKeySequence("F4"));
    actionQuitter->setShortcut(QKeySequence("Ctrl+Q"));

    actionNouvellePartie->setIcon(QIcon("gamepad.png"));
    actionAnnuler->setIcon(QIcon("game50.png"));
    actionStatistiques->setIcon(QIcon("games18.png"));
    actionQuitter->setIcon(QIcon("door13.png"));
    actionAPropos->setIcon(QIcon("info2.png"));

    menuFichier->addAction(actionNouvellePartie);
    menuFichier->addSeparator();
    menuFichier->addAction(actionAnnuler);
    menuFichier->addSeparator();
    menuFichier->addAction(actionStatistiques);
    menuFichier->addSeparator();
    menuFichier->addAction(actionQuitter);

    menuInfos->addAction(actionAPropos);

    connect(actionQuitter,SIGNAL(triggered()),qApp,SLOT(quit()));
    connect(actionNouvellePartie,SIGNAL(triggered()),this,SLOT(nouvellePartie()));
    connect(actionAnnuler,SIGNAL(triggered()),this,SLOT(annuler()));
    connect(actionStatistiques,SIGNAL(triggered()),this,SLOT(statistiques()));
    connect(actionAPropos,SIGNAL(triggered()),this,SLOT(aPropos()));
    /********* Paramètres Fenêtre **********/
    setWindowTitle("Tours de Hanoï");
    setWindowIcon(QIcon("ico.png"));

     ui->centralwidget->setFocus(Qt::OtherFocusReason);
}

FenetrePrincipale::~FenetrePrincipale()
{
    delete ui;
}

void FenetrePrincipale::deplacement()
{
    int a;
    a=tours[aDeplacer[1]]->ajouterBloc(tours[aDeplacer[0]]->dernierBloc());
   if(a==0)
   {
    tours[aDeplacer[0]]->supprimerBloc();
   }
    compteur->display(compteur->value()+1+a);

}

void FenetrePrincipale::mousePressEvent(QMouseEvent *ev)
{
    emit fenClique();

    x=ev->x();
    y=ev->y();

}

void FenetrePrincipale::actualiser()
{
    for(int i=0;i<tours.size();i++)
    {
        tours[i]->setCliquee(false);
    }
    nbCliques=0;
}

void FenetrePrincipale::lance()
{
    //QMessageBox::question(ui->centralwidget,"Nouvelle partie ?","Bravo, vous avez gagné ! Voulez-vous rejouer ?",QMessageBox::Yes | QMessageBox::No);
    lancee=true;
    int a;
    switch(nombreBlocs->value())
    {
    case 3 : a=7;
        break;
    case 4 : a=15;
        break;
    case 5 : a=31;
    }

    scoreParfait->setText(QString("Le score parfait est de %1 coups").arg(a));
    nombreDepalcement->setHidden(false);
    compteur->setHidden(false);
    scoreParfait->setHidden(false);

    nombreBlocs->setHidden(true);
    okBtn->setHidden(true);
    label->setHidden(true);
        Bloc *bloc;
    for(int i=0;i<nombreBlocs->value();i++)
    {
        bloc =new Bloc(tours[0],i+1,tours[0]->getNbBlocs());
         tours[0]->ajouterBloc(bloc);
    }

}


void FenetrePrincipale::mouvement()
{
    if(lancee)
    {
    estClique=true;

    nbCliques++;
    if(nbCliques==2)
    {
        if(x<=450 && 50<=x && y<=570 && 50<=y){tours[0]->setCliquee(true);}
        if(x<=850 && 450<x && y<=570 && 50<=y){tours[1]->setCliquee(true);}
        if(x<=1250 && 850<x && y<=570 && 50<=y){tours[2]->setCliquee(true);}
        for(int i=0;i<tours.size();i++)
        {
            if(tours[i]->getCliquee()) {aDeplacer[0]=i;}
        }
    }
    else if(nbCliques==4)
    {
        if(x<=450 && 50<=x && y<=570 && 50<=y){tours[0]->setCliquee(true);}
        if(x<=850 && 450<x && y<=570 && 50<=y){tours[1]->setCliquee(true);}
        if(x<=1250 && 850<x && y<=570 && 50<=y){tours[2]->setCliquee(true);}
        for(int i=0;i<tours.size();i++)
        {
            if(tours[i]->getCliquee() && i!=aDeplacer[0]) {aDeplacer[1]=i;}
        }
        deplacement();
        actualiser();

    }
    }

        if(tours[2]->getNbBlocs()==nombreBlocs->value())
        {
            if(compteur->value()==7)
            {
            int reponse=QMessageBox::question(ui->centralwidget,"Rejouer","Bravo vous avez atteint le score parfait ! Voulez-vous rejouez ?",QMessageBox::Yes | QMessageBox::No);
            if(reponse==QMessageBox::Yes)
            {
                nouvellePartie();
            }
            }
            else
            {
                QString score("Bravo vous avez gangé, votre score est de : ");
                score+=QString::number(compteur->value());
                score+=" coups.Ce score n'est pas parfait voulez-vous rejouez ?";
                int reponse=QMessageBox::question(ui->centralwidget,"Rejouer",score,QMessageBox::Yes | QMessageBox::No);
                if(reponse==QMessageBox::Yes)
                {
                    nouvellePartie();
                }
            }
       }


}

void FenetrePrincipale::nouvellePartie()
{   if(lancee)
    {
    lancee=false;
    label->setHidden(false);
    nombreBlocs->setHidden(false);
    nombreBlocs->setValue(3);
    okBtn->setHidden(false);

    scoreParfait->setHidden(true);
    nombreDepalcement->setHidden(true);
    compteur->setHidden(true);
    compteur->display(0);
    for(int i=0;i<tours.size();i++)
    {
        tours[i]->vider();
    }
    actualiser();
    }
}

void FenetrePrincipale::annuler()
{
    if(aDeplacer[0]!=-1 && aDeplacer[1]!=-1)
    {
        tours[aDeplacer[0]]->ajouterBloc(tours[aDeplacer[1]]->dernierBloc());
        tours[aDeplacer[1]]->supprimerBloc();
        compteur->display(compteur->value()-1);
    }
}

void FenetrePrincipale::statistiques()
{

}

void FenetrePrincipale::aPropos()
{
    //QMessageBox::information(ui->centralwidget,"À propos","Ce jeu a été créer par <strong>MehdiBOUZIDI© </strong> \nContact : <strong>mehdi.bouzidi.92@gmail.com<strong>/\n                                           23/09/2015");
    QWidget *aProp=new QWidget;
    aProp->setFixedSize(505,300);
    aProp->setHidden(false);
    aProp->setWindowTitle("À propos");
    QString stringPrincipe(" <strong>Principe :</strong> <br>Le problème des tours de Hanoï est un jeu de réflexion imaginé par le </br><br>mathématicien français <strong>Édouard Lucas</strong>,et consistant à déplacer des disques de</br><br>diamètres différents d'une tour de « départ » à une tour d'« arrivée » en passant</br> <br>par une tour « intermédiaire », et ceci en un minimum de coups, tout en respectant </br><br>les règles suivantes :</br> ");
    stringPrincipe+="<br>1.On ne peut déplacer plus d'un disque à la fois,</br>";
    stringPrincipe+="<br>2.On ne peut placer un disque que sur un autre disque plus grand que lui</br> <br>ou sur un emplacement vide.</br>";
    stringPrincipe+="<br> </br><br><strong>Remarque :</strong></br> <br> Un double clique sur la premiere tour, ensuite un double clique sur la seconde tour pour déplacer un disque </br> ";

    QLabel *principe = new QLabel(stringPrincipe);
    QLabel *info=new QLabel("<br>Ce programme a été créer par <strong>MehdiBOUZIDI© </strong><br>Contact : <strong>mehdi.bouzidi.92@gmail.com</strong> </br>");
    QLabel *date = new QLabel("<strong>23/09/2015</strong>");

    QVBoxLayout* layoutAProp=new QVBoxLayout;
    QGridLayout *layoutDate=new QGridLayout;
    layoutDate->addWidget(date,0,4,1,4);
    layoutAProp->addWidget(principe);
    layoutAProp->addWidget(info);
    layoutAProp->addLayout(layoutDate);

    aProp->setLayout(layoutAProp);
}

