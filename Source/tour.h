#ifndef TOUR_H
#define TOUR_H

#include <QWidget>
#include <QPainter>
#include <vector>
#include <QtGui>
#include <QMessageBox>
#include <QMouseEvent>
#include <iostream>

#include "bloc.h"
class Tour : public QWidget
{
Q_OBJECT
public:
    Tour();
    Tour(int nbBlocs);
    Tour(QWidget *parent,int nom);
    ~Tour();
    int ajouterBloc(Bloc *bloc);
    void supprimerBloc();
    void vider();
    void paintEvent(QPaintEvent *e);

    int getNbBlocs()const;
    Bloc* at(int i)const;
    Bloc* dernierBloc();


    void setCliquee(bool b);
    bool getCliquee()const;

    void mousePressEvent(QMouseEvent *ev);

signals:
    void tourCliquee();
private:
    std::vector<Bloc*> blocs;
    bool    clique;

private slots:
    void cliquee();
};

#endif // TOUR_H
