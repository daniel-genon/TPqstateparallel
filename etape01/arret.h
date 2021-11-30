#ifndef ARRET_H
#define ARRET_H

#include "joueur.h"
class Arret : public QState
{
public:
    Arret( Joueur *vjoueur, QState *vparent = 0 );
protected:
    virtual void onEntry(QEvent *);
    virtual void onExit(QEvent *);
private:
    Joueur * joueur;
};

#endif // ARRET_H
