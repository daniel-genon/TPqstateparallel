#include "joueur.h"
#include <QPropertyAnimation>
#include <QFinalState>
#include "bouge.h"
#include "couleurjoueur.h"
#include "positionjoueur.h"
#include "arret.h"
#include "transdemarre.h"
#include "tranchange.h"
#include <QMessageBox>

Joueur::Joueur()
{
    duree = 150;
    vitesse=0;
    setZValue(4);
    setFlags(QGraphicsItem::ItemIsFocusable);
    animationdelobjet = new QPropertyAnimation(this,"pos");

    machine = new QStateMachine(this);

    QState *stop_P = new QState( QState::ParallelStates, machine );
        Arret *arret = new Arret(this, stop_P);
        CouleurJoueur *sanscouleur  = new CouleurJoueur(this, QString(":/motif/joueur.png"), stop_P);
        PositionJoueur *debout   = new PositionJoueur(this, 0, stop_P);
    machine->setInitialState(stop_P);

    QState *conteneur = new QState(machine);
    conteneur->addTransition(animationdelobjet, SIGNAL(finished()), arret);

    QKeyEventTransition *stopjoueur = new QKeyEventTransition(this, QEvent::KeyPress,Qt::Key_5);
      stopjoueur->setTargetState(arret);
      conteneur->addTransition(stopjoueur);

      QState *Droite_P = new QState( QState::ParallelStates, conteneur );
          Bouge *bougeadroite   = new Bouge(this, Droite_P);
          CouleurJoueur *couleurbleue  = new CouleurJoueur(this, QString(":/motif/jvb.png"), Droite_P);
          PositionJoueur *PlatDroite   = new PositionJoueur(this, 90, Droite_P);

      QState *Gauche_P = new QState( QState::ParallelStates, conteneur );
          Bouge *bougeagauche   = new Bouge(this, Gauche_P);
          CouleurJoueur *couleurrouge  = new CouleurJoueur(this, QString(":/motif/jvr.png"), Gauche_P);
          PositionJoueur *platgauche   = new PositionJoueur(this, 270, Gauche_P);

      QState *Haut_P = new QState( QState::ParallelStates, conteneur );
          Bouge *bougeenhaut     = new Bouge(this, Haut_P);
          CouleurJoueur *couleurjaune  = new CouleurJoueur(this, QString(":/motif/jvj.png"), Haut_P);
          PositionJoueur *debouthaut   = new PositionJoueur(this, 0, Haut_P);

      QState *Bas_P = new QState( QState::ParallelStates, conteneur );
          Bouge *bougeenbas       = new Bouge(this, Bas_P);
          CouleurJoueur *couleurmauve  = new CouleurJoueur(this,QString(":/motif/jvm.png"), Bas_P);
          PositionJoueur *deboutbas    = new PositionJoueur(this, 180, Bas_P);


              TransDemarre *SversG = new TransDemarre(this, QEvent::KeyPress, Qt::Key_4);
                  SversG->setTargetState(bougeagauche);
                  arret->addTransition(SversG);
              TransDemarre *SversD = new TransDemarre(this, QEvent::KeyPress, Qt::Key_6);
                  SversD->setTargetState(bougeadroite);
                  arret->addTransition(SversD);
              TransDemarre *SversB = new TransDemarre(this, QEvent::KeyPress, Qt::Key_2);
                  SversB->setTargetState(bougeenbas);
                  arret->addTransition(SversB);
              TransDemarre *SversH = new TransDemarre(this, QEvent::KeyPress, Qt::Key_8);
                  SversH->setTargetState(bougeenhaut);
                  arret->addTransition(SversH);

    TransChange *versG = new TransChange(this, QEvent::KeyPress, Qt::Key_4);
        versG->setTargetState(bougeagauche);
        conteneur->addTransition(versG);
    TransChange *versD = new TransChange(this, QEvent::KeyPress, Qt::Key_6);
        versD->setTargetState(bougeadroite);
        conteneur->addTransition(versD);
    TransChange *versH = new TransChange(this, QEvent::KeyPress, Qt::Key_8);
        versH->setTargetState(bougeenhaut);
        conteneur->addTransition(versH);
    TransChange *versB = new TransChange(this, QEvent::KeyPress, Qt::Key_2);
        versB->setTargetState(bougeenbas);
        conteneur->addTransition(versB);

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
    case Qt::Key_8 :{trajet=npos.y();npos.setY(0);}break;//haut
    case Qt::Key_2 :{trajet=scene()->height()-size().height()-npos.y(); npos.setY(scene()->height() - size().height());}break;//bas
    default : bougeok=false;
    }
    if (bougeok)
    {
        animationdelobjet->setEndValue(npos);
        animationdelobjet->setDuration(vitesse*trajet);
        animationdelobjet->start();
    }
}
