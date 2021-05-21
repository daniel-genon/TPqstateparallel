#include "bouge.h"

Bouge::Bouge(Joueur *vjoueur, int vdir, QState *vparent ) : QState(vparent)
{
    joueur    = vjoueur;
    direction = vdir;
}
void Bouge::onEntry(QEvent *)
{
    joueur->InitDirection(direction);
    joueur->MajMouvement();
}
void Bouge::onExit(QEvent *)
{

}
