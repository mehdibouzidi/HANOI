#ifndef FONDECRAN_H
#define FONDECRAN_H

#include <QWidget>
#include <QtGui>
#include <QPainter>
#include <QPaintEvent>
class FondEcran : public QWidget
{
    Q_OBJECT
public:
    explicit FondEcran(QWidget *parent = 0);
             FondEcran(QWidget *parent, QString fond);
    void paintEvent(QPaintEvent *e);

private:

    QString *image;
};

#endif // FONDECRAN_H
