#ifndef JOUEUR_H
#define JOUEUR_H

#include "../vue.h"
#include "../objetmobile.h"
class Joueur : public ObjetMobile
{
Q_OBJECT
public:
    Joueur();
    void ReInitialiser();
    void InverserDeplacement();
    void MajMouvement();
    void InitPtrVue(Vue *vpvue );
    virtual void FixerObjet();
private:
    int      vitesse;
    int      duree;
    Vue      *pvue;
    QPointF  npos;
};

#endif // JOUEUR_H
