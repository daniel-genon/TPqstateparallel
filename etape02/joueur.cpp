#include "joueur.h"
#include <QtCore/QPropertyAnimation>
#include <QtCore/QFinalState>
#include <QtCore/QSignalTransition>
#include "bouge.h"
#include "couleurjoueur.h"
#include "positionjoueur.h"
#include "arret.h"
#include "transdemarre.h"
#include "transchange.h"
#include <QMessageBox>

Joueur::Joueur()
{
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
    Bouge *bougeagauche   = new Bouge(this, Qt::Key_4, conteneur);
    bougeagauche->setChildMode(QState::ParallelStates);
        CouleurJoueur *couleurrouge  = new CouleurJoueur(this, QString(":/motif/jvr.png"), bougeagauche);
        PositionJoueur *platgauche   = new PositionJoueur(this, 270, bougeagauche);
    Bouge *bougeenhaut     = new Bouge(this, Qt::Key_8, conteneur);
    bougeenhaut->setChildMode(QState::ParallelStates);
        CouleurJoueur *couleurjaune  = new CouleurJoueur(this, QString(":/motif/jvj.png"), bougeenhaut);
        PositionJoueur *debouthaut   = new PositionJoueur(this, 0, bougeenhaut);
    Bouge *bougeenbas       = new Bouge(this, Qt::Key_2, conteneur);
    bougeenbas->setChildMode(QState::ParallelStates);
        CouleurJoueur *couleurmauve  = new CouleurJoueur(this,QString(":/motif/jvm.png"), bougeenbas);
        PositionJoueur *deboutbas    = new PositionJoueur(this, 180, bougeenbas);

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

    bougeagauche->addTransition(animationdelobjet, SIGNAL(finished()), bougeadroite);
    bougeadroite->addTransition(animationdelobjet, SIGNAL(finished()), bougeagauche);
    bougeenbas->addTransition(animationdelobjet, SIGNAL(finished()), bougeenhaut);
    bougeenhaut->addTransition(animationdelobjet, SIGNAL(finished()), bougeenbas);
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
