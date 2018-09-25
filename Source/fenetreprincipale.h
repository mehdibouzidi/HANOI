#ifndef FENETREPRINCIPALE_H
#define FENETREPRINCIPALE_H

#include <QMainWindow>
#include <QLCDNumber>
#include <QtGui>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QSpinBox>
#include <QPushButton>
#include <iostream>

#include "tour.h"
#include "fondecran.h"
namespace Ui {
class FenetrePrincipale;
}

class FenetrePrincipale : public QMainWindow
{
    Q_OBJECT

public:
    explicit FenetrePrincipale(QWidget *parent = 0);
    ~FenetrePrincipale();
    void deplacement ();
    void mousePressEvent(QMouseEvent *ev);
    void actualiser();
signals:
    void fenClique();
private slots:
    void lance();
    void mouvement();
    void nouvellePartie();
    void annuler();
    void statistiques();
    void aPropos();

private:
    Ui::FenetrePrincipale *ui;
    QLCDNumber            *compteur;
    QLabel                *label;
    QLabel                *scoreParfait;
    QLabel                *nombreDepalcement;
    QSpinBox              *nombreBlocs;
    QPushButton           *okBtn;
    QWidget               *espaceJeu;
    std::vector<Tour*>     tours;
    int                    aDeplacer[2];
    int                    nbCliques;
    bool                   estClique;
    int                    x;
    int                    y;
    bool lancee;
};

#endif // FENETREPRINCIPALE_H
