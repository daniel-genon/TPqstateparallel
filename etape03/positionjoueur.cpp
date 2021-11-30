#include "positionjoueur.h"

PositionJoueur::PositionJoueur( Joueur *vjoueur, qreal vrot, QState *vparent ) : QState(vparent)
{
    joueur      = vjoueur;
    rotation    = vrot;
}
void PositionJoueur::onEntry(QEvent *)
{
    joueur->setRotation(rotation);
}
void PositionJoueur::onExit(QEvent *)
{

}
