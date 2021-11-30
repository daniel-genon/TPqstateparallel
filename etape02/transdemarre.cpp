#include "transdemarre.h"
TransDemarre::TransDemarre(Joueur *vjoueur, QEvent::Type t, int k) : QKeyEventTransition(vjoueur, t, k)
{
    joueur = vjoueur;
    touche = k;
}
void TransDemarre::onTransition(QEvent *)
{
    joueur->InitDirection(touche);
}

