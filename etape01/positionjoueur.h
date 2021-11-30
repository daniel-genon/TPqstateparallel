#ifndef POSITIONJOUEUR_H
#define POSITIONJOUEUR_H

#include "joueur.h"
class PositionJoueur : public QState
{
public:
    PositionJoueur(Joueur *vjoueur, qreal vrot, QState *vparent = 0 );
protected:
    virtual void onEntry(QEvent *);
    virtual void onExit(QEvent *);
private:
    Joueur *joueur;
    qreal   rotation;
};

#endif // POSITIONJOUEUR_H
