#include <QApplication>
#include <QtGui>
#include <QTranslator>
#include <QLocale>
#include <QLibraryInfo>

#include "fenetreprincipale.h"



int main(int argc,char *argv[])
{
     QApplication app(argc,argv);

QString locale = QLocale::system().name().section('_', 0, 0);
     QTranslator translator;

     translator.load(QString("fenetreprincipale_") + locale);
    app.installTranslator(&translator);

    FenetrePrincipale fenetre;
    fenetre.show();

return app.exec();
}
