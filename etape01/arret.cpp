#include "arret.h"
Arret::Arret( Joueur *vjoueur, QState *vparent) : QState(vparent)
{
    joueur = vjoueur;
}
void Arret::onEntry(QEvent *)
{
    joueur->FixerObjet();
    joueur->MajMouvement();
}
void Arret::onExit(QEvent *){}
