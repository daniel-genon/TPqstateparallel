#include "transcouleur.h"

TransCouleur::TransCouleur(Joueur *vjoueur, const QString &vcoul, QEvent::Type t, int k) : QKeyEventTransition(vjoueur, t, k)
{
    joueur  = vjoueur;
    couleur = vcoul;
}
void TransCouleur::onTransition(QEvent *)
{
    joueur->InitImage(couleur);
    joueur->setTransformOriginPoint( joueur->boundingRect().center());
}

