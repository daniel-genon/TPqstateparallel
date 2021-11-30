#include "couleurjoueur.h"

CouleurJoueur::CouleurJoueur(Joueur *vjoueur,const QString &vcoul, QState *vparent ) : QState(vparent)
{
    joueur  = vjoueur;
    couleur = QString(vcoul);
}
void CouleurJoueur::onEntry(QEvent *)
{
    joueur->InitImage(couleur);
    joueur->setTransformOriginPoint( joueur->boundingRect().center());
}
void CouleurJoueur::onExit(QEvent *)
{

}
