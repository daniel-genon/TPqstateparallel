#ifndef TRANSDEMARRE_H
#define TRANSDEMARRE_H

#include <QtWidgets/QKeyEventTransition>
#include "joueur.h"
class TransDemarre : public QKeyEventTransition
{
public:
    TransDemarre(Joueur *vjoueur, QEvent::Type t, int k);
protected:
    virtual void onTransition(QEvent *);
private:
    Joueur * joueur;
    int touche;
};

#endif // TRANSDEMARRE_H
