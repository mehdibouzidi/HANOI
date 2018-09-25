#ifndef BLOC_H
#define BLOC_H

#include <QWidget>
#include <QPainter>
#include <QPushButton>


class Bloc : public QPushButton
{

public:
    Bloc();
    //Bloc(int nom, int nbBlocs);
    Bloc(QWidget *parent,int nom, int nbBlocs);
    void actualiser(int nbBlocs);
    int getNom()const;
    ~Bloc();
private:
    int nom;
};

#endif // BLOC_H
