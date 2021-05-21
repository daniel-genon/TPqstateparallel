#ifndef SCENE_H
#define SCENE_H

#include <QToolButton>
#include <QLineEdit>
#include "../vue.h"
#include "joueur.h"
#include "borneappel.h"
class Scene : public QGraphicsScene
{
Q_OBJECT
public:
    Scene(int x, int y, int width, int height);
    ~Scene();
    void InitialiserScene(QToolButton *nouvellepartie,QToolButton *quitterlejeu,QLineEdit *linformation);
    void NettoyerScene();
    void ReInitialiserScene();
    void InitPtrVue(Vue *vptr);
    Joueur   *pJoueur() const;
    Vue      *pVue() const;

private:
    Joueur *joueur;
    Vue    *ptrvue;
    LBorne  lstborne;
};

#endif // SCENE_H
