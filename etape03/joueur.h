#ifndef JOUEUR_H
#define JOUEUR_H

#include "../vue.h"
#include "../objetmobile.h"
#include "borneappel.h"

class Joueur : public ObjetMobile
{
Q_OBJECT
public:
    Joueur( LBorne *ptrb );
    ~Joueur();
    void ReInitialiser();
    void InverserDeplacement();
    void MajMouvement();
    void InitPtrVue(Vue *vpvue );
    virtual void FixerObjet();

    BorneAppel *TestCollision();

private slots:
    void BorneContact();

private:
    int      vitesse;
    int      duree;
    Vue      *pvue;
    QPointF  npos;

    LBorne      *pborne;
    QState      *Gauche;
    QState  *Garage;
    QState  *Illusion;

};

#endif // JOUEUR_H
