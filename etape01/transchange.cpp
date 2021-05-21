#include "tranchange.h"

TransChange::TransChange(Joueur *vjoueur, QEvent::Type t, int k) : QKeyEventTransition(vjoueur, t, k)
{
    joueur = vjoueur;
    touche = k;
}
bool TransChange::eventTest(QEvent *evt)
{
    if (!QKeyEventTransition::eventTest(evt))
        return false;

    return (touche != joueur->CodeDirection());
}
void TransChange::onTransition(QEvent *)
{
    joueur->InitDirection(touche);
}
