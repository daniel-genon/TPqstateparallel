#ifndef BOUGE_H
#define BOUGE_H

#include "joueur.h"
class Bouge : public QState
{
    Q_OBJECT
public:
    Bouge( Joueur *vjoueur, QState *vparent = 0 );
protected:
    virtual void onEntry(QEvent *);
    virtual void onExit(QEvent *);
private:
    Joueur * joueur;
};

#endif // BOUGE_H
