#ifndef TRANSCHANGE_H
#define TRANSCHANGE_H

#include <QtWidgets/QKeyEventTransition>
#include "joueur.h"
class TransChange : public QKeyEventTransition
{
public:
    TransChange(Joueur *vjoueur, QEvent::Type t, int k);
protected:
    virtual bool eventTest(QEvent *evt);
    virtual void onTransition(QEvent *);
private:
    Joueur * joueur;
    int touche;
};

#endif // TRANSCHANGE_H
