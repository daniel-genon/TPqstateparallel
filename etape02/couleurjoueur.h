#ifndef COULEURJOUEUR_H
#define COULEURJOUEUR_H

#include "joueur.h"
class CouleurJoueur : public QState
{
    Q_OBJECT
public:
    CouleurJoueur( Joueur *vjoueur, const QString &vcoul, QState *vparent = 0 );
protected:
    virtual void onEntry(QEvent *);
    virtual void onExit(QEvent *);
private:
    Joueur * joueur;
    QString couleur;
};

#endif // COULEURJOUEUR_H
