#include "scene.h"
#include <QStateMachine>
#include <QFinalState>
#include <QtWidgets/QApplication>
#include "../zoneanime.h"
Scene::Scene(int x, int y, int width, int height): QGraphicsScene(x , y, width, height)
{
    ObjetImage *fondItem = new ObjetImage(QString(":/motif/fond.png"));
    fondItem->setZValue(1);
    fondItem->setPos(0,0);
    addItem(fondItem);
    joueur = new(Joueur);
    joueur->hide();
    addItem(joueur);
}
Scene::~Scene(){ if(joueur) delete joueur; }
void Scene::InitialiserScene( QToolButton *nouvellepartie, QToolButton *quitterlejeu, QLineEdit *linformation)
{
    linformation->setText("déplacement simple");
    QStateMachine *machine =new QStateMachine(this);
    ZoneAnime *zoneanime = new ZoneAnime(this, machine );
    QFinalState *final = new QFinalState( machine );
    zoneanime->addTransition(nouvellepartie, SIGNAL(clicked()), zoneanime );
    zoneanime->addTransition(quitterlejeu, SIGNAL(clicked()), final );
    connect(machine, SIGNAL(finished()), qApp, SLOT(quit()));
    machine->setInitialState(zoneanime);
    machine->start();
}
void Scene::NettoyerScene()
{
    joueur->Stop();
    joueur->hide();
    joueur->setEnabled(true);
}
void Scene::ReInitialiserScene()
{
    setFocusItem( joueur, Qt::OtherFocusReason );
    joueur->ReInitialiser();
}
void Scene::InitPtrVue(Vue *vptr)
{
    ptrvue = vptr;
    joueur->InitPtrVue( vptr );
}
Vue *Scene::pVue()       const {   return ptrvue;}
Joueur *Scene::pJoueur() const {   return joueur;}
