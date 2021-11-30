#include "bouge.h"

Bouge::Bouge( Joueur *vjoueur, QState *vparent ) : QState(vparent)
{
    joueur = vjoueur;
}
void Bouge::onEntry(QEvent *)
{
    joueur->MajMouvement();
}
void Bouge::onExit(QEvent *){}
