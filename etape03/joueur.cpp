#include "joueur.h"
#include <QtCore/QPropertyAnimation>
#include <QFinalState>
#include <QSignalTransition>
#include "bouge.h"
#include "couleurjoueur.h"
#include "positionjoueur.h"
#include "arret.h"
#include "transdemarre.h"
#include "transchange.h"
#include <QMessageBox>

Joueur::Joueur( LBorne *ptrb )
{
    pborne = ptrb;
    duree = 180;
//    duree = 50;// pour debug avec points d'arrêts
    vitesse=0;
    setZValue(4);
    setFlags(QGraphicsItem::ItemIsFocusable);
    animationdelobjet = new QPropertyAnimation(this,"pos");

    machine = new QStateMachine(this);

    Arret *arret = new Arret(this, machine);
    arret->setChildMode(QState::ParallelStates);
        CouleurJoueur *sanscouleur  = new CouleurJoueur(this, QString(":/motif/joueur.png"), arret);
        PositionJoueur *debout   = new PositionJoueur(this, 0, arret);
    machine->setInitialState(arret);

    QState *conteneur = new QState(machine);

    QKeyEventTransition *stopjoueur = new QKeyEventTransition(this, QEvent::KeyPress,Qt::Key_5);
      stopjoueur->setTargetState(arret);
      conteneur->addTransition(stopjoueur);

    Bouge *bougeadroite   = new Bouge(this, Qt::Key_6, conteneur);
    bougeadroite->setChildMode(QState::ParallelStates);
        CouleurJoueur *couleurbleue  = new CouleurJoueur(this, QString(":/motif/jvb.png"), bougeadroite);
        PositionJoueur *PlatDroite   = new PositionJoueur(this, 90, bougeadroite);
    conteneur->setInitialState(bougeadroite);
//-----------------------------------------------------------------

//Etude sur l'inversion du ChilMode parallèle<>exclusif :
// Premier cas de structure d'état parallèle parallèle<>exclusif
//
    Gauche = new QState(QState::ParallelStates, conteneur);
        Bouge *bougeagauche   = new Bouge(this, Qt::Key_4, Gauche);
        CouleurJoueur *couleurrouge  = new CouleurJoueur(this, QString(":/motif/jvr.png"), Gauche);
        PositionJoueur *platgauche   = new PositionJoueur(this, 270, Gauche);

// Deuxième cas de structure d'état parallèle parallèle<>exclusif
//
//    Bouge *bougeagauche   = new Bouge(this, Qt::Key_4, conteneur);
//    bougeagauche->setChildMode(QState::ParallelStates);
//        CouleurJoueur *couleurrouge  = new CouleurJoueur(this, QString(":/motif/jvr.png"), bougeagauche);
//        PositionJoueur *platgauche   = new PositionJoueur(this, 270, bougeagauche);
//        Illusion = new QState(bougeagauche);
//    Garage = conteneur;
//    Gauche = bougeagauche;

//-----------------------------------------------------------------
      TransDemarre *SversG = new TransDemarre(this, QEvent::KeyPress, Qt::Key_4);
          SversG->setTargetState(bougeagauche);
          arret->addTransition(SversG);
      TransDemarre *SversD = new TransDemarre(this, QEvent::KeyPress, Qt::Key_6);
          SversD->setTargetState(bougeadroite);
          arret->addTransition(SversD);

    TransChange *versG = new TransChange(this, QEvent::KeyPress, Qt::Key_4);
        versG->setTargetState(bougeagauche);
        conteneur->addTransition(versG);
    TransChange *versD = new TransChange(this, QEvent::KeyPress, Qt::Key_6);
        versD->setTargetState(bougeadroite);
        conteneur->addTransition(versD);

    bougeagauche->addTransition(animationdelobjet, SIGNAL(finished()), bougeadroite);
    bougeadroite->addTransition(animationdelobjet, SIGNAL(finished()), bougeagauche);

    connect(animationdelobjet,SIGNAL(valueChanged(QVariant)), this, SLOT(BorneContact()));

}
Joueur::~Joueur()
{
    if(Gauche) delete Gauche;
}
void Joueur::ReInitialiser()
{
    vitesse = scene()->width()/duree;
    FixerObjet();
    setPos((pvue->scene()->width()-size().width())/2,(pvue->scene()->height()-size().height())/2);
    show();
    BougeToi();
}
void Joueur::InitPtrVue(Vue *vpvue )
{
    pvue=vpvue;
    if (pvue==0){QMessageBox::information(NULL,"info","pas de scene");}
}
void Joueur::FixerObjet()
{
    direction = 0;
}
BorneAppel *Joueur::TestCollision()
{
    QList<QGraphicsItem*> lstobjet = collidingItems(Qt::IntersectsItemBoundingRect);

    for(int i=0;i<pborne->count();i++)
        if(lstobjet.indexOf(pborne->at(i))!=-1) return pborne->at(i);

    return nullptr;
}
void Joueur::BorneContact()
{
    if(!pborne->isEmpty())
    {
        if(BorneAppel *pbornecontact=TestCollision())
        {
            if(pbornecontact==pborne->first())
            {
                Gauche->setChildMode(QState::ExclusiveStates);
//Lignes à décommenter pour le deuxième cas de structure d'état parallèle<>exclusif
//                Illusion->setParent(Gauche);
//                Gauche->setInitialState(Illusion);
            }
            else
            {
//Ligne à décommenter pour le deuxième cas de structure d'état parallèle<>exclusif
//                Illusion->setParent(Garage);
                Gauche->setChildMode(QState::ParallelStates);
            }
        }
    }
}
void Joueur::MajMouvement()
{
    animationdelobjet->stop();
    if ( Immobile() ) return;
    int trajet;
    bool    bougeok=true;
    QPointF npos = pos();
    switch(CodeDirection())
    {
    case Qt::Key_4 :{trajet=npos.x();npos.setX(0);}break;//gauche
    case Qt::Key_6 :{trajet=scene()->width()-npos.x(); npos.setX(scene()->width()-size().width());}break;//droite
    default : bougeok=false;
    }
    if (bougeok)
    {
        animationdelobjet->setEndValue(npos);
        animationdelobjet->setDuration(vitesse*trajet);
        animationdelobjet->start();
    }
}

